#include <indicator/progress_bar.hpp>
#include <indicator/progress_spinner.hpp>
#include <vector>

/*
  [
    "|/-\\",
    "⠂-–—–-",
    "◐◓◑◒",
    "◴◷◶◵",
    "◰◳◲◱",
    "▖▘▝▗",
    "■□▪▫",
    "▌▀▐▄",
    "▉▊▋▌▍▎▏▎▍▌▋▊▉",
    "▁▃▄▅▆▇█▇▆▅▄▃",
    "←↖↑↗→↘↓↙",
    "┤┘┴└├┌┬┐",
    "◢◣◤◥",
    ".oO°Oo.",
    ".oO@*",
    ["🌍", "🌎", "🌏"],
    "◡◡ ⊙⊙ ◠◠",
    "☱☲☴",
    "⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏",
    "⠋⠙⠚⠞⠖⠦⠴⠲⠳⠓",
    "⠄⠆⠇⠋⠙⠸⠰⠠⠰⠸⠙⠋⠇⠆",
    "⠋⠙⠚⠒⠂⠂⠒⠲⠴⠦⠖⠒⠐⠐⠒⠓⠋",
    "⠁⠉⠙⠚⠒⠂⠂⠒⠲⠴⠤⠄⠄⠤⠴⠲⠒⠂⠂⠒⠚⠙⠉⠁",
    "⠈⠉⠋⠓⠒⠐⠐⠒⠖⠦⠤⠠⠠⠤⠦⠖⠒⠐⠐⠒⠓⠋⠉⠈",
    "⠁⠁⠉⠙⠚⠒⠂⠂⠒⠲⠴⠤⠄⠄⠤⠠⠠⠤⠦⠖⠒⠐⠐⠒⠓⠋⠉⠈⠈",
    "⢄⢂⢁⡁⡈⡐⡠",
    "⢹⢺⢼⣸⣇⡧⡗⡏",
    "⣾⣽⣻⢿⡿⣟⣯⣷",
    "⠁⠂⠄⡀⢀⠠⠐⠈",
    ["🌑", "🌒", "🌓", "🌔", "🌕", "🌝", "🌖", "🌗", "🌘", "🌚"],
    ["🕛", "🕐", "🕑", "🕒", "🕓", "🕔", "🕕", "🕖", "🕗", "🕘", "🕙", "🕚"]
  ]
*/

