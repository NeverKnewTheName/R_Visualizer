#ifndef FILEPARSABLE_H
#define FILEPARSABLE_H

class FileParser;

class FileParsable
{
public:
    FileParsable(){}
    virtual ~FileParsable(){}

    virtual void accept(FileParser *visitor) = 0;
};

#endif /* FILEPARSABLE_H */
