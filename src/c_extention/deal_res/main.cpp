// The functions contained in this file are pretty dummy
// and are included only as a placeholder. Nevertheless,
// they *will* get included in the shared library if you
// don't remove them :)
//
// Obviously, you 'll have to write yourself the super-duper
// functions to include in the resulting library...
// Also, it's not necessary to write every function in this file.
// Feel free to add more files in this project. They will be
// included in the resulting library.
//#include <cmath>
#include <Python.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <windows.h>
#include <tuple>
//#include <algorithm>


#include "py2cpp.hpp"

using namespace std;
using namespace dubzzz::Py2Cpp;

typedef  tuple<string,string,string,string,string,string,string,string, bool,string,string,string,int,string,string,bool,string, string, int, string> tuple_row;


struct  data_row{
    string lift_type;
    string plan_design_finish;
    string contract_id;
    string project_id;
    string project_name;
    string lift_id;
    string project_catalog;
    string is_urgent;
    string res_engineer;
    string act_design_finish;
    string prj_distribution;
    string remarks;
    string bom_trans_rel;
    string req_delivery_date;
    string refresh_id;
    int lift_num;
    string act_id;
    int flow_ser;
    string s_status;
 //   long iter=0;

    data_row & operator=(const data_row &other);
};
/*
wstring StringToWString(const string &str)
{
    wstring wstr(str.length(),L' ');
    copy(str.begin(), str.end(), wstr.begin());
    return wstr;
}

string WStringToString(const wstring &wstr)
{
    string str(wstr.length(), ' ');
    copy(wstr.begin(), wstr.end(), str.begin());
    return str;
}*/

void trim(string &s)
{
    if (s.empty())
    {
        return;
    }
     s.erase(0,s.find_first_not_of(" "));
     s.erase(s.find_last_not_of(" ") + 1);
}

data_row & data_row::operator=(const data_row &other)
{
    if(&other!=this)
    {
        lift_type = other.lift_type;
        plan_design_finish = other.plan_design_finish;
        contract_id=other.contract_id;
        project_id = other.project_id;
        project_name = other.project_name;
        lift_id = other.lift_id;
        res_engineer=other.res_engineer;
        act_design_finish = other.act_design_finish;
        prj_distribution = other.prj_distribution;
        remarks = other.remarks;
        bom_trans_rel = other.bom_trans_rel;
        req_delivery_date = other.req_delivery_date;
        refresh_id=other.refresh_id;
        lift_num = other.lift_num;

        project_catalog = other.project_catalog;
        is_urgent = other.is_urgent;
        act_id = other.act_id;
        flow_ser = other.flow_ser;
        s_status=other.s_status;
     //   iter = other.iter;
    }

    return *this;
}

void string_replace(string&s1,const string s2,const string s3)
{
	string::size_type pos=0;
    string::size_type a=s2.size();
	string::size_type b=s3.size();
	while((pos=s1.find(s2,pos))!=string::npos)
	{
		s1.replace(pos,a,s3);
		pos+=b;
	}
}


PyObject* topyfromstruct(data_row & row)
{
//MessageBox(NULL,"test", "对话框（标题）", MB_OK);
     return Py_BuildValue("(s, s, s,s,s,s,s,s,s,s,s,s,s,s,s,i,s,i,s)",row.lift_type.c_str(),row.plan_design_finish.c_str(), row.contract_id.c_str(),\
                          row.project_id.c_str(),row.project_name.c_str(),row.lift_id.c_str(),row.project_catalog.c_str(),row.is_urgent.c_str(), row.res_engineer.c_str(),row.act_design_finish.c_str(),\
                          row.prj_distribution.c_str(),row.remarks.c_str(),row.bom_trans_rel.c_str(),row.req_delivery_date.c_str(),row.refresh_id.c_str(),row.lift_num, row.act_id.c_str(), row.flow_ser, row.s_status.c_str());
}


