/***** This code was generated by Yaggo. Do not edit ******/

#ifndef __HISTO_ARGS_HPP__
#define __HISTO_ARGS_HPP__

#include <jellyfish/yaggo.hpp>

class histo_args {
public:
  uint64_t                       low_arg;
  bool                           low_given;
  uint64_t                       high_arg;
  bool                           high_given;
  uint64_t                       increment_arg;
  bool                           increment_given;
  uint32_t                       threads_arg;
  bool                           threads_given;
  bool                           full_flag;
  const char *                   output_arg;
  bool                           output_given;
  uint64_t                       buffer_size_arg;
  bool                           buffer_size_given;
  bool                           verbose_flag;
  yaggo::string                  db_arg;

  enum {
    USAGE_OPT = 1000,
    FULL_HELP_OPT,
    HELP_OPT
  };

  histo_args() : 
    low_arg(1), low_given(false),
    high_arg(10000), high_given(false),
    increment_arg(1), increment_given(false),
    threads_arg(1), threads_given(false),
    full_flag(false),
    output_arg(""), output_given(false),
    buffer_size_arg(10000000), buffer_size_given(false),
    verbose_flag(false)
  { }

  histo_args(int argc, char* argv[]) :
    low_arg(1), low_given(false),
    high_arg(10000), high_given(false),
    increment_arg(1), increment_given(false),
    threads_arg(1), threads_given(false),
    full_flag(false),
    output_arg(""), output_given(false),
    buffer_size_arg(10000000), buffer_size_given(false),
    verbose_flag(false)
  { parse(argc, argv); }

