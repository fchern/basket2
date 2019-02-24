
#!/usr/bin/env Rscript
library("optparse")

option_list = list(
        make_option(c("-X", "--Xpath"), type="character", default=NULL,
            help="the csv file that stores X data frame, NOT a matrix! we do matrix conversion in the R script ", metavar="character"),
        make_option(c("-y", "--ypath"), type="character", default=NULL,
            help="the csv file thta stores the response vector. however, it  is still a dataframe " , metavar="character"),
        make_option(c("-w", "--weightpath"), type="character", default=NULL,
            help="the csv file that stores the weight vector", metavar="character"),
        make_option(c("-p", "--predictorspath"), type="character", default=NULL,
            help="the csv file that stores the predictor information", metavar="character"),
        make_option(c("-r", "--regularization"), type="character", default=NULL,
            help="regularization approach, 2 choices only LASSO, RIDGE", metavar="character")
        );

opt_parser = OptionParser(option_list=option_list);
opt = parse_args(opt_parser);


if (is.null(opt$Xpath)){
    print_help(opt_parser)
        stop("please specify the inptu X path", call.=FALSE)
}

if (is.null(opt$ypath)){
    print_help(opt_parser)
        stop("please specify response vector path", call.=FALSE)
}

if (is.null(opt$weightpath)){
    print_help(opt_parser)
        stop("please specify weight vector path", call.=FALSE)
}

if (is.null(opt$predictorspath)){
    print_help(opt_parser)
    stop("please specify predictor data frame path", call.=FALSE)
}

if (is.null(opt$regularization)){
    print_help(opt_parser)
    stop("please specify regularization approach", call.=FALSE)
}

print(paste("we are loading X data frame from ", opt$Xpath))
print(paste("we are loading y vector from ", opt$ypath))
print(paste("we are loading w vector from ", opt$weightpath))
print(paste("we are loading predictor data frame ", opt$predictorspath))
print(paste("we are loading regularization ", opt$regularization))
## program...
