// Addon-2016 Jason, 法国迷你任务 (FMK) 最后一课
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "明显的错误。 告诉开发者。 ";
			link.l1 = "哦, 我会的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_04.wav");
			pchar.quest.FMQL_delete_guide.over = "yes";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
			if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "哦, " +GetFullName(pchar)+ "! 你看起来不一样了, 我的朋友, 而且你成功了! 你知道吗, 他们开始谈论你了? 你学得很快, 先生, 我真的为你感到骄傲。 祝你未来有更多的财富和好运! 很高兴再次见到你! ";
				link.l1 = "格雷瓜尔.瓦利尼先生, 真是奇遇! 我的微薄成就多亏了你。 也很高兴见到你! 祝你好运! ";
				link.l1.go = "greguar_exit_1";
			}
			else
			{
				dialog.text = "哦, " +GetFullName(pchar)+ "! 你看起来不一样了, 我的朋友, 而且你成功了! 你知道吗, 他们开始谈论你了? 你学得很快, 先生, 我得说你让我感到骄傲。 ";
				link.l1 = "格雷瓜尔.瓦利尼先生, 真是奇遇! 我的微薄成就多亏了你。 很高兴见到你! 让我猜猜, 你有商业提议给我? ";
				link.l1.go = "greguar_1";
			}
		break;
		
		case "greguar_1":
			dialog.text = "是的! 我确实有。 我长话短说, 时间就是金钱。 所以, 一支从巴西驶往库拉索的荷兰皇家中队, 载有战略价值的货物, 在特立尼达和大陆之间被英国人伏击。 公司的一艘长笛船设法逃脱并停泊在蛇口海岸。 他们保住了部分货物, 但没过多久 --他们遭到了当地印第安部落的袭击\n根据我的信息, 他们消灭了海岸上的所有荷兰人, 并将货物带到了他们的村庄。 印第安人还抢走了荷兰人的火器, 但也遭受了重大伤亡。 这是我们的机会! 英国人和荷兰人仍在该地区交战, 他们太忙了, 无暇顾及丢失的长笛船。 目前... 你有船和船员。 我们可以航行到那里, 登陆并消灭印第安人。 货物极其珍贵, 而且数量很大\n我已经派了一支小型探险队去侦察 --这是我能负担得起的, 还记得资金问题吗? 我有一个可靠的买家, 你可以指望我的剑和我的雇佣兵。 五五分成, 我们有一周的时间到达那里。 那么, 我的朋友, 你加入吗? ";
			link.l1 = "原谅我, 先生, 但我会拒绝。 我刚结束一次艰苦的航行, 我们没有足够的时间进行维修和招募。 即使在这个被上帝遗忘的地方, 一个人也不能拥有一切。 ";
			link.l1.go = "greguar_exit";
			link.l2 = "这听起来是一笔危险的生意, 但有可观的利润和冒险的味道。 我当然加入! 我们不要浪费时间! ";
			link.l2.go = "greguar_2";
		break;
		
		case "greguar_exit":
			dialog.text = "可惜。 那是你的决定。 祝你好运, 先生, 无论如何我都会去那里。 一个人必须尝试, 嗯? ";
			link.l1 = "祝你好运, 瓦利尼先生! ";
			link.l1.go = "greguar_exit_1";
		break;
		
		case "greguar_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 20.0);
		break;
		
		case "greguar_2":
			dialog.text = "正确的选择, 我的朋友! 你可以用额外的钱, 对吗? 顺便问一下, 你弟弟怎么样了? ";
			link.l1 = "我总是能用额外的钱。 米歇尔? 我弟弟身体健康, 只是无聊。 有时我羡慕他... 该起航了! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_Begin");
		break;
		
		case "greguar_3":
			PlaySound("Voice\English\QuestMan02.wav");
			dialog.text = "易如反掌! 这些是在与荷兰人的小规模冲突中幸存下来的新手。 我们应该深入大陆, 我的探险队一定在那里! ";
			link.l1 = "这似乎太容易了... 但现在庆祝还为时过早, 瓦利尼先生。 看看那边... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_SecondCoastBattle");
		break;
		
		case "greguar_4":
			PlaySound("Voice\English\LE\Greguar\Greguar_05.wav");
			dialog.text = "该死的红皮肤! 他们差点抓住我们! 现在我确定村子里只剩下妇女和儿童了。 出发! ";
			link.l1 = "我不确定你提到的滑膛枪... 我没看到它们... 啊, 不管了。 我们走! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_GoToJungle");
		break;
		
		case "greguar_5":
			PlaySound("Voice\English\LE\Greguar\Greguar_06.wav");
			dialog.text = "什么意思? 荷兰人和我们一定把他们都杀了! ";
			link.l1 = "";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_7":
			dialog.text = "逃跑? 你疯了吗? 我们就快到了! 你害怕一群涂漆的野蛮人? ";
			link.l1 = "";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_9":
			dialog.text = "最低劣的事情, 船长。 我要回欧洲了。 我很失望! 对你, 对这些懦夫, 对这个该死的地区! ";
			link.l1 = "... ";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			DialogExit();
			DoQuestReloadToLocation("shore18", "goto", "goto8", "FMQL_JungleExit");
		break;
		
		case "greguar_11":
			dialog.text = "呼! 我们做到了! ";
			link.l1 = "但代价是什么! 看! 我们小队几乎所有人都死了。 我们应该撤退, 格雷瓜尔, 不能保证还有更多的战士在等我们。 另外, 我们根本没有足够的人手搬运战利品。 ";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "该死! 真遗憾, 但你是对的, " +pchar.name+ ": 即使野蛮人都死了, 我们也无法在荷兰人或英国人登陆前运走货物。 我们现在必须离开! 去他妈的这个海岸! ";
			link.l1 = "... ";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_13":
			dialog.text = "呼! 我们做到了! 干得好, " +pchar.name+ "! 现在让我们去野蛮人的巢穴拿我们的奖品! 现在没有什么能阻止我们了! ";
			link.l1 = "我们应该趁英国人和荷兰人还在互相争斗的时候赶紧走。 我们走! ";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			DialogExit();
			DoQuestCheckDelay("FMQL_RunToGrabbing", 1.0);
		break;
		
		case "greguar_15":
			dialog.text = "我们做得很好, " +pchar.name+ "。 现在我们需要做的就是在不引起任何怀疑的情况下出售货物。 我有一个可靠的买家, 他会在午夜在拉曼廷湾等我们。 不要带任何军官, 在会议前避开那个地方, 客户是个非常紧张的人。 ";
			link.l1 = "生意就是生意。 货物必须出售, 而且必须安全地完成, 否则我欠潘西的债务会更高。 好的, 我会在午夜前到那里。 ";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.quest.FMQL_goods_timer.win_condition.l1 = "Timer";
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQL_goods_timer.function = "FMQL_MeetingOnLamanten";
			AddQuestRecord("FMQ_Lesson", "7");
			LAi_LocationDisableOfficersGen("Shore38", true); // may-16
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
			locations[FindLocation("Shore38")].DisableEncounters = true;
			Pchar.GenQuest.Hunter2Pause = true;
		break;
		
		case "greguar_17":
			PlaySound("Voice\English\Master_01.wav");
			pchar.quest.FMQL_goods_over.over = "yes";// 樵夫取消会议中断.
			dialog.text = "完成了。 货物已卸下, 客户在这里。 我们来谈谈。 ";
			link.l1 = "... ";
			link.l1.go = "greguar_18";
		break;
		
		case "greguar_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("FMQL_contra_"+i);
				if (i == 2) 
				{
					LAi_CharacterEnableDialog(sld);
					AddLandQuestMark(sld, "questmarkmain");
				}
			}
		break;
		
		case "greguar_19":
			dialog.text = "惊喜吧, 你们这些混蛋! ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_LookOnGuards");
		break;
		
		case "greguar_20":
			PlaySound("Voice\English\OliverTrast01.wav");
			dialog.text = "啊, 约翰尼, 真是个好家伙! 太棒了! 你有什么要说的吗, " +pchar.name+ "? ";
			link.l1 = "不。 实际上, 是的! 搞什么鬼? ! ";
			link.l1.go = "greguar_21";
		break;
		
		case "greguar_21":
			dialog.text = "别逗死人了, 先生。 你的礼貌在哪里? .. 钱在这里, 货物由我和我的朋友处理。 我没有派他们去海岸, 那会是浪费。 尤其是派约翰尼去那里。 看到那个手里拿着短炮的红皮肤家伙了吗? 你知道, 约翰尼从来都不喜欢他自己的部落。 ";
			link.l1 = "我明白了... 现在怎么办? 你也要杀了我? ";
			link.l1.go = "greguar_22";
		break;
		
		case "greguar_22":
			dialog.text = "嗯, 我应该。 但我多愁善感。 离开并拿走四分之一的现金。 货物和剩下的钱将和我一起留在这里。 别想扮演英雄, 这不是大陆的丛林。 你没有机会。 ";
			link.l1 = "你的高贵和礼貌在哪里, 格雷瓜尔? 我没料到你会这样。 我要走了, 但我不会忘记这一点。 ";
			link.l1.go = "greguar_23";
			link.l2 = "我不是在扮演英雄, 我从来没有。 我只是要杀了你们所有人! 先杀这些女士, 然后是那个拿着榴弹发射器的猿猴, 然后是你! ";
			link.l2.go = "greguar_25";
		break;
		
		case "greguar_23":
			dialog.text = "这个海滩上既没有贵族, 也没有暴徒, 先生。 只有五个人, 一门大炮和一个受害者。 这在这里经常发生, 但你做出了唯一正确的选择。 做得好。 你知道吗, 现在站在这里的可能不是你, 而是另外两个人? 他们几乎和你一样。 但你在这里, 他们不在, 我想他们会因此而灭亡。 ";
			link.l1 = "我不明白... ";
			link.l1.go = "greguar_24";
		break;
		
		case "greguar_24":
			dialog.text = "总有一天你会明白的。 他们没有上最后一课。 你上了。 不客气。 再见, 先生。 欢迎来到加勒比! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_PeaceFinal");
		break;
		
		case "greguar_25":
			dialog.text = "啊... 你不是我教过的最聪明的学生。 很好... 各人有各人的选择! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_BattleOnBeach");
		break;
		
		case "mercen":
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "时机正好! 我们刚从加勒比人的部落逃出来, 他们正朝你的方向前进, 从你的样子来看, 你已经遇到他们了。 他们的村庄就在附近, 但我们的问题才刚刚开始。 ";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper":
			dialog.text = "" +GetFullName(pchar)+ "! 你在这里! 我为什么不惊讶呢! 时机正好, 我的朋友。 我们刚从加勒比人的部落逃出来, 他们正朝你的方向前进, 从你的样子来看, 你已经遇到他们了。 ";
			link.l1 = "普罗斯珀! 我很惊讶! 又在给印第安人打洞? 希望塞莉娜没事? ";
			link.l1.go = "prosper_1";
		break;
		
		case "prosper_1":
			dialog.text = "我加入这次探险是愚蠢的, 我不知道我女儿是否还能再见到我。 塞莉娜? 嗯, 她坐在家里, 梦想着你! 马提尼克的年轻人现在已经失去任何希望了... 你知道, 我不再后悔买这把滑膛枪了。 一把可靠的火器。 值得信赖。 这也是参加另一次自杀式努力的额外理由, 尽管现在因为你的出现, 自杀的可能性小了一点。 他们的村庄就在附近, 但我们的问题才刚刚开始。 ";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper_2":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_3":
			dialog.text = "不是全部。 我们的侦察兵中枪了, 但还是设法到达了他们的巢穴。 酋长本人正带着他的卫兵来这里。 他们有荷兰滑膛枪。 他们在人数上有优势, 而且非常愤怒。 酋长是他们部落中最好的战士, 他的手下是血肉之躯的魔鬼。 我们应该现在就在这里迅速做出决定。 要么我们和他们战斗, 要么我们逃跑。 老实说, 我更喜欢后者... ";
			link.l1 = "";
			link.l1.go = "prosper_4";
		break;
		
		case "prosper_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_5":
			dialog.text = "你没见过他们, 我的好人! 这些‘野蛮人’有滑膛枪, 而且他们用得相当好。 毫无疑问, 有人在给他们上课! 所以别再叫我懦夫了! ";
			link.l1 = "让我们冷静下来, 决定该怎么做。 还有时间。 ";
			link.l1.go = "prosper_6";
		break;
		
		case "prosper_6":
			int n = 0;
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1) n++;
			}
			dialog.text = "我在听, " +pchar.name+ "。 ";
			if (n > 2 && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 30)
			{
				link.l1 = "我们会和他们战斗, 孩子们! 这座山后面有货物和钱! 我们来这里就是为了它们, 我们不会离开。 不管一群红皮肤, 即使有滑膛枪, 也无法阻止我们! 让我们埋葬这些混蛋, 完成任务! 我们有足够的人手, 有机会伏击他们。 四个人从侧翼用火迎接他们, 我们其他人在这里占据位置。 削减他们的数量, 然后消灭他们! ";
				link.l1.go = "prosper_8";
			}
			else
			{
				if (n > 0)
				{
					link.l1 = "我们会和他们战斗, 孩子们! 这座山后面有货物和钱! 我们来这里就是为了它们, 我们不会离开。 不管一群红皮肤, 即使有滑膛枪, 也无法阻止我们! 让我们埋葬这些混蛋, 完成任务! ";
					link.l1.go = "prosper_7";
				}
				else
				{
					link.l1 = "各种可能性都对我们不利。 别忘了荷兰人就在我们后面。 ";
					link.l1.go = "prosper_9";
				}
			}
		break;
		
		case "prosper_9":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_7":
			DialogExit();
			pchar.questTemp.FMQL = "battle";
			AddDialogExitQuestFunction("FMQL_PrepareAttack");
		break;
		
		case "prosper_8":
			DialogExit();
			pchar.questTemp.FMQL = "sneak";
			AddDialogExitQuestFunction("FMQL_PrepareSneakAttack");
		break;
		
		case "prosper_9x":
			dialog.text = "我们还活着, 我们回家了! 我发誓, 我受够了冒险... 接下来的几个月, 哈哈哈! 我应该去见我的女儿, 请来看我们, " +pchar.name+ "。 请小心。 ";
			link.l1 = "不保证, 普罗斯珀。 祝你好运! ";
			link.l1.go = "prosper_10";
		break;
		
		case "prosper_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		break;
		
		case "prosper_11":
			pchar.quest.FMQL_prosper_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "我警告过你, 船长, 要小心! 我对这个混蛋有怀疑。 ";
			link.l1 = "普罗斯珀! 谢谢你! 但怎么做到的? ";
			link.l1.go = "prosper_12";
		break;
		
		case "prosper_12":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) sTemp = "可怜的孩子, 尽管他是个海盗。 ";
			dialog.text = "约翰尼说得太多了。 沙滩上的那个红皮肤家伙。 他去了一家妓院, 试图勾搭一个女孩。 她们拒绝为他服务, 约翰尼生气了, 开始大喊他很快就会发财, 一旦他和他的伙伴们在丛林里杀了某个船长。 我看到了即将发生的事情, 就跑去找你的军官, 他也在镇上惹了些麻烦。 " + sTemp + " 我欠你很多, " +pchar.name+ ", 所以不需要太感谢我。 ";
			link.l1 = "不过, 还是非常感谢你, 普罗斯珀! 这里很艰难... 太艰难了。 想加入我的船员吗? 我需要像你这样的军官。 现在很难找到忠诚的人, 尤其是神枪手。 ";
			link.l1.go = "prosper_13";
		break;
		
		case "prosper_13":
			dialog.text = "不, 我的朋友。 我对我的女儿有义务。 她让我发誓不再冒险。 这是我最后一次。 该死的, 真可惜, 但我爱我的女儿胜过世界上的一切。 再见, " +pchar.name+ "。 还有... 塞莉娜一直在谈论你。 也许有一天你能来看我们? ";
			link.l1 = "谁知道呢, 也许我会... 再见, 普罗斯珀! 祝你女儿找到一个好丈夫... (自言自语) 学到了教训, 格雷瓜尔先生, 学到了教训... 他说各人有各人的选择... 我会记住这一点。 ";
			link.l1.go = "prosper_14";
		break;
		
		case "prosper_14":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // 允许保存
			AddQuestRecord("FMQ_Lesson", "15");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "contra":
			DelLandQuestMark(npchar);
			dialog.text = "你到底是谁? ";
			link.l1 = "我们有货物。 感兴趣吗? ";
			link.l1.go = "contra_1";
		break;
		
		case "contra_1":
			dialog.text = "哈。 非常感兴趣。 我的客户特别感兴趣。 有什么收获? ";
			link.l1 = "" + FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl)) + "的铁木, " + FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk)) + "的船用丝绸, " + FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope)) + "的绳索和" + FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil)) + "的树脂。 ";
			link.l1.go = "contra_2";
		break;
		
		case "contra_2":// Addon 2016-1 Jason 海盗系列
			iTotalTemp = 2200*sti(pchar.questTemp.FMQL.Sanl)+1600*sti(pchar.questTemp.FMQL.Silk)+1000*sti(pchar.questTemp.FMQL.Rope)+900*sti(pchar.questTemp.FMQL.Oil);
			dialog.text = "很好。 每块铁木2200比索, 树脂900比索, 船用丝绸1600比索, 绳索1000比索。 我们这里有什么... 嗯-嗯。 " + iTotalTemp + "比索。 成交? ";
			link.l1 = "成交! ";
			link.l1.go = "contra_3";
		break;
		
		case "contra_3":
			LAi_Fade("", "");
			FMQL_CreateGuidesWarriors();
			dialog.text = "太棒了! 再带更多来。 荷兰人对红皮肤从不吝啬... 这些客人是谁? 搞什么鬼? ! ";
			link.l1 = "";
			link.l1.go = "contra_4";
		break;
		
		case "contra_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_19";
			AddMoneyToCharacter(sld, iTotalTemp);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQL_beach":
			pchar.quest.FMQL_pirate_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			dialog.text = "是的, 船长。 我有理由喝得酩酊大醉。 ";
			link.l1 = "你? 怎么回事? ! ";
			link.l1.go = "FMQL_beach_1";
		break;
		
		case "FMQL_beach_1":
			dialog.text = "对不起, 船长。 在和印第安人的混乱之后, 我不得不喝了一两杯。 有一个女孩, 我花了一百比索开了个房间, 然后她... 她... ";
			link.l1 = "什么? 她抢了你? ";
			link.l1.go = "FMQL_beach_2";
		break;
		
		case "FMQL_beach_2":
			sld = CharacterFromID("FMQL_Prosper");
			dialog.text = "不! 她爱上我了! 该死的, 我应该从那里逃跑的! 但后来你的朋友出现了, 对我大喊大叫, 说这个混蛋, 你以前的同伴, 想骗你并杀了你。 ";
			if (LAi_GetCharacterHP(sld) > 0)
			{
				link.l1 = "干得好, 普罗斯珀... ";
				link.l1.go = "FMQL_beach_3";
			}
			else
			{
				link.l1 = "普罗斯珀... 我很抱歉。 我会照顾你的女儿。 学到了教训, 格雷瓜尔先生... 你说什么? 各人有各人的选择? 我应该记住这一点。 ";
				link.l1.go = "FMQL_beach_3";
			}
		break;
		
		case "FMQL_beach_3":
			dialog.text = "我们走吗, 船长? ";
			link.l1 = "是的。 感谢你的服务。 远离酒杯, 我们会把你从那个美人身边救出来。 我们走。 ";
			if (CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) link.l1.go = "FMQL_beach_5";
			else link.l1.go = "FMQL_beach_4";
		break;
		
		case "FMQL_beach_4": // 普罗斯珀活着
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload_sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			sld = CharacterFromID("FMQL_Prosper");
			sld.Dialog.currentnode = "prosper_11";
			sld.MusketerDistance = 20;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "FMQL_beach_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
			else
			{
				pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
				pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
				pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
				pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
			}
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // 允许保存
			AddQuestRecord("FMQ_Lesson", "10");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}