#ifndef FILEPARSABLE_H
#define FILEPARSABLE_H

class FileParser;

class IFileParsable
{
public:
    virtual ~IFileParsable(){}

    virtual void accept(FileParser *visitor) = 0;
};

#endif /* FILEPARSABLE_H */