  void parse(int argc, char* argv[]) {
    static struct option long_options[] = {
      {"low", 1, 0, 'l'},
      {"high", 1, 0, 'h'},
      {"increment", 1, 0, 'i'},
      {"threads", 1, 0, 't'},
      {"full", 0, 0, 'f'},
      {"output", 1, 0, 'o'},
      {"buffer-size", 1, 0, 's'},
      {"verbose", 0, 0, 'v'},
      {"help", 0, 0, HELP_OPT},
      {"full-help", 0, 0, FULL_HELP_OPT},
      {"usage", 0, 0, USAGE_OPT},
      {"version", 0, 0, 'V'},
      {0, 0, 0, 0}
    };
    static const char *short_options = "Vl:h:i:t:fo:s:v";

    std::string err;
#define CHECK_ERR(type,val,which) if(!err.empty()) { std::cerr << "Invalid " #type " '" << val << "' for [" which "]: " << err << "\n"; exit(1); }
    while(true) { 
      int index = -1;
      int c = getopt_long(argc, argv, short_options, long_options, &index);
      if(c == -1) break;
      switch(c) {
      case ':': 
        std::cerr << "Missing required argument for "
                  << (index == -1 ? std::string(1, (char)optopt) : std::string(long_options[index].name))
                  << std::endl;
        exit(1);
      case HELP_OPT:
        std::cout << usage() << "\n\n" << help() << std::endl;
        exit(0);
      case USAGE_OPT:
        std::cout << usage() << "\nUse --help for more information." << std::endl;
        exit(0);
      case 'V':
        print_version();
        exit(0);
      case '?':
        std::cerr << "Use --usage or --help for some help\n";
        exit(1);
      case FULL_HELP_OPT:
        std::cout << usage() << "\n\n" << help() << "\n\n" << hidden() << std::endl;
        exit(0);
      case 'l':
        low_given = true;
        low_arg = yaggo::conv_uint<uint64_t>((const char *)optarg, err, false);
        CHECK_ERR(uint64_t, optarg, "-l, --low=uint64")
        break;
      case 'h':
        high_given = true;
        high_arg = yaggo::conv_uint<uint64_t>((const char *)optarg, err, false);
        CHECK_ERR(uint64_t, optarg, "-h, --high=uint64")
        break;
      case 'i':
        increment_given = true;
        increment_arg = yaggo::conv_uint<uint64_t>((const char *)optarg, err, false);
        CHECK_ERR(uint64_t, optarg, "-i, --increment=uint64")
        break;
      case 't':
        threads_given = true;
        threads_arg = yaggo::conv_uint<uint32_t>((const char *)optarg, err, false);
        CHECK_ERR(uint32_t, optarg, "-t, --threads=uint32")
        break;
      case 'f':
        full_flag = true;
        break;
      case 'o':
        output_given = true;
        output_arg = optarg;
        break;
      case 's':
        buffer_size_given = true;
        buffer_size_arg = yaggo::conv_uint<uint64_t>((const char *)optarg, err, true);
        CHECK_ERR(uint64_t, optarg, "-s, --buffer-size=Buffer length")
        break;
      case 'v':
        verbose_flag = true;
        break;
      }
    }

    // Parse arguments
    if(argc - optind != 1)
      error("Requires exactly 1 argument.");
    db_arg = yaggo::string(argv[optind]);
    ++optind;
  }

#define histo_args_USAGE "Usage: jellyfish histo [options] db:path"
  const char * usage() const { return histo_args_USAGE; }
  void error(const char *msg) { 
    std::cerr << "Error: " << msg << "\n" << usage()
              << "\nUse --help for more information"
              << std::endl;
    exit(1);
  }

#define histo_args_HELP "Create an histogram of k-mer occurrences\n\nCreate an histogram with the number of k-mers having a given\n" \
  "count. In bucket 'i' are tallied the k-mers which have a count 'c'\n" \
  "satisfying 'low+i*inc <= c < low+(i+1)*inc'. Buckets in the output are\n" \
  "labeled by the low end point (low+i*inc).\n" \
  "\n" \
  "The last bucket in the output behaves as a catchall: it tallies all\n" \
  "k-mers with a count greater or equal to the low end point of this\n" \
  "bucket.\n\n" \
  "Options (default value in (), *required):\n" \
  " -l, --low=uint64                         Low count value of histogram (1)\n" \
  " -h, --high=uint64                        High count value of histogram (10000)\n" \
  " -i, --increment=uint64                   Increment value for buckets (1)\n" \
  " -t, --threads=uint32                     Number of threads (1)\n" \
  " -f, --full                               Full histo. Don't skip count 0. (false)\n" \
  " -o, --output=string                      Output file\n" \
  " -v, --verbose                            Output information (false)\n" \
  "     --usage                              Usage\n" \
  "     --help                               This message\n" \
  "     --full-help                          Detailed help\n" \
  " -V, --version                            Version"

  const char * help() const { return histo_args_HELP; }
#define histo_args_HIDDEN "Hidden options:\n" \
  " -s, --buffer-size=Buffer length          Length in bytes of input buffer (10000000)"

  const char * hidden() const { return histo_args_HIDDEN; }
  void print_version(std::ostream &os = std::cout) const {
#ifndef PACKAGE_VERSION
#define PACKAGE_VERSION "0.0.0"
#endif
    os << PACKAGE_VERSION << "\n";
  }
  void dump(std::ostream &os = std::cout) {
    os << "low_given:" << low_given << " low_arg:" << low_arg << "\n";
    os << "high_given:" << high_given << " high_arg:" << high_arg << "\n";
    os << "increment_given:" << increment_given << " increment_arg:" << increment_arg << "\n";
    os << "threads_given:" << threads_given << " threads_arg:" << threads_arg << "\n";
    os << "full_flag:" << full_flag << "\n";
    os << "output_given:" << output_given << " output_arg:" << output_arg << "\n";
    os << "buffer_size_given:" << buffer_size_given << " buffer_size_arg:" << buffer_size_arg << "\n";
    os << "verbose_flag:" << verbose_flag << "\n";
    os << "db_arg:" << db_arg << "\n";
  }
private:
};

#endif // __HISTO_ARGS_HPP__"
