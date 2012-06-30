#include <qcodecchunk.h>

template <typename T>
QCodecChunk<T>::QCodecChunk()
{
	mData = 0;
	mSize = 0;
}

template <typename T>
QCodecChunk<T>::QCodecChunk(T *data, int size)
{
	mData = data;
	mSize = size;
}

template <typename T>
QCodecChunk<T>::~QCodecChunk()
{
	if(mData != 0)
	{
		delete mData;
		mData = 0;
	}
}

template <typename T>
QCodecChunk QCodecChunk<T>::create(int size)
{
	return QCodecChunk(new T[size], size);
}

template <typename T>
T* QCodecChunk<T>::data()
{
	return mData;
}

template <typename T>
int QCodecChunk<T>::size()
{
	return mSize;
}

template <typename T>
void QCodecChunk<T>::setData(T *data, int size)
{
	mData = data;
	mSize = size;
}

template <typename T>
void QCodecChunk<T>::setData(T *data)
{
	mData = data;
}

template <typename T>
void QCodecChunk<T>::setSize(int size)
{
	mSize = size;
}