int main() {

  // Hide cursor
  std::cout << "\e[?25l";

  {}

  //
  // PROGRESS BAR 1
  //
  indicator::ProgressBar p1;
  p1.set_bar_width(50);
  p1.start_bar_with("[");
  p1.fill_bar_progress_with("■");
  p1.lead_bar_progress_with("■");
  p1.fill_bar_remainder_with(" ");
  p1.end_bar_with("]");
  p1.set_foreground_color(indicator::Color::YELLOW);

  std::atomic<size_t> index1{0};
  std::vector<std::string> status_text1 = {"Rocket.exe is not responding",
                                           "Buying more snacks",
                                           "Finding a replacement engineer",
                                           "Assimilating the modding community",
                                           "Crossing fingers",
                                           "Porting KSP to a Nokia 3310",
                                           "Flexing struts",
                                           "Releasing space whales",
                                           "Watching paint dry"};

  auto job1 = [&p1, &index1, &status_text1]() {
    while (true) {
      if (p1.is_completed())
        break;
      p1.set_postfix_text(status_text1[index1 % status_text1.size()]);
      p1.set_progress(index1 * 10);
      index1 += 1;
      std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }
  };
  std::thread thread1(job1);
  thread1.join();

  //
  // PROGRESS BAR 3
  //
  indicator::ProgressBar p3;
  p3.set_bar_width(40);
  p3.set_prefix_text("Reading package list... ");
  p3.start_bar_with("");
  p3.fill_bar_progress_with("");
  p3.lead_bar_progress_with("");
  p3.fill_bar_remainder_with("");
  p3.end_bar_with("");
  p3.set_foreground_color(indicator::Color::WHITE);
  p3.hide_percentage();
  auto job3 = [&p3]() {
    while (true) {
      p3.set_prefix_text("Reading package list... " + std::to_string(p3.current()) + "% ");
      if (p3.current() + 2 >= 100)
        p3.set_prefix_text("Reading package list... Done");
      p3.tick();
      if (p3.is_completed()) {
        break;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
  };
  std::thread thread3(job3);
  thread3.join();

  //
  // PROGRESS BAR 2
  //
  indicator::ProgressBar p2;
  p2.set_bar_width(50);
  p2.start_bar_with("[");
  p2.fill_bar_progress_with("=");
  p2.lead_bar_progress_with(">");
  p2.fill_bar_remainder_with(" ");
  p2.end_bar_with("]");
  p2.set_postfix_text("Getting started");
  p2.set_foreground_color(indicator::Color::GREEN);
  auto job2 = [&p2]() {
    while (true) {
      auto ticks = p2.current();
      if (ticks > 20 && ticks < 50)
        p2.set_postfix_text("Delaying the inevitable");
      else if (ticks > 50 && ticks < 80)
        p2.set_postfix_text("Crying quietly");
      else if (ticks > 80 && ticks < 98)
        p2.set_postfix_text("Almost there");
      else if (ticks >= 98)
        p2.set_postfix_text("Done");
      p2.tick();
      if (p2.is_completed())
        break;
      std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
  };
  std::thread thread2(job2);
  thread2.join();

  //
  // PROGRESS BAR 4
  //
  std::vector<std::string> lead_spinner{"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"};
  indicator::ProgressBar p4;
  p4.set_bar_width(50);
  p4.start_bar_with("");
  p4.fill_bar_progress_with("⠸");
  p4.lead_bar_progress_with("");
  p4.fill_bar_remainder_with(" ");
  p4.end_bar_with("");
  p4.set_foreground_color(indicator::Color::CYAN);
  p4.set_postfix_text("Restoring system state");
  p4.hide_percentage();
  std::atomic<size_t> index4{0};
  auto job4 = [&p4, &index4, &lead_spinner]() {
    while (true) {
      p4.set_prefix_text("{ " + std::to_string(p4.current()) + "% } ");
      p4.lead_bar_progress_with(lead_spinner[index4 % lead_spinner.size()]);
      index4 += 1;
      if (p4.current() + 2 >= 100) {
	std::cout << std::endl;
        p4.set_foreground_color(indicator::Color::RED);
        p4.set_prefix_text("{ ERROR } ");
        p4.show_percentage();
        p4.set_postfix_text("Failed to restore system");
        p4.mark_as_completed();
        break;
      }
      p4.tick();
      std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
  };
  std::thread thread4(job4);
  thread4.join();

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  {
    //
    // GOING BACKWARDS
    //
    indicator::ProgressBar p;
    p.set_bar_width(50);
    p.start_bar_with("[");
    p.fill_bar_progress_with("■");
    p.lead_bar_progress_with("■");
    p.fill_bar_remainder_with("-");
    p.end_bar_with("]");
    p.set_progress(100);
    p.set_foreground_color(indicator::Color::WHITE);
    p.set_postfix_text("Reverting system restore");
    std::atomic<size_t> progress{100};
    auto job = [&p, &progress]() {
      while (true) {
        progress -= 1;
        p.set_progress(progress);
        if (progress == 0) {
          p.set_postfix_text("Revert complete!");
          p.mark_as_completed();
          break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
      }
    };
    std::thread thread(job);
    thread.join();
  }
  
  {
    indicator::ProgressSpinner p;    
    p.set_postfix_text("Checking credentials");
    p.set_foreground_color(indicator::Color::YELLOW);
    p.set_spinner_states({"⠈", "⠐", "⠠", "⢀", "⡀", "⠄", "⠂", "⠁"});
    auto job = [&p]() {
      while (true) {
        if (p.is_completed()) {
          p.set_foreground_color(indicator::Color::GREEN);
          p.set_prefix_text("✔");
	  p.hide_spinner();	  
          p.hide_percentage();
          p.set_postfix_text("Authenticated!");
          p.mark_as_completed();
          break;
        }
	else
	  p.tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
      }
    };
    std::thread thread(job);
    thread.join();    
  }  

  std::cout << "Compiling code\n";
  {
    indicator::ProgressSpinner p;
    p.set_prefix_text("- ");
    p.set_postfix_text("Checking project dependencies");
    p.set_foreground_color(indicator::Color::WHITE);    
    p.set_spinner_states({"▖", "▘", "▝", "▗"});
    auto job = [&p]() {
      while (true) {
        if (p.is_completed()) {
          break;
        }
	else
	  p.tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
      }
    };
    std::thread thread(job);
    thread.join();    
  }  

  std::this_thread::sleep_for(std::chrono::milliseconds(5000));

  // Show cursor
  std::cout << "\e[?25h";

  return 0;
}
