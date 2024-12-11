#include<iostream>
#include<fstream>
#include <sstream>
#include<vector>
#define MAX 3500
using namespace std;
struct ITJob
{
    string position;
    string location;
    string gender;
    string education;
    int experience;
    long long salary;
};
struct ArrList
{
    ITJob itjb[MAX];
    int size = 0;
    int max = MAX;
};
struct MinMaxResult 
{
    int minPos;  // Vị trí của phần tử nhỏ nhất
    int maxPos;  // Vị trí của phần tử lớn nhất
};

//Đọc file
bool readFile(ArrList& arr, string filename);

//In file
bool printFile(const ArrList& arr, string filename);

//In thông tin
void printJob(ITJob itjb);

//Tìm min,max
MinMaxResult findMinMax(ArrList& arr, int left, int right);
void findMinMax(ArrList& arr);

//Them du lieu
void addJob(ArrList& arr);

//Xoa du lieu
void deleteJob(ArrList& arr, int position);

int main()
{
    ITJob min, max;
    ArrList arr;
    arr.size = 0;
    arr.max = MAX;
    int input;
    readFile(arr, "D:/position_salary.csv");
    for (int i = 0; i < arr.size; i++)
    {
        //cout << "ID: " << i << endl;
        //printJob(arr.itjb[i]);
    }
    printFile(arr, "D:/file.txt");
    //findMinMax(arr);
    //addJob(arr);
    deleteJob(arr, 0);  
    printJob(arr.itjb[0]);
}

//Đọc file
bool readFile(ArrList& arr, string filename)
{
    ifstream file(filename);
    if (!file.is_open()) 
    {
        cout << "Error! Cannot open file: " << filename << endl;
        return false;
    }

    string line;
    getline(file, line); // Bỏ qua dòng header

    while (getline(file, line) && arr.size < MAX) 
    {
        try 
        {
            stringstream ss(line);
            string data;
            string temp;
            string remaining_line = line;

            // Đọc position
            if (line[0] == '\"') // Nếu dòng bắt đầu bằng dấu "
            {  
                size_t pos = line.find('\"', 1);  // Tìm dấu " thứ hai
                while (pos != string::npos) {
                    if (pos + 1 < line.length() && line[pos + 1] != ',') // Nếu sau dấu " không phải là dấu , thì tìm tiếp
                    {
                        pos = line.find('\"', pos + 1);
                    }
                    else // Đã tìm thấy cặp "" hoàn chỉnh 
                    {
                        arr.itjb[arr.size].position = line.substr(0, pos + 1);
                        remaining_line = line.substr(pos + 2);  // +2 để bỏ qua dấu " và dấu ,
                        break;
                    }
                }
                ss.str(remaining_line);  // Cập nhật stringstream với phần còn lại của dòng
            }
            else if (getline(ss, data, ',')) 
            {
                // Xử lý các trường hợp khác của position
                if (data.empty()) {
                    arr.itjb[arr.size].position = "No Info, Info Missing";
                }
                else if (data[0] == '-') {
                    arr.itjb[arr.size].position = "\"" + data + "\"";
                }
                else {
                    arr.itjb[arr.size].position = data;
                }
            }

            // Đọc location
            getline(ss, data, ',');
            if (!data.empty() && data[0] == '\"') {
                size_t start_pos = remaining_line.find('\"');
                if (start_pos != string::npos) {
                    size_t pos = remaining_line.find('\"', start_pos + 1);
                    while (pos != string::npos) {
                        if (pos + 1 < remaining_line.length() && remaining_line[pos + 1] != ',') {
                            pos = remaining_line.find('\"', pos + 1);
                        }
                        else {
                            arr.itjb[arr.size].location = remaining_line.substr(start_pos, pos - start_pos + 1);
                            remaining_line = remaining_line.substr(pos + 2);
                            ss.str(remaining_line);
                            break;
                        }
                    }
                }
            }
            else 
            {
                arr.itjb[arr.size].location = data;
            }

            // Đọc gender
            if (getline(ss, data, ',')) 
            {
                arr.itjb[arr.size].gender = data;
            }

            // Đọc education
            if (getline(ss, data, ',')) 
            {
                arr.itjb[arr.size].education = data;
            }

            // Đọc experience
            if (getline(ss, data, ',')) 
            {
                arr.itjb[arr.size].experience = stoi(data);
            }

            // Đọc salary
            if (getline(ss, data)) 
            {
                arr.itjb[arr.size].salary = stoll(data);
            }

            arr.size++;
        }
        catch (const exception& e) 
        {
            cout << "Cannot read line " << arr.size + 1 << ": " << e.what() << endl;
            continue;
        }
    }

    file.close();
    cout << "Read file successful. Total records: " << arr.size << endl;
    return true;
}

//In file
bool printFile(const ArrList& arr, string filename)
{
    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        cout << "Khong the tao file " << filename << endl;
        return false;
    }

    try 
    {
        // Ghi tiêu đề
        outFile << "Position,Location,Gender,Education,Experience,Salary\n";

        // Ghi dữ liệu
        for (int i = 0; i < arr.size; i++)
        {
            outFile << arr.itjb[i].position << "," << arr.itjb[i].location << "," << arr.itjb[i].gender << "," << arr.itjb[i].education << "," << arr.itjb[i].experience << "," << arr.itjb[i].salary << "\n";
        }

        outFile.close();
        cout << "The dataset has been print out the file successfully!" << endl;
        return true;
    }
    catch (const exception& e)
    {
        cout << "Error! Can not print file!" << e.what() << endl;
        outFile.close();
        return false;
    }
}