PyObject* topyfromvector(vector<data_row> & rows)
{
    vector<data_row>::iterator  it;

    PyObject* pylist=PyList_New(rows.size());
    Py_ssize_t i_pos=0;
    for(it=rows.begin();it!=rows.end();it++,i_pos++)
    {
        PyList_SetItem(pylist,i_pos, topyfromstruct(*it));
    }

    //MessageBox(NULL, rows[0].project_id.c_str(), "对话框（标题）", MB_OK);

    return pylist;

}

data_row tocppfromtuple(PyObject* pyo)
{
    assert(pyo);

    data_row  row;

    Py_ssize_t i_size=15;

    if (PyTuple_Check(pyo))
    {


      if (PyTuple_Size(pyo) == 15)
      {
          PyObject * py0=PyTuple_GetItem(pyo,0);

          if(py0==Py_None)
              row.lift_type="";
          else
             row.lift_type = CppBuilder<string>()(py0) ;

          PyObject * py1=PyTuple_GetItem(pyo, 1);
          if(py1==Py_None)
            row.plan_design_finish="";
          else
          {
             row.plan_design_finish =  CppBuilder<string>()(py1) ;
          }



          PyObject * py2 = PyTuple_GetItem(pyo, 2);
          if(py2==Py_None)
              row.contract_id="";
          else
          {
             row.contract_id = CppBuilder<string>()(py2)  ;
          }


          PyObject *py3 = PyTuple_GetItem(pyo, 3);
          if(py3==Py_None)
               row.project_id="";
          else
          {
              row.project_id = CppBuilder<string>()(py3) ;

          }

          PyObject *py4 = PyTuple_GetItem(pyo, 4);
          if(py4==Py_None)
               row.project_name ="";
          else
          {
              row.project_name = CppBuilder<string>()(py4) ;

              string_replace(row.project_name, "~", "-");

          }

          PyObject *py5 = PyTuple_GetItem(pyo, 5);
          if(py5==Py_None)
            row.lift_id="";
          else
          {
              row.lift_id = CppBuilder<string>()(py5) ;
              /*

              size_t i_len = row.lift_id.size();

              size_t i_pos  = find_sub_str(row.lift_id, "*");

              if(i_pos!=-1)
              {
                  row.lift_id = row.lift_id.substr(0, i_pos);
              }

              i_pos =find_sub_str(row.lift_id, "[");

              if(i_pos!=-1)
              {
                  row.lift_id = row.lift_id.substr(0, i_pos);
              }*/

          }

          PyObject* py6 = PyTuple_GetItem(pyo, 6);
          if(py6==Py_None)
              row.res_engineer="";
          else
          {
              row.res_engineer = CppBuilder<string>()(py6) ;
          }

          //MessageBox(NULL,row.plan_design_finish.c_str(),"对话框（标题）", MB_OK);

          PyObject * py7 = PyTuple_GetItem(pyo,7);
          if(py7==Py_None)
              row.act_design_finish="";
          else
              row.act_design_finish = CppBuilder<string> ()(py7);

         PyObject * py8 = PyTuple_GetItem(pyo,8);
         if(py8==Py_None)
            row.prj_distribution="";
         else
             row.prj_distribution = CppBuilder<string> ()(py8) ;


         PyObject *py9 = PyTuple_GetItem(pyo, 9);
         if(py9==Py_None)
             row.remarks = "";
         else
              row.remarks =CppBuilder<string> ()(py9) ;

        PyObject *py10 = PyTuple_GetItem(pyo, 10);
        if(py10==Py_None)
            row.bom_trans_rel="";
        else
           row.bom_trans_rel = CppBuilder<string>()(py10);

        PyObject* py11 = PyTuple_GetItem(pyo, 11);
        if(py11==Py_None)
            row.req_delivery_date="";
        else
            row.req_delivery_date = CppBuilder<string>()(py11);

        PyObject *py13 =PyTuple_GetItem(pyo, 13);

        string s_load, s_speed;
        if(py13==Py_None)
            s_load = "";
        else
            s_load = CppBuilder<string>()(py13);

        PyObject * py14=PyTuple_GetItem(pyo, 14);

        if(py14==Py_None)
            s_speed ="";
        else
            s_speed = CppBuilder<string>()(py14);


        trim(s_load);
        trim(s_speed);


        if(s_speed.substr(0,1)==".")
            s_speed="0"+s_speed;

         // MessageBox(NULL,s_speed.c_str(),  "对话框（标题）", MB_OK);

          if(!row.lift_type.empty()&&!s_load.empty()&&!s_speed.empty())
            row.lift_type=row.lift_type+"@"+s_load+"kg"+s_speed+"m/s";

         row.lift_num = 1;

         row.project_catalog="";
         row.is_urgent="";
         row.act_id="";
         row.flow_ser=0;
         row.s_status="";

         return row;
      }
      else
      {
        ostringstream oss;
        oss << "PyTuple length differs from required one: "
            << "PyTuple(" << PyTuple_Size(pyo) << ") "
            << "and required( %d" <<i_size << ")";
        throw length_error(oss.str());
      }
    }
    throw invalid_argument("Not a PyTuple instance");

}

