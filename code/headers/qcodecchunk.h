#ifndef QCODECHUNK_H
#define QCODECHUNK_H

template <typename T>
class QCodecChunk
{

	public:

		QCodecChunk();
		QCodecChunk(T *data, int size);
		~QCodecChunk();

		static QCodecChunk create(int size);

		T* data();
		int size();

		void setData(T *data, int size);
		void setData(T *data);
		void setSize(int size);

	private:

		T *mData;
		int mSize;

};

typedef QCodecChunk<char> QCodecChunk8;
typedef QCodecChunk<short> QCodecChunk16;
typedef QCodecChunk<int> QCodecChunk32;

#endif