//In thông tin
void printJob(ITJob itjb)
{

    cout << "---------------------------------------------" << endl;
    cout << "Position: " << itjb.position << endl;
    cout << "Location: " << itjb.location << endl;
    cout << "Gender : " << itjb.gender << endl;
    cout << "Education : " << itjb.education << endl;
    cout << "Experience : " << itjb.experience << endl;
    cout << "Salary : " << itjb.salary << endl;
    cout << "---------------------------------------------" << endl;
}

// Tìm Min,Max 
MinMaxResult findMinMax(ArrList& arr, int left, int right) 
{
    MinMaxResult result;

    // Trường hợp cơ sở 1: Chỉ có một phần tử
    if (left == right) 
    {
        result.minPos = result.maxPos = left;
        return result;
    }

    // Trường hợp cơ sở 2: Có hai phần tử
    if (right == left + 1) {
        if (arr.itjb[left].experience <= arr.itjb[right].experience) 
        {
            result.minPos = left;
            result.maxPos = right;
        }
        else 
        {
            result.minPos = right;
            result.maxPos = left;
        }
        return result;
    }

    // Chia mảng thành hai phần
    int mid = left + (right - left) / 2;

    // Đệ quy tìm min-max ở nửa trái
    MinMaxResult leftResult = findMinMax(arr, left, mid);

    // Đệ quy tìm min-max ở nửa phải
    MinMaxResult rightResult = findMinMax(arr, mid + 1, right);

    // Kết hợp kết quả
    result.minPos = (arr.itjb[leftResult.minPos].experience <= arr.itjb[rightResult.minPos].experience)
        ? leftResult.minPos : rightResult.minPos;

    result.maxPos = (arr.itjb[leftResult.maxPos].experience >= arr.itjb[rightResult.maxPos].experience)
        ? leftResult.maxPos : rightResult.maxPos;

    return result;
}

// Hàm wrapper để gọi thuật toán chia để trị
void findMinMax(ArrList& arr) 
{
    if (arr.size == 0) 
    {
        cout << "Mảng rỗng!" << endl;
        return;
    }

    MinMaxResult result = findMinMax(arr, 0, arr.size - 1);

    // In kết quả
    cout << "\nJob Info required least experience:" << endl;
    cout << "Position: " << arr.itjb[result.minPos].position << endl;
    cout << "Location: " << arr.itjb[result.minPos].location << endl;
    cout << "Gender: " << arr.itjb[result.minPos].gender << endl;
    cout << "Education: " << arr.itjb[result.minPos].education << endl;
    cout << "Experience: " << arr.itjb[result.minPos].experience << " Years" << endl;
    cout << "Salary: " << arr.itjb[result.minPos].salary << endl;

    cout << "\nJob Info required most experience:" << endl;
    cout << "Position: " << arr.itjb[result.maxPos].position << endl;
    cout << "Location: " << arr.itjb[result.maxPos].location << endl;
    cout << "Gender: " << arr.itjb[result.maxPos].gender << endl;
    cout << "Education: " << arr.itjb[result.maxPos].education << endl;
    cout << "Experience: " << arr.itjb[result.maxPos].experience << " Years" << endl;
    cout << "Salary: " << arr.itjb[result.maxPos].salary << endl;
}

//Thêm dữ liệu
void addJob(ArrList& arr) 
{
    if (arr.size >= MAX) 
    {
        std::cout << "The dataset is full, can not create more!\n";
        return;
    }

    ITJob newJob;
    // Nhập thông tin cho job mới
    std::cout << "(Position): ";
    std::getline(std::cin, newJob.position);

    std::cout << "(Location): ";
    std::getline(std::cin, newJob.location);

    std::cout << "(Gender - Male/Female/Others): ";
    std::getline(std::cin, newJob.gender);

    std::cout << "(Education): ";
    std::getline(std::cin, newJob.education);

    std::cout << "(Experience Years): ";
    std::cin >> newJob.experience;

    std::cout << "(Salary): ";
    std::cin >> newJob.salary;
    std::cin.ignore(); // Xóa bộ đệm

    // Thêm job mới vào mảng
    arr.itjb[arr.size] = newJob;
    arr.size++;

    std::cout << "\nAdd new Job successfully!\n";
}

//Xoa du lieu
void deleteJob(ArrList& arr, int position) {
    // Kiểm tra vị trí có hợp lệ không
    if (position < 0 || position >= arr.size) {
        std::cout << "Position is not available!\n";
        return;
    }

    // Hiển thị thông tin job sắp xóa
    std::cout << "\nThe Deleted Job Info:\n";
    std::cout << "Position: " << arr.itjb[position].position << "\n";
    std::cout << "Location: " << arr.itjb[position].location << "\n";
    std::cout << "Gender: " << arr.itjb[position].gender << "\n";
    std::cout << "Education: " << arr.itjb[position].education << "\n";
    std::cout << "Experience: " << arr.itjb[position].experience << "\n";
    std::cout << "Salary: " << arr.itjb[position].salary << "\n";

    char confirm;
    std::cout << "\nDo you sure that you want to delete? (y/n): ";
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        // Dịch chuyển các phần tử sau vị trí i lên trước một vị trí
        for (int j = position; j < arr.size - 1; j++) 
        {
            arr.itjb[j] = arr.itjb[j + 1];
        }
        arr.size--; // Giảm kích thước mảng
        std::cout << "Delete Successful!\n";
    }
    else 
    {
        std::cout << "Stop Delete Successful!\n";
    }
}