vector<data_row> tocppfromlist(PyObject * pyo)
{
    assert(pyo);

    if(PyList_Check(pyo))
    {

       vector<data_row> rows;

       data_row row;

       Py_ssize_t i_rows= PyList_Size(pyo);

      for(Py_ssize_t i=0;i<i_rows;i++)
      {

      //     MessageBox(NULL, "test", "对话框（标题）", MB_OK);
           row = tocppfromtuple(PyList_GetItem(pyo, i));

           rows.push_back(row);

      }
      //MessageBox(NULL, rows[0].project_id.c_str(), "对话框（标题）", MB_OK);
       return rows;
    }
   throw invalid_argument("Not a PyList instance");
}


vector<data_row> combine_the_same_section(vector<data_row> &rows)
{
    vector<data_row> drv_res;
    data_row dr_base;
    size_t i_count = rows.size();

    //char a[25];

    //MessageBox(NULL, itoa(i_count, a, 10), "对话框（标题）", MB_OK);

    string s_refresh_id;

    size_t i_pos, i_same_count;
    size_t i_new =0;

    dr_base=rows[0];
    dr_base.lift_num=1;

    dr_base.refresh_id=dr_base.contract_id+":"+dr_base.project_id+":"+dr_base.project_name+":"+dr_base.lift_id;

    drv_res.push_back(dr_base);
    i_pos=i_new;
    i_same_count=1;

    bool b_new=false;


    for(size_t i=1;i<i_count;i++)
    {

       if(dr_base.project_id!=rows[i].project_id)
       {
           dr_base=rows[i];
           dr_base.lift_num=1;

           dr_base.refresh_id=dr_base.contract_id+":"+dr_base.project_id+":"+dr_base.project_name+":"+dr_base.lift_id;

           drv_res.push_back(dr_base);
           i_new++;
           i_same_count =1;
           i_pos=i_new;
           b_new=false;
       }else{
            dr_base=rows[i];
            dr_base.lift_num=1;
            dr_base.refresh_id=dr_base.contract_id+":"+dr_base.project_id+":"+dr_base.project_name+":"+dr_base.lift_id;


            for(size_t j=i_pos; j<i_pos+i_same_count; j++)
            {
                if(dr_base.lift_type==drv_res[j].lift_type&&dr_base.plan_design_finish==drv_res[j].plan_design_finish&&
                dr_base.res_engineer==drv_res[j].res_engineer&&dr_base.act_design_finish==drv_res[j].act_design_finish&&dr_base.prj_distribution==drv_res[j].prj_distribution&&dr_base.s_status==drv_res[j].s_status&&
                dr_base.bom_trans_rel==drv_res[j].bom_trans_rel&&dr_base.project_catalog==drv_res[j].project_catalog&&dr_base.is_urgent==drv_res[j].is_urgent&&dr_base.req_delivery_date==drv_res[j].req_delivery_date)
                {
                   drv_res[j].lift_id=drv_res[j].lift_id+","+dr_base.lift_id;
                  //MessageBox(NULL, drv_res[j].lift_id.c_str(), "对话框（标题）", MB_OK);
                   drv_res[j].refresh_id=drv_res[j].contract_id+":"+drv_res[j].project_id+":"+drv_res[j].project_name+":"+drv_res[j].lift_id;

                   drv_res[j].lift_num++;
                   b_new=true;
                   break;
                }else
                    b_new=false;
            }

            if(!b_new)
            {
            drv_res.push_back(dr_base);
            i_new++;
            i_same_count++;
                    }
       }
    }


    rows.clear();

    return drv_res;
}

