int compareInts(const void *p, const void *q)
 {
    int x = *(const int *)p;
    int y = *(const int *)q;

    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    return 0;
}
int BinarySearch(int* array,int arraySize, int toFind)
{
  int lb = 0;
  int ub = arraySize-1;
  int mid;
  int found =0;

  while(lb <= ub)
  {
    mid = lb + (ub-lb)/2;
    if(array[mid] == toFind)
    {
      found =1;
      break;
    }
    else if(array[mid] < toFind)
    {
      lb = mid +1;
    }
    else
    {
      ub = mid -1;
    }
  }
  return found;
}
