//һ����������һ��˳��ṹ�������в���ֵ��ģ�壬���������ֵ��������ǰ�� 
template<typename ElemType>
ElemType* find(ElemType* first,const ElemType* last,ElemType value)
{
	if((!first)||(!last))return 0;
	
	for(;first!=last;first++){
		if(*first==value)return first; 
	}
	return 0;
}

//����֧������ṹ�Ĳ���ģ��
template<typename iteratorType,typename ElemType>
ElemType* find(iteratorType first,iteratorType last,ElemType value)
{
	if((!first)||(!last))return 0;
	
	for(;first!=last;first++){
		if(*first==value)return first; 
	}
	return 0;
} 