bool isNum(string str)
{
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d))
        return false;
    if (sin >> c)
        return false;
    return true;
}


string get_num_from_string(string str)
{
    string s_sub, s_p;

    size_t  i_len = str.length();

    for(size_t i=0;i<i_len;i++)
    {
         s_p = str.substr(i,1);
        if(isNum(s_p))
            s_sub = s_sub+s_p;
    }

    //MessageBox(NULL, s_sub.c_str(), "对话框（标题）", MB_OK);
    return s_sub;
}

/*
bool SortByM1( data_row  &v1, data_row &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致
{
    return  v1.iter < v2.iter;//升序排列
}*/

void del_str(string &str)
{
    size_t len = str.size();
    string sub_str;
    if(len>0)
    {
        sub_str = str.substr(len-1,1);
        if(sub_str=="*")
            str=str.substr(0,len-1);
    }

    size_t i_pos=str.rfind("[");

    if(i_pos!=str.npos)
    {
        str=str.substr(0,i_pos);
    }

}

string prj_catalog_int2string(int i_prj)
{
    string str;
    switch(i_prj)
    {

    case 1:
        str = "Common Project";
        break;
    case 2:
        str = "High-Speed Project";
        break;
    case 3:
        str = "Special Project";
        break;
    case 4:
        str = "Major Project";
        break;
    case 5:
        str = "Pre_engineering";
        break;
    case 6:
        str = "Lean Project";
        break;
    default:
        str="";
        break;
    }

    return str;

}


string prj_catalog_2string(string s_catalog)
{
    int i_prj= atoi(s_catalog.c_str());
    string str;
    switch(i_prj)
    {

    case 1:
        str = "Common Project";
        break;
    case 2:
        str = "High-Speed Project";
        break;
    case 3:
        str = "Special Project";
        break;
    case 4:
        str = "Major Project";
        break;
    case 5:
        str = "Pre_engineering";
        break;
    case 6:
        str = "Lean Project";
        break;
    default:
        str="";
        break;
    }

    return str;

}

string Bool2Y(bool b_bool)
{
    string str;
    if(b_bool)
        str= "Y";
    else
        str= "";

	return str;
}

vector<data_row> from_dataset(PyObject * pyo)
{
    //MessageBox(NULL, "test1", "对话框（标题）", MB_OK);
    vector<tuple_row> data_rows=CppBuilder<vector<tuple_row>>()(pyo);
    size_t i_rows=data_rows.size();

    vector<data_row> res_data;
    tuple_row  f_temp;

    data_row t_temp;

    string  instance_id,temp,action_id,start_date, finish_date, action_name;
    string str, s_load,s_speed;
    int  flow_ser,total_flow;
    bool  b_continue=false;
    //int i_catalog;
    bool b_is_urgent;

    instance_id = "";
    for(size_t i=0;i<i_rows; i++)
    {
         f_temp=data_rows[i];

         temp=get<10>(f_temp);
         action_id = get<11>(f_temp);
         start_date=get<13>(f_temp);
         finish_date = get<14>(f_temp);
         flow_ser = get<12>(f_temp);
         total_flow = get<18>(f_temp);

         action_name = get<19>(f_temp);

        if(instance_id!=temp)
         {

         //   str=get_num_from_string(t_temp.bom_trans_rel)+get_num_from_string(t_temp.contract_id);
         //    t_temp.iter = atol(str.c_str());

         //    printf("%ld",t_temp.iter);

             if(i!=0&&!b_continue)
                res_data.push_back(t_temp);

             b_continue =false;

             instance_id = temp;
             s_load = get<16>(f_temp);
             s_speed = get<17>(f_temp);
             t_temp.lift_type= get<0>(f_temp);
             t_temp.plan_design_finish = get<1>(f_temp);
             t_temp.req_delivery_date = get<2>(f_temp);
             t_temp.contract_id = get<3>(f_temp);
             t_temp.project_id = get<4>(f_temp);
             t_temp.project_name = get<5>(f_temp);
             t_temp.lift_id = get<6>(f_temp);

            string_replace(t_temp.project_name, "~", "-");

            trim(s_load);
            trim(s_speed);


             if(s_speed.substr(0,1)==".")
                   s_speed = "0"+s_speed;

            if(!t_temp.lift_type.empty()&&!s_load.empty()&&!s_speed.empty())
                  t_temp.lift_type = t_temp.lift_type+"@"+s_load+"kg"+s_speed+"m/s";

             str=get<7>(f_temp);
             //i_catalog = get<6>(f_temp);
             b_is_urgent = get<8>(f_temp);

             t_temp.project_catalog = prj_catalog_2string(str);
             t_temp.is_urgent = Bool2Y(b_is_urgent);
             del_str(t_temp.lift_id);
             //t_temp.res_engineer = get<6>(f_temp);
             t_temp.lift_num =1;

            //if(action_id == "AT00000003")
            // {
                 t_temp.act_design_finish = start_date;


             //}
             t_temp.res_engineer="";
             t_temp.bom_trans_rel="";
             t_temp.prj_distribution = "";

         }

         if(b_continue)
             continue;

         if(instance_id==temp)
         {

            if(get<15>(f_temp))
            {
                 t_temp.act_id=action_id;
                 t_temp.flow_ser = flow_ser;
                 t_temp.s_status = action_name;
                 b_continue=true;
            }else if(total_flow==flow_ser)
            {
                 t_temp.act_id=action_id;
                 t_temp.flow_ser = flow_ser;
                 t_temp.s_status="completed";
            }

             if(action_id =="AT00000004")
             {
                 t_temp.prj_distribution = start_date;
                 t_temp.res_engineer = get<9>(f_temp);
             }

             if(action_id=="AT00000008")
             {
                 t_temp.bom_trans_rel = finish_date;

                if(t_temp.plan_design_finish.empty())
                     t_temp.plan_design_finish = finish_date;
                // MessageBox(NULL, finish_date.c_str(), "对话框（标题）", MB_OK);
             }

         }


         if(i==i_rows-1 || b_continue)
            res_data.push_back(t_temp);

    }

    if(res_data.size()==0)
        MessageBox(NULL, "test2", "对话框（标题）", MB_OK);

    data_rows.clear();

  //  sort(res_data.begin(), res_data.end(), SortByM1);

    return res_data;
}

extern "C"
{
    // A function adding two integers and returning the result
    PyObject * combine_list( PyObject * pyo)
    {
        assert(pyo);
        PyObject *py_res;
        vector<data_row> drv_temp =tocppfromlist(pyo);
        vector<data_row> drv_res=combine_the_same_section(drv_temp);

        py_res = topyfromvector(drv_res);
        drv_res.clear();

        return py_res;
    }

    PyObject * combine_new_list(PyObject* pyo)
    {
        assert(pyo);
        PyObject* py_res;

        //MessageBox(NULL, "test1", "对话框（标题）", MB_OK);
        vector<data_row> drv_temp = from_dataset(pyo);
       //MessageBox(NULL, "test2", "对话框（标题）", MB_OK);
        vector<data_row>  drv_res = combine_the_same_section(drv_temp);
        //MessageBox(NULL, "test3", "对话框（标题）", MB_OK);
        py_res= topyfromvector(drv_res);
        //MessageBox(NULL, "test4", "对话框（标题）", MB_OK);
        drv_res.clear();
        return py_res;
    }

}


