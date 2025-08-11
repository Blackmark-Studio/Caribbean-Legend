// Филипп де Пуанси - генерал-губернатор французских колоний
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyFox"))
			{
				dialog.text = "你好, " +pchar.name+ "。 进来吧, 我已经得知消息了。 ";
				link.l1 = "得知消息? 可能有些误会, 大人。 我是来汇报您交代的任务已成功完成的, 但我看您似乎心情不太好。 ";
				link.l1.go = "PZ_PoincyAngry1";
				DeleteAttribute(pchar, "questTemp.Terrapin");
				DeleteAttribute(pchar, "questTemp.Terrapin_KathyFox");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done")
			{
				dialog.text = "很高兴见到你, " +pchar.name+ "。 我已得知你的成就, 最重要的是, 你成功完成了任务! 你展现出了最好的一面, 我很高兴没有看错你。 ";
				link.l1 = "现在我能从您这里收到释放我兄弟的书面命令吗? ";
				link.l1.go = "serve";
				AddCharacterExpToSkill(pchar, "Sneak", 500);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && CheckAttribute(pchar, "questTemp.Sharlie.LevasserDied"))
			{
				dialog.text = "很高兴见到你, " +pchar.name+ "。 我听说了你的事迹, 最重要的是, 你的任务完成了! 不过我得说, 我本期待一个比正面进攻更聪明的主意。 为死去的法国士兵感到惋惜。 \n但战争就是战争, 总会有伤亡。 你履行了职责, 我很高兴没有看错你。 ";
				link.l1 = "现在我能从您这里收到释放我兄弟的书面命令吗? ";
				link.l1.go = "serve";
				DeleteAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga");
				DeleteAttribute(pchar, "questTemp.Sharlie.LevasserDied");
				break;
			}
			// Jason НСО 
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && GetCharacterIndex("Noel") == -1 && pchar.questTemp.Patria != "epizode_12_barondie" && pchar.questTemp.Patria != "epizode_12_baronfail" && pchar.questTemp.Patria != "epizode_12_baronkilled" && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "很高兴见到你, 查尔斯。 首先, 请允许我祝贺你成功完成了保护圣皮埃尔殖民地免受西班牙侵略者攻击的复杂任务。 干得漂亮, 我的朋友! ";
					link.l1 = "谢谢您, 骑士先生。 ";
					link.l1.go = "patria";
					Patria_SetInspector();
				}
				else
				{
					dialog.text = "很高兴见到你, 查尔斯。 首先, 请允许我祝贺你成功完成了保护圣皮埃尔殖民地免受西班牙侵略者攻击的复杂任务。 干得漂亮, 我的朋友! 我再给你一个与海军合作的机会。 法国急需像你这样的军官。 我希望这次你能更明智些... 拿着这份委任状吧, 查尔斯.德.莫尔船长! ";
					link.l1 = "谢谢您, 骑士先生。 我很乐意帮助国家, 并渴望继续为它服务! ";
					link.l1.go = "patria";
					if (!CheckCharacterItem(pchar, "suit1")) GiveItem2Character(pchar, "suit1");
					GiveItem2Character(pchar, "patent_fra");
					EquipCharacterbyItem(pchar, "patent_fra");
					Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
					Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
					ChangeCharacterNationReputation(pchar, FRANCE, 100);
					Patria_SetInspector();
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (!CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "查尔斯, 你让我失望了。 由于你不明智的行为, 你失去了委任状和皇家海军的军衔。 没有进一步合作的余地了。 解散。 ";
					link.l1 = "嗯... ";
					link.l1.go = "patria_patentfail";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_1_return")
				{
					dialog.text = "很高兴见到你, 查尔斯。 汇报吧! ";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "任务完成了, 已收到圣何塞殖民地的赎金。 但有个坏消息: 在与‘辉煌’堡垒的战斗中, 它沉没了。 我警告过船长要小心, 但他不听我的, 然后... ";
						link.l1.go = "patria_8_1";
					}
					else
					{
						link.l1 = "任务完成了, 已收到圣何塞殖民地的赎金。 ";
						link.l1.go = "patria_8";
					}
					break;
				}
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(!IsUniformEquip())
				{
					dialog.text = "先生, 从今天起, 只允许你穿着合适的制服进入我的大厅! ";
					link.l1 = "... ";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_2_return" && IsUniformEquip())
				{
					dialog.text = "男爵, 船长! 很高兴见到你们! ";
					link.l1 = "任务完成了, 骑士先生。 ";
					link.l1.go = "patria_14";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_3_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting() + ", 船长。 你带来了什么消息? ";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "西班牙人确实计划进攻太子港。 在伊斯帕尼奥拉岛西端, 我们发现了一支强大的敌方中队。 它被彻底摧毁了。 然而, ‘辉煌’号沉没了。 ";
						link.l1.go = "patria_26_1";
					}
					else
					{
						link.l1 = "西班牙人确实计划进攻太子港。 在伊斯帕尼奥拉岛西端, 我们发现了一支强大的敌方中队。 它被彻底摧毁了。 ";
						link.l1.go = "patria_26";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_4_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting() + ", 查尔斯。 斯特伊弗桑特先生怎么样? ";
					link.l1 = "一切都好, 骑士先生。 运送成功, 这是给您信的回复。 ";
					link.l1.go = "patria_31";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_5_return" && IsUniformEquip())
				{
					dialog.text = "查尔斯, 男爵... 你们已经回来了? ";
					link.l1 = "... ";
					link.l1.go = "patria_36";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_6_return" && IsUniformEquip())
				{
					dialog.text = "我不喜欢你皱着眉头, 查尔斯。 斯特伊弗桑特说了什么, 汇报! ";
					if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win") link.l1 = "他原话是: ‘告诉骑士先生, 他不再负责圣马丁了。 受够他了。 至于宗主国的视察 —让他自己想办法, 德庞西向来擅长颠倒黑白。 ’宣布完这条消息后, 先生就把我赶出了官邸。 我们的谈判就这么结束了。 ";
					else link.l1 = "嗯, 他是这么说的: ‘你的君主最近在圣马丁太贪婪了, 是时候抑制他那永不满足的欲望了。 ’说完, 他试图逮捕我。 我不得不拔刀杀出一条路回到船上。 荷兰的外交就是这样。 ";
					link.l1.go = "patria_43";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_go" && IsUniformEquip())
				{
					dialog.text = "船长, 我们一直在等你。 我向男爵解释了目前的情况, 他完全支持我的决定。 荷兰人要为他们的傲慢付出代价。 ";
					link.l1 = "那么这是战争了? ";
					link.l1.go = "patria_51";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_continue" && IsUniformEquip() && pchar.location.from_sea == "Charles_town") // add-7
				{
					Patria_HunterShipChecker();
					if (CheckAttribute(pchar, "questTemp.Patria.Hunter.GiveShip"))
					{
						dialog.text = "那么, 我的朋友, 我看到你俘获了东印度公司的船和货物。 太好了! ";
						link.l1 = "我把船交给您, 请给港口官员下达命令, 骑士先生。 ";
						link.l1.go = "patria_55";
					}
					else
					{
						dialog.text = "你有什么问题吗, 查尔斯? ";
						link.l1 = "目前没有, 先生。 那我就告辞了... ";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8" && IsUniformEquip())
				{
					dialog.text = "你终于到了, 船长! 圣克里斯托弗有紧急情况! ";
					link.l1 = "是敌方中队吗? ";
					link.l1.go = "patria_59";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_wait" && IsUniformEquip() && GetCompanionQuantity(pchar) < 5)
				{
					dialog.text = "你准备好接收我们的信使单桅帆船了吗? ";
					link.l1 = "准备好了。 ";
					link.l1.go = "patria_64";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_return")
				{
					dialog.text = "德.莫尔船长, 多伊利爵士! 很高兴见到你们! 全城的人都看到你们教训了那些觊觎我们殖民地的西班牙-荷兰恶棍! ";
					link.l1 = "这是我的职责, 骑士先生。 ";
					link.l1.go = "patria_66";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_start" && IsUniformEquip())
				{
					dialog.text = TimeGreeting() + ", 查尔斯。 我们开始吧, 好吗? ";
					link.l1 = "当然, 骑士先生。 我就是为此而来的。 ";
					link.l1.go = "patria_69";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_return" && IsUniformEquip())
				{
					dialog.text = "我很高兴在我的办公室欢迎法国皇家海军的舰队副司令! 是的, 我的朋友, 你没听错: 我亲自签署了任命你的命令。 正式来说, 它还需要在法国批准, 但你不必怀疑这会发生。 恭喜你! ";
					link.l1 = "我为国家服务! ";
					link.l1.go = "patria_76";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_10_return" && IsUniformEquip())
				{
					if (GetQuestPastDayParam("questTemp.Patria.Curacao.Date") < 30) sTemp = "很快就会准备好并且"; // 根据到达所需时间
					else sTemp = "已经准备好并且";
					dialog.text = "你在努力中取得成功了吗? 多伊利上校满意吗? ";
					link.l1 = "一切都很顺利, 骑士先生。 斯特伊弗桑特的商队被抓获, 所有奴隶都被带到了牙买加, 上校的中队" + sTemp + "正在前往库拉索的路上。 ";
					link.l1.go = "patria_81";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_11_return" && IsUniformEquip())
				{
					dialog.text = "荣耀属于胜利者! 恭喜你, 恭喜你, 我的朋友! 你总是让人惊叹。 ";
					link.l1 = "谢谢您, 骑士先生。 斯特伊弗桑特受到了惩罚, 准备支付赔偿金, 和平得以恢复, 现在圣马丁完全属于法国了。 ";
					link.l1.go = "patria_85";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_continue")
				{
					dialog.text = "那么, 我的朋友, 很高兴再次见到你。 你休息得好吗? ";
					link.l1 = "是的, 骑士先生。 这是一次非常必要的休息... 您提到了一些微妙的事情? ";
					link.l1.go = "patria_88";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronalive")
				{
					dialog.text = "我的朋友, 你一定是个巫师! 你完成了一项壮举! 我们的男爵不再想在这里成立贸易公司了。 ";
					link.l1 = "我相信他现在唯一的愿望就是回到巴黎。 ";
					link.l1.go = "patria_103";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_barondie")
				{
					dialog.text = "查尔斯, 你听说男爵的事了吗? 他被海盗抓走了... ";
					link.l1 = "是的, 骑士先生。 唉, 男爵死了。 我对此非常确定。 ";
					link.l1.go = "patria_112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronfail")
				{
					dialog.text = "查尔斯, 你的进展如何? 我听说男爵登上了你的船... ";
					link.l1 = "是的, 骑士先生。 他在船上, 我正在努力说服他, 但是... 他死于发烧。 ";
					link.l1.go = "patria_x112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronkilled")
				{
					dialog.text = "查尔斯, 你的进展如何? 我听说男爵登上了你的船... ";
					link.l1 = "是的, 骑士先生。 他在船上, 我正在努力说服他, 但是... 他在战斗中牺牲了。 ";
					link.l1.go = "patria_y112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronwin")
				{
					dialog.text = "我的朋友, 你一定是个巫师! 你完成了一项壮举! 我们的男爵不再想在这里成立贸易公司了。 ";
					link.l1 = "他可能现在正前往巴黎。 ";
					link.l1.go = "patria_117";
					break;
				}
				dialog.text = "你有什么问题吗, 查尔斯? ";
				link.l1 = "目前没有, 先生。 那我就告辞了... ";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "你想要什么? 先生? ";
			link.l1 = "没什么要紧的, 只是礼节性拜访。 我现在就离开... ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// 游戏开始时在监狱中
		case "Puancie_Jail":
			dialog.text = "日安, 查尔斯。 请允许我自我介绍: 我是菲利普.德.波因西, 我... ";
			link.l1 = "你到底为什么把我关进监狱? 这太不像话了! 我是法国贵族, 而且... ";
			link.l1.go = "Puancie_Jail_1";			
			// belamour传奇版 -->
			link.l2 = "好... 下午好? 先生, 这笑话真有趣。 你怎么知道我是谁? ";
			link.l2.go = "Puancie_Jail_1a";	
		break;
		
		case "Puancie_Jail_1a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			dialog.text = "年轻人, 我请求你不要打断我! 你正在和加勒比群岛法属殖民地的总督说话! 我可以原谅你傲慢的语气, 只是因为你不可能知道站在你面前的是谁。 但我建议你以后要更克制一些。 ";
			link.l1 = "嗯... 对不起, 大人。 ";
			link.l1.go = "Puancie_Jail_2";
		break;
		
		case "Puancie_Jail_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			// < —传奇版
			dialog.text = "听我说, 年轻人, 别打断我! 你在和加勒比群岛法属殖民地的总督说话! 我原谅你的语气, 只是因为你不知道在和谁说话。 但我建议你以后要更克制些。 ";
			link.l1 = "嗯... 请原谅, 大人。 ";
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_2":
			dialog.text = "这就对了。 现在, 关于你之前的问题 —你被误认为是西班牙间谍而被捕, 直到你的身份查清为止。 该死的卡斯蒂利亚人最近变得更活跃了, 因此我下令拘留所有可疑人员。 \n但我们现在知道你是谁了 —你确实是查尔斯.德.莫尔, 米歇尔.德.蒙佩的弟弟, 我亲自来这里是为了释放你。 而你却像个小男孩一样对我大喊大叫! ";
			link.l1 = "再次请您原谅, 大人。 我现在自由了吗? ";
			link.l1.go = "Puancie_Jail_3";			
		break;
		
		case "Puancie_Jail_3":
			dialog.text = "是的, 你自由了。 但在警卫打开你的牢房之前, 我想和你私下谈谈。 你知道吗, 你的哥哥, 马耳他骑士团最杰出的战士之一, 已经被捕并被看守起来了? ";
			link.l1 = "我只知道我哥哥有麻烦了, 他需要帮助。 这就是我从巴黎来这里的原因。 ";
			link.l1.go = "Puancie_Jail_4";			
		break;
		
		case "Puancie_Jail_4":
			dialog.text = "很高兴听到你这么说。 我想让你知道, 德.蒙佩先生处境很危险。 我有充分的理由怀疑他滥用职权。 挪用财产和作伪证。 但你可以帮助他。 ";
			link.l1 = "先生, 你能告诉我更多吗? 我不明白, 米歇尔曾是骑士团的骄傲, 而且... ";
			link.l1.go = "Puancie_Jail_5";			
		break;
		
		case "Puancie_Jail_5":
			dialog.text = "我以前也这么想。 我们都这么想! 但他最近的行为让我们... 对他是否忠于骑士团产生了怀疑, 所以他被逮捕了。 米歇尔会亲自告诉你细节。 他会解释你如何帮助他应对指控, 避免身败名裂。 ";
			link.l1 = "我哥哥现在在哪里? 你告诉我他在监狱里, 但我在这里没看到他... ";
			link.l1.go = "Puancie_Jail_6";			
		break;
		
		case "Puancie_Jail_6":
			dialog.text = "年轻人, 我什么时候说过他被监禁了? 你到底有没有在听? ! 我说的是他被逮捕了! 这不是一回事。 米歇尔.德.蒙佩被关押在圣皮埃尔的地下基地, 那是马耳他骑士团的财产。 \n我允许你不受任何限制地访问该基地, 并根据需要尽可能频繁地与你哥哥交谈。 骑士团的军官和士兵都知道我的指示, 他们不会阻止你。 ";
			link.l1 = "那个地下基地在哪里? ";
			link.l1.go = "Puancie_Jail_7";			
		break;
		
		case "Puancie_Jail_7":
			dialog.text = "当然是在这里, 圣皮埃尔。 找到当地的监狱, 进入有骑士团标志的门。 下楼到地下室二层的弹药库。 蒙佩先生会在那里。 但别担心: 出狱后, 会有人迎接你并护送你到你哥哥那里 —我已经安排好了一切... 就这样。 我希望我们能再次见面, 查尔斯。 警卫! ";
			link.l1 = "请等一下, 大人! 那我的... 物品呢? 我的剑和其他东西? ";
			link.l1.go = "Puancie_Jail_8";			
		break;
		
		case "Puancie_Jail_8":
			dialog.text = "你的物品被没收, 用于偿还你哥哥的债务。 再见, 德.莫尔先生。 ";
			link.l1 = "搞什么鬼... ";
			link.l1.go = "Puancie_Jail_9";			
		break;
		
		case "Puancie_Jail_9":
			DialogExit();
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Sharlie_GoFromPrison", 3.5);
			NextDiag.CurrentNode = "First time";
			locCameraFromToPos(-11.09, 0.65, 3.05, true, -12.59, 0.09, -4.66);
		break;
		
		// 归还钱款
		case "saga":
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", false);
			dialog.text = "啊哈, 查尔斯.德.莫尔本人! 很高兴见到你。 我想你是来这里和我讨论你哥哥的命运的吧? ";
			link.l1 = "我准备偿还米歇尔.德.蒙佩欠骑士团和您个人的债务。 ";
			if (sti(pchar.money) >= 1000000) link.l1.go = "saga_1";
			else link.l1.go = "saga_exit";			
		break;
		
		case "saga_exit":
			dialog.text = "嗯... 但钱在哪里? 年轻人, 你的幽默感很奇怪, 我不明白。 ";
			link.l1 = "请原谅, 骑士先生。 我把钱忘在船上的储物柜里了。 我很快就回来。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_repeat";	
		break;
		
		case "saga_repeat":
			dialog.text = "你把钱带来了吗, 查尔斯? ";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "当然! 我希望这笔钱能完全偿还你所有的花费。 ";
				link.l1.go = "saga_1";
			}
			else
			{
				link.l1 = "还没有... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_repeat";
			}		
		break;
		
		case "saga_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Charles");
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = "太好了! 我会收下的。 查尔斯, 你展现了自己最好的一面! ";
			link.l1 = "我什么时候能拿到释放米歇尔.德.蒙佩的命令? ";
			link.l1.go = "saga_2";			
		break;
		
		case "saga_2":
			dialog.text = "别着急, 年轻人。 我只能说, 你冒着生命危险偿还债务。 保护家人, 这让我很敬佩。 在如今这个时代, 这种高尚的品格很少见... 但在这个悲伤的故事中, 金钱并不是主要部分。 你哥哥是在承担一项非常微妙的任务的条件下才得到这么一大笔钱的。 \n米歇尔.德.蒙佩作为一名忠实的天主教徒, 曾对着圣经起誓, 他会找到惩罚一个傲慢的异教徒的方法, 并为了骑士团和神圣教会的荣耀, 恢复被他破坏的正义... ";
			link.l1 = "但他被捕了, 就无法信守诺言! 如果你释放他, 我们俩一起完成任务的速度会比我一个人快得多。 ";
			link.l1.go = "saga_3";			
		break;
		
		case "saga_3":
			dialog.text = "你看, 我的朋友, 你哥哥给了我一个不信任他品德的充分理由。 无法保证他不会逃跑并违背誓言。 所以如果你想为他洗清所有指控 —就由你自己来履行这个誓言。 德.蒙佩先生会告诉你细节。 ";
			link.l1 = "嗯... 我没想到会这样。 但你没给我留下任何选择。 我和我哥哥谈过之后会做出最终决定。 ";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			dialog.text = "我开始真的喜欢你了, 查尔斯。 也许有一天, 我们会成为朋友。 无论如何, 这是我释放你哥哥的最后条件。 我向你保证, 如果你完成了你哥哥没有完成的事情, 你家族的声誉将不会受到损害。 而且你将来可以指望我的友谊。 ";
			link.l1 = "我完全理解了。 再见! ";
			link.l1.go = "saga_5";			
		break;
		
		case "saga_5":
			DialogExit();
			pchar.questTemp.Saga = "mishelle";//传奇 - 开始
			AddQuestRecord("Sharlie", "21");
			NextDiag.CurrentNode = "First time";
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		break;
		
		case "serve":
			dialog.text = "别担心, "+pchar.name+", 我会信守诺言。 你哥哥会被释放, 所有指控都会被撤销。 你家族的声誉现在没有危险了。 我想说, 这全是你的功劳, 只属于你。 你父亲会为养育了这样一个儿子而感到骄傲。 ";
			link.l1 = "谢谢您的夸奖, 骑士先生。 我想我可以立即前往马提尼克岛了吧? ";
			link.l1.go = "serve_1";	
			Island_SetReloadEnableGlobal("Tortuga", true);
			CloseQuestHeader("Terrapin");
			SetFunctionTimerCondition("Terrapin_SetFontene", 0, 0, 5, false); // 计时器
		break;
		
		case "serve_1":
			dialog.text = "等一下, 我的朋友。 我希望我可以称你为朋友, 对吗? 我想亲自表达我的感激之情。 自从你来到这里, 我一直在关注你的进展, 我知道你大部分的事迹。 你在加勒比地区已经声名鹊起, 毫无疑问, 你在社会的某些特定阶层中也广为人知和尊敬。 法国需要像你这样的人\n"+GetFullName(pchar)+"船长! 凭借国王陛下赋予我的权力, 我荣幸地向你授予皇家海军上尉的任命书, 并让你指挥法国海军的一艘轻型护卫舰'格里芬多'号! \n由于你的缘故, 前船长德.方特诺将担任托尔图加的总督, 而加勒比地区最好的轻型护卫舰需要一位船长。 你接受这个提议吗? ";
			link.l1 = "很有趣。 作为回报, 我需要做什么? ";
			link.l1.go = "serve_2";		
		break;
		
		case "serve_2":
			dialog.text = "只是一点小事。 你捕获物的十分之一, 有时还要完成一些微妙的任务。 我在等待你的决定。 ";
			link.l1 = "没有人会拒绝这样的提议, 大人! 为国家服务是我的荣幸! ";
			link.l1.go = "serve_3";
			link.l2 = "请原谅我的不客气, 但我现在不得不拒绝你的提议。 我的家庭事务可能需要我立即回国。 ";
			link.l2.go = "serve_no";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "serve_no":
			ChangeCharacterComplexReputation(pchar, "fame", 7);
			dialog.text = "真遗憾。 我本希望你会同意... 但无论如何, 我不得不请你再帮一个忙, 实际上这也符合你的利益。 马提尼克岛正在遭受攻击。 港口和城市本身都在激烈战斗。 \n唉, 除了你, 我没有人可以派去帮助驻军。 我以祖国爱国者的身份请求你, 尽一切必要手段击退进攻。 我希望你有足够的资源做到这一点。 \n此外, 你的哥哥还在那里, 你可以救他的命。 ";
			link.l1 = "我哥哥有危险? 我这就去! ";
			link.l1.go = "serve_exit";			
		break;
		
		case "serve_3":
			dialog.text = "多么可敬的话语! 真正的军人和祖国忠诚之子的话语! 恭喜你, "+GetFullName(pchar)+"先生。 你被授予法国海军指挥官的军衔。 接受我给你的这套制服吧。 自豪地穿上它, 不辜负它! ";
			link.l1 = "我为国家服务! ";
			link.l1.go = "serve_4";	
			locCameraFromToPos(-2.63, 2.20, -4.96, true, 2.64, 0.22, -4.96);
			npchar.greeting = "puancie_1";			
		break;
		
		case "serve_4":
			dialog.text = "轻型护卫舰'格里芬多'号现在由你指挥。 从这一刻起, 这艘出色的船属于你了。 利用它的优良性能, 为陛下的荣耀和加强法国在加勒比群岛的影响力服务吧! ";
			link.l1 = "马上! ";
			link.l1.go = "serve_5";
			LAi_Fade("SharlePutsSuit", "");
		break;
		
		case "serve_5":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "但你的中队已经太大了, 所以等你处理掉一艘船后再来取'格里芬多'号吧。 ";
				link.l1 = "好的。 我会的。 ";
				link.l1.go = "serve_wait";		
			}
			else
			{
				dialog.text = "除了这艘船, 你还会得到它的代理船长和船员。 如果你愿意, 你可以让他留在你的指挥下, 或者把他从船上调走, 我们会给他找另一个职位。 ";
				link.l1 = "明白了! ";
				link.l1.go = "serve_6";
			}
		break;
		
		case "serve_6":
			dialog.text = "但我有个坏消息要告诉你, 船长。 我刚得知马提尼克岛正在遭受攻击。 港口和城市本身都在激烈战斗。 \n唉, 除了你, 我没有人可以派去帮助驻军。 这是你的第一个任务: \n 保护圣皮埃尔! 此外, 你的哥哥还在那里, 你可以救他的命。 ";
			link.l1 = "我哥哥有危险? 我这就去! ";
			link.l1.go = "serve_7";
		break;
		
		case "serve_7":
			DialogExit();
			locCameraTarget(PChar);
			locCameraFollow();
			CreateGriffondor();
			sld = characterFromId("GriffOfficer");
			SetCharacterRemovable(sld, true);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "24");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
			pchar.questTemp.GoldenGirl_Block = true;	// 禁止任务《比黄金更珍贵》
		break;
		
		case "serve_wait":
			DialogExit();
			NextDiag.CurrentNode = "serve_shipcheck";
		break;
		
		case "serve_shipcheck":
			dialog.text = "你准备好指挥‘狮鹫号’了吗? ";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "还没有, 我正在重新部署舰队中的船只... ";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "准备好了。 ";
				link.l1.go = "serve_5a";
			}
			NextDiag.TempNode = "serve_wait";
		break;
		
		case "serve_5a":
			dialog.text = "太好了! 随船你将获得代理船长和全体船员。 如果你愿意, 可以让他继续留任, 或者将他调离, 我们会为他安排其他职位。 ";
			link.l1 = "明白了! ";
			link.l1.go = "serve_6";
		break;
		
		case "serve_exit":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "23");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
		break;
		
		// Jason 国家任务
		case "patria":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince"); // Rebbebion, 删除海盗命令以防万一
			DelCharleePrince("");
			dialog.text = "而这仅仅是开始, 先生! 以你的军事天赋, 我相信你定会成就非凡! 我已经为一位优秀的海军军官准备了另一项任务, 相信你同样能出色完成。 此外, 这与你之前的任务直接相关。 ";
			link.l1 = "我洗耳恭听, 先生。 ";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "但首先让我介绍一下进入我办公室的这位先生。 这位是诺埃尔.福盖男爵, 法国西印度贸易公司的名誉会员。 他抵达群岛是为了视察我们的殖民地, 以扩展甘蔗和其他作物的种植组织, 并探索在我们地区发展贸易关系的可能性。 巴黎方面指示我们在这些事务上给予他各种支持和协助, 我们无疑会照办。 男爵, 我向你介绍查尔斯.德.莫尔先生, 法国皇家海军最有才华的船长之一... ";
			link.l1 = "";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			DialogExit();
			sld = characterFromId("Noel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_3":
			dialog.text = "那么, 查尔斯, 在我和男爵视察圣克里斯托弗期间, 我给你分配以下任务。 没有人可以攻击法国定居点而逍遥法外, 西班牙人虽然已经因侵略马提尼克岛而受到教训, 但他们必须用金钱为自己的罪行买单, 并赔偿给殖民地造成的损失。 \n与法国男爵一同抵达的有一支强大的舰队, 其中包括一艘装备66门加农炮的‘辉煌’号战舰。 该舰船长是一位经验丰富的水手, 但他首次来到加勒比海, 因此他将听从你的指挥。 你将与‘辉煌’号一起前往西班牙属特立尼达岛海岸, 要求西班牙人为袭击圣皮埃尔支付三十万比索的赔偿金。 ";
			link.l1 = "骑士先生, 你真的认为西班牙人会同意吗? ";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "我确信他们会 —在‘辉煌’号和你的舰队将圣何塞堡炸成废墟之后。 我认为不需要登陆部队和夺取城市, 也不会有士兵伤亡。 无需警告就发动攻击, 摧毁堡垒, 然后向指挥官发出信号, 表示你想提出条件。 在这种情况下, 西班牙人将无处可逃, 他们会选择付钱。 如果你处在那个失去防御的城市总督的位置, 你会怎么做? ";
			link.l1 = "嗯, 似乎有道理, 骑士先生。 ";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "你清楚自己的任务了吗? ";
			link.l1 = "是的, 阁下。 ";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			// belamour传奇版修复带步枪制服的检查
			if(IsUniformEquip())
			{
				dialog.text = "那就行动吧。 这是给‘辉煌’号船长的信, 确认你的指挥权。 这艘优秀的战舰和训练有素的船员现在由你指挥。 查尔斯, 别忘了你现在为法国服务, 建议你穿着制服与我这样的官员进行适当沟通。 制服非常适合你。 祝你好运, 德.莫尔船长! ";
			}
			else
			{
				dialog.text = "那就行动吧。 这是给‘辉煌’号船长的信, 确认你的指挥权。 这艘优秀的战舰和训练有素的船员现在由你指挥。 哦, 还有查尔斯: 我命令你穿上船长制服! 首先, 法国皇家海军军官看起来像商人或私掠者是不合适的, 其次, 你的制服非常适合你。 立即执行, 德.莫尔船长! ";
			}
			link.l1 = "";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "1");
			pchar.questTemp.Patria = "epizode_1";
			Patria_SetEcliaton();
			pchar.questTemp.GoldenGirl_Block = true;	// 禁止"比黄金更珍贵"任务
		break;
		
		case "patria_8_1":
			if (sti(pchar.money) >= 300000) AddMoneyToCharacter(pchar, -300000);
			else pchar.questTemp.Patria.NoMoney = "true";
			dialog.text = "‘辉煌’号沉没了? 查尔斯, 这是一场灾难! 部长现在会怎么说? 你让我失望了, 查尔斯! 我原以为可以依靠你的经验, 而你... 唉, 你要为此负责。 我会写一份报告, 你最好消失一段时间。 你在皇家海军的服役结束了。 ";
			link.l1 = "嗯... 对不起, 先生。 看来我确实最好消失一两个月, 直到部长平息怒火。 再见, 再次为让你失望深感抱歉。 ";
			link.l1.go = "patria_8_2";
		break;
		
		case "patria_8_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "8");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// 允许"比黄金更珍贵"任务
			RemoveItems(pchar, "patent_fra", 1);
			if (CheckAttribute(pchar, "questTemp.Patria.NoMoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -20);
				ChangeCharacterNationReputation(pchar, FRANCE, -30);
				DeleteAttribute(pchar, "questTemp.Patria.NoMoney");
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -5);
				ChangeCharacterNationReputation(pchar, FRANCE, -5);
			}
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // 移除计时器
		break;
		
		case "patria_8":
			if (sti(pchar.money) >= 300000)
			{
				dialog.text = "完美! ";
				link.l1 = "给您, 这三十万比索。 ";
				link.l1.go = "patria_9";
			}
			else
			{
				dialog.text = "完美, 但钱在哪里, 查尔斯? ";
				link.l1 = "呃, 在船上的箱子里, 我马上送来! ";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_8_3":
			DialogExit();
			npchar.dialog.currentnode = "patria_8_4";
		break;
		
		case "patria_8_4":
			dialog.text = "那么, 查尔斯, 你从特立尼达带来赎金了吗? ";
			if (sti(pchar.money) >= 300000)
			{
				link.l1 = "是的, 先生。 给您。 ";
				link.l1.go = "patria_9";
			}
			else
			{
				link.l1 = "我马上就带来! ";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_9":
			AddMoneyToCharacter(pchar, -300000);
			dialog.text = "我对你很满意, 查尔斯, 你从未让我失望。 这项任务并不容易, 你将从赎金中获得五万比索作为奖励。 拿去吧, 这都是你的。 ";
			link.l1 = "谢谢您, 骑士先生。 ";
			link.l1.go = "patria_10";
		break;
		
		case "patria_10":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "你已经有了一项新任务。 福盖先生完成了对圣克里斯托弗的视察, 现在希望访问我们的北部殖民地。 我请你带男爵前往托尔图加和伊斯帕尼奥拉岛, 在他的事务上提供各种帮助, 并满足他的要求。 清楚了吗, 查尔斯? ";
			link.l1 = "当然, 骑士先生。 ";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "男爵时间紧迫, 所以我请你不要分心处理其他事务, 也不要将行程拖延超过两个月。 ";
			link.l1 = "当然, 先生。 岛屿之间的航行不会花费太多时间, 除非福盖先生在殖民地的事务耗时。 ";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "很好。 那么男爵将乘坐你的船旅行。 把你最好的船舱给他。 ";
			link.l1 = "当然, 骑士先生! ";
			if(IsUniformEquip()) link.l1.go = "patria_13";
			else link.l1.go = "patria_13_1";
		break;
		
		case "patria_13_1":
			dialog.text = "还有一件事, 查尔斯: 你又没穿军官制服! 这是你最后一次警告。 从现在起, 我要求你只穿制服来见我, 否则我不会听你说话。 你在执勤, 纪律至上, 尤其是海军军官的仪表! ";
			link.l1 = "请原谅, 骑士先生。 不会再发生了。 ";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "9");
			pchar.questTemp.Patria = "epizode_2";
			Patria_VisiterBegin();
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // 移除计时器
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_14":
			sld = characterFromId("Noel");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
			dialog.text = "我毫不怀疑你的旅程会成功。 有来自托尔图加或太子港的消息吗? ";
			link.l1 = "... ";
			link.l1.go = "patria_15";
		break;
		
		case "patria_15":
			DialogExit(); // 切换至巡查官
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_16";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//锁定界面
		break;
		
		case "patria_16":
			dialog.text = "";
			link.l1 = "是的, 骑士先生, 我带来了消息, 但并非好消息。 首先, 太子港总督确信西班牙人正在准备进攻殖民地, 为此他们在... 嗯, 叫什么来着... 圣地亚哥集结了一支军事舰队, 没错。 这似乎并非谣言。 我认为我们不能忽视此事, 尤其是太子港的种植园是我见过的最佳种植园之一。 ";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "西班牙人在准备进攻太子港? 嗯... 好吧。 我们会指令查尔斯.德.莫尔船长处理此事。 ‘辉煌号’刚刚修复。 装备完毕, 随时可以起航... ";
			link.l1 = "还有一件事, 先生: 在巴黎, 圣马丁岛被视为法国殖民地, 但查尔斯.德.莫尔船长告诉我那里由荷兰人控制。 是这样吗, 骑士先生? ";
			link.l1.go = "patria_18";
		break;
		
		case "patria_18":
			dialog.text = "嗯... 某种程度上是这样。 圣马丁是法国殖民地。 然而, 男爵, 从经济角度看, 这个岛毫无用处 —面积狭小, 土壤贫瘠, 淡水稀缺, 井里的水又浑浊又苦涩。 甚至有人告诉我那里靠收集雨水饮用。 \n因此, 圣马丁被长期租给荷兰西印度贸易公司, 该公司将其用作从该地区到母国的北部中转点。 荷兰人扩建了那里的菲利普斯堡定居点, 建造了堡垒和港口, 对于像查尔斯.德.莫尔船长这样刚到群岛的人来说, 圣马丁似乎是荷兰殖民地。 ";
			link.l1 = "但法律上该岛属于我们? ";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			dialog.text = "当然。 但如我所说, 收取租金比利用其稀缺资源更划算。 ";
			link.l1 = "在我看来, 当法国西印度贸易公司进入加勒比时, 这个岛对其将非常有用。 正如你所说, 它是通往欧洲的北部前哨。 我需要访问这个殖民地, 很可能会停止将该岛租给荷兰人。 ";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "首先, 你需要向威廉斯塔德的荷兰西印度贸易公司董事彼得.斯特伊弗桑特发出询问。 他必须允许检查该岛 —毕竟荷兰人在那里已久。 ";
			link.l1 = "那我们需要派信使去威廉斯塔德。 ";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			dialog.text = "问题是, 斯特伊弗桑特先生很少在威廉斯塔德, 他经常乘大帆船出差处理公司事务... ";
			link.l1 = "但我想他至少有时会在那里吧? 无论如何, 荷兰人有义务让合法所有者检查该岛。 我们为何不写信给菲利普斯堡总督? ";
			link.l1.go = "patria_22";
		break;
		
		case "patria_22":
			dialog.text = "马丁.托马斯先生, 尽管对他表示尊重, 但他只是个普通雇员, 真正的管理由公司负责。 男爵, 我会解决这个问题, 别担心, 需要些时间。 ";
			link.l1 = "好吧, 我时间充裕。 毕竟我们还要访问南部殖民地瓜德罗普和马提尼克。 可惜查尔斯.德.莫尔船长这次不能陪我 —他必须再次前往伊斯帕尼奥拉... ";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetActorType(pchar); // 17-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//解锁界面
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_24";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
		break;
		
		case "patria_24":
			dialog.text = "是的, 是的, 我们用无聊的谈话耽误了亲爱的船长! 查尔斯, 把‘辉煌号’编入舰队, 前往伊斯帕尼奥拉, 查明西班牙人对太子港的任何真实威胁。 如果有, 就处理掉。 不过, 不用我教你, 你比我更清楚。 如果没发现什么, 就别浪费时间, 我需要你在这里。 不迟于一个月等你汇报。 祝你好运, 我的朋友! ";
			link.l1 = "谢谢您, 骑士先生。 我马上起航。 ";
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10) link.l1.go = "patria_25_1";
			else link.l1.go = "patria_25_2";
		break;
		
		case "patria_25_1":
			dialog.text = "还有一件事, 查尔斯: 我听说你和荷兰当局有麻烦? 请尽快解决这个问题, 不久你将不得不访问他们的殖民地。 如你所知, 在堡垒的炮火下这是不可能的。 ";
			link.l1 = "好的, 先生, 一定办到。 ";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25_2":
			dialog.text = "还有一件事, 查尔斯: 我警告你: 避免与荷兰人发生任何冲突。 不久你将不得不访问他们的殖民地。 如你所知, 在堡垒的炮火下这是不可能的... ";
			link.l1 = "好的, 先生。 不与荷兰人争吵。 ";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "15");
			pchar.questTemp.Patria = "epizode_3";
			Patria_PortPaxBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_26_1":
			dialog.text = "‘辉煌号’沉没了? 查尔斯, 这是一场灾难! 部长现在会怎么说? 你让我失望了, 查尔斯! 我原以为可以依靠你的经验, 而你... 唉, 你要为此负责。 我会写一份报告, 你最好消失一段时间。 你在皇家海军的服役结束了。 ";
			link.l1 = "嗯... 对不起, 先生。 看来我确实最好消失一两个月, 直到部长平息怒火。 再见, 再次为让你失望深感抱歉。 ";
			link.l1.go = "patria_26_2";
		break;
		
		case "patria_26_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "19");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// 允许"比黄金更珍贵"任务
			RemoveItems(pchar, "patent_fra", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterNationReputation(pchar, FRANCE, -5);
			pchar.quest.Patria_PortPaxOver.over = "yes"; // 移除计时器
		break;
		
		case "patria_26":
			dialog.text = "太棒了! 只要我们海军中有像你这样的船长, 就不必害怕卡斯蒂利亚人的诡计。 我明天会派信使去太子港送急件和法国邮件, 同时我会在给热雷米.德尚.迪穆萨卡先生的私人信件中暗示, 最好感谢你的服务, 所以我可以保证你, 查尔斯, 会得到应有的奖励。 \n现在来谈谈你的下一个任务。 是的, 我的朋友, 我有一个新任务给你, 不过这次不是军事任务, 而是非常微妙的, 我希望你能完成。 ";
			link.l1 = "我洗耳恭听, 骑士先生。 ";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "我想你还记得我和福盖先生关于圣马丁的讨论吧? 我们需要向男爵保证殖民地已被检查, 你将前往库拉索的威廉斯塔德, 去找公司董事彼得.斯特伊弗桑特。 他现在在那里, 还会待三周。 另外, 你需要护送载有公司货物的福禄特船到库拉索, 并把我的信交给斯特伊弗桑特先生。 ";
			link.l1 = "这些就是全部任务吗? ";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			dialog.text = "是的, 船长。 告诉我斯特伊弗桑特先生的回复。 我们应该赶在福盖先生从马提尼克和瓜德罗普访问回来之前, 他最终将能够访问圣马丁, 这是他非常想去的地方。 ";
			link.l1 = "很好。 我可以走了吗? ";
			link.l1.go = "patria_29";
		break;
		
		case "patria_29":
			dialog.text = "可以, 查尔斯。 别太久, 男爵不喜欢等待。 拜访彼得.斯特伊弗桑特时, 一定要穿制服! 一切都要显得正式, 如果你明白我的意思。 ";
			link.l1 = "当然, 骑士先生。 再见! ";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "20");
			pchar.questTemp.Patria = "epizode_4";
			Patria_CureerBegin();
			pchar.quest.Patria_PortPaxOver.over = "yes"; // 移除计时器
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_1");
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_31":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "谢谢你, 船长, 给我... (阅读) ... 那么, 太好了! 彼得.斯特伊弗桑特说福盖男爵可以访问圣马丁进行检查, 菲利普斯堡总督将得到通知并予以配合。 我想, 男爵访问后会做出正确决定 —让该岛继续租给荷兰人。 \n现在, 最令人高兴的消息, 船长! 我有几件事要告诉你。 首先: 考虑到你所有的军事成就, 你被提升为‘准将’。 接受我的祝贺, 先生! ";
			link.l1 = "我为法国服务! ";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			dialog.text = "其次: 太子港总督给我们送来了一艘满载货物的贸易船给你: 500大袋咖啡和500袋可可。 这些都是伊斯帕尼奥拉种植园的全部收成, 就是你保护免受西班牙袭击的那些。 还有一批特别贵重的货物给你 —50单位愈创木。 我想不需要解释那是什么。 你的货物在卡普斯维尔商店的仓库里, 你可以随时去找商人领取。 ";
			link.l1 = "谢谢您, 骑士先生! 真是好消息! ";
			link.l1.go = "patria_33";
		break;
		
		case "patria_33":
			dialog.text = "现在, 关于你的下一个任务: 福盖男爵随时会回到圣克里斯托弗。 你要带他去圣马丁, 并确保他得到良好保护。 可以说, 你要密切关注菲利普斯堡的情况, 然后向我汇报。 不要离开城市, 船长, 男爵一到 —我的仆人会找到你并报告。 ";
			link.l1 = "清楚了。 我可以走了吗? ";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "可以。 在陆地上休息几天对你有好处。 ";
			link.l1 = "... ";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "25");
			pchar.questTemp.Patria = "epizode_5";
			pchar.quest.Patria_CureerBackOver.over = "yes"; // 移除计时器
			Items[sti(pchar.EquipedPatentId)].TitulCur = 4; 
			Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.quest.Patria_SanMartin_wait.win_condition.l1 = "Timer";
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.hour  = 8 + rand(2);
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1 + rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1 + rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1 + rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l2 = "Location_Type";
			pchar.quest.Patria_SanMartin_wait.win_condition.l2.location_type = "town";
			pchar.quest.Patria_SanMartin_wait.function = "Patria_SanMartinBaron";
			pchar.questTemp.Patria.Goods = "true"; // 货物-奖品
			bQuestDisableMapEnter = true; // 关闭地图
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_36":
			DialogExit(); // 切换至巡查官
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_37";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true; // 锁定界面
		break;
		
		case "patria_37":
			dialog.text = "";
			link.l1 = "是的, 骑士先生, 我已经回来了! 圣马丁附近的荷兰‘朋友’用堡垒的大炮向我们开火, 还派出三艘船的中队袭击我们。 多亏查尔斯.德.莫尔船长和船员的精湛技术, 我们才得以逃脱! 看来彼得.斯特伊弗桑特先生实际上并不希望法国国王的使者进入菲利普斯堡, 您怎么看, 骑士先生? ";
			link.l1.go = "patria_38";
		break;
		
		case "patria_38":
			dialog.text = "什么? ! 这是斯特伊弗桑特的亲笔信, 他在信中保证... ";
			link.l1 = "但菲利普斯堡堡垒的指挥官显然收到了斯特伊弗桑特的另一封信, 信中命令他随意开火并用中队伏击我们! 这是意外吗, 骑士先生? ! 不! 他们显然在那里等着我们! 带着炮弹和铅弹! ";
			link.l1.go = "patria_39";
		break;
		
		case "patria_39":
			dialog.text = "男爵, 我恳求您... 我会处理此事。 我们立即派亲爱的查尔斯.德.莫尔船长再次前往库拉索会见斯特伊弗桑特。 船长在处理微妙局势方面经验丰富... 现在, 我让仆人给您准备洗澡水和美味午餐。 ";
			link.l1 = "... ";
			link.l1.go = "patria_40";
		break;
		
		case "patria_40":
			DialogExit();
			LAi_SetActorType(pchar); // 14-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false; // 解锁界面
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_41";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_41":
			dialog.text = "查尔斯, 我的朋友, 你得赶紧去威廉斯塔德。 也许斯特伊弗桑特还在那里。 如果不在, 就查明他的行踪并找到他。 会面时, 向他说明事件经过并要求解释。 我信任你的经验和权威, 委托你负责谈判。 然后分秒必争地回来向我汇报会面结果。 ";
			link.l1 = "任务明确, 骑士先生。 我立即备船出发。 ";
			link.l1.go = "patria_42";
		break;
		
		case "patria_42":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "29");
			pchar.questTemp.Patria = "epizode_6";
			Patria_DiplomatBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_43":
			dialog.text = "我简直不敢相信... ";
			link.l1 = "而且返程时我遭到荷兰海军中队的袭击。 请您解释一下, 骑士先生, 这到底是怎么回事? ";
			link.l1.go = "patria_44";
		break;
		
		case "patria_44":
			dialog.text = "我的朋友, 我知道你洞察力敏锐, 所以不打算对你隐瞒。 我只有一个要求 —你听到的内容绝不能泄露出去。 你能保证吗? ";
			link.l1 = "当然, 骑士先生。 ";
			link.l1.go = "patria_45";
		break;
		
		case "patria_45":
			dialog.text = "好的。 我确信, 法国海军将为你开启辉煌的职业生涯。 当然, 在我的帮助下, 你完全可以晋升为副舰队司令! 不过这是后话了... 现在说回荷兰和圣马丁岛。 \n在你抵达圣马丁岛很久之前, 那里就发现了大型盐矿。 起初无人问津, 但后来古巴和伊斯帕尼奥拉的西班牙人对盐矿表现出浓厚兴趣 —他们需要用盐腌制公牛尸体。 你肯定明白, 我们不能直接与西班牙人交易, 因此... ";
			link.l1 = "... 你以荷兰西印度贸易公司为幌子充当‘中间商’... ";
			link.l1.go = "patria_46";
		break;
		
		case "patria_46":
			dialog.text = "正是如此! 你思维敏捷, 判断准确, 查尔斯! 现在斯特伊弗桑特得知巴黎要派人检查, 便大胆决定将盐业生意完全据为己有, 他以为我们不敢公开与西班牙人的交易。 但他错了。 没人能从法国总督手中夺走利益还不受惩罚! 我们会让他付出代价。 ";
			link.l1 = "据我理解, 福盖男爵不能知道这件事... ";
			link.l1.go = "patria_47";
		break;
		
		case "patria_47":
			dialog.text = "我的朋友, 你说得完全正确, 男爵不需要知道细节。 已经发生的事足够严重: 企图杀害法国国王的代表, 袭击外交使团船只 (也就是袭击你) , 最重要的是 —实际吞并圣马丁岛! 这些足以成为对荷兰采取军事行动的理由。 ";
			link.l1 = "战争? ! ";
			link.l1.go = "patria_48";
		break;
		
		case "patria_48":
			dialog.text = "没错! 我的朋友, 副舰队司令的职位离你并不遥远, 你明白吗? 想象一下, 你身着上将制服在卢浮宫参与谈判, 路易十四亲自接见你这位尊贵的客人... 我们必须让荷兰人安分守己! 斯特伊弗桑特会后悔所作所为的。 你同意吗? ";
			link.l1 = "我同意, 骑士先生。 荷兰人必须为他们的无耻恶行付出代价。 ";
			link.l1.go = "patria_49";
		break;
		
		case "patria_49":
			dialog.text = "太好了。 我会将决定通知男爵, 并立即派信使前往各法属殖民地! 你呢, 长途跋涉后先休息一下, 请明天上午九点后再来见我, 我会为你准备战斗任务。 ";
			link.l1 = "好的, 先生。 请允许我告退。 ";
			link.l1.go = "patria_50";
		break;
		
		case "patria_50":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "33");
			pchar.questTemp.Patria = "epizode_7";
			Patria_HunterBegin();
			pchar.quest.Patria_DiplomatTimeOver.over = "yes"; // снять таймер
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_51":
			dialog.text = "我不认为这是战争, 实际上更像是强迫求和。 如果斯特伊弗桑特改变主意, 我们只会更高兴。 所以现在必须让他知道, 企图宣称拥有圣马丁岛, 他的损失将远大于收益。 这就是你要做的, 查尔斯。 ";
			link.l1 = "我在听。 ";
			link.l1.go = "patria_52";
		break;
		
		case "patria_52":
			dialog.text = "圣马丁岛是荷兰船只前往欧洲的转运基地, 公司船只定期停泊在菲利普斯堡海湾。 直到现在, 这些水域对他们来说都很安全。 但现在不同了, 船长! ... 你要前往圣马丁岛海岸巡逻, 捕获该公司的贸易船只。 \n该公司运输贵重货物时会使用东印度船 —这些船坚固耐用。 武装精良且货舱宽敞, 它们将是你的目标。 捕获五艘这样的船只及其货物, 作为战利品带到卡斯特维尔。 之后我们会继续与斯特伊弗桑特谈判, 或许他在计算损失后会改变主意。 ";
			link.l1 = "任务明确。 我可以走了吗? ";
			link.l1.go = "patria_53";
		// belamour legendary edition -->
			link.l2 = "先生, 我不得不问, 能否为这次行动提供部分资金? 这将是数月的航行, 需要持续维修和应对损失... ";
			link.l2.go = "patria_53a";
		break;
		
		case "patria_53a":
			AddMoneyToCharacter(pchar, 20000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			dialog.text = "恐怕我们的储备已经耗尽了, 查尔斯。 ‘辉煌号’的维护和战斗已花费了法属殖民地半年的预算。 现在我只能给你这些了。 想想未来的奖励吧, 查尔斯! 你前途无量! ";
			link.l1 = "是, 先生! ";
			link.l1.go = "patria_54";
		break;
		// < —legendary edtion
		case "patria_53":
			dialog.text = "出发吧, 我的朋友, 愿幸运永远伴随你。 ";
			link.l1 = "...";
			link.l1.go = "patria_54";
		break;
		
		case "patria_54":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "34");
			pchar.questTemp.Patria = "epizode_7_continue";
			Patria_HunterContinue();
		break;
		
		case "patria_55":
			pchar.questTemp.Patria.Hunter = sti(pchar.questTemp.Patria.Hunter)+1;
			if (sti(pchar.questTemp.Patria.Hunter) > 4) // все собрал
			{
				dialog.text = "你已完成任务, 船长。 感谢你出色的服务! 你应获得出售战利品的部分收入 —二十万比索。 ";
				link.l1 = "很高兴听到这个, 先生! ";
				link.l1.go = "patria_57";
			}
			else
			{
				dialog.text = "那么, 你只剩" + FindRussianQtyString(5-sti(pchar.questTemp.Patria.Hunter)) + "艘荷兰船只需要带到我们港口了。 ";
				link.l1 = "是的, 骑士先生! ";
				link.l1.go = "patria_56";
			}
		break;
		
		case "patria_56":
			DialogExit();
			AddQuestRecord("Patria", "35");
			AddQuestUserData("Patria", "sQty", 5-sti(pchar.questTemp.Patria.Hunter));
			DeleteAttribute(pchar, "questTemp.Patria.Hunter.GiveShip");
		break;
		
		// belamour legendary edition -->
		case "patria_57":
			AddMoneyToCharacter(pchar, 200000);
			dialog.text = "而且不止这些。 前几天我思考了一下... 查尔斯, 你确实为法国做了很多贡献。 坦白说, 铲除叛徒勒瓦瑟, 保卫圣皮埃尔免受西班牙的阴险袭击, 成功攻克圣何塞殖民地的堡垒并从西班牙人那里获得赔偿作为对他们大胆诡计的惩罚... 在那之后, 你亲自陪同从欧洲抵达的法国王室代表, 甚至在飞利浦堡水域的荷兰伏击中救了他的命! ";
			link.l1 = "先生, 说真的, 您让我不好意思了... 我只是在尽我的职责。 ";
			link.l1.go = "patria_57_1";
		break;
		
		case "patria_57_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "你总是这么谦虚, 我的朋友。 现在, 在执行迫使荷兰求和的下一项任务时, 你再次没有让我失望。 你不愧于这个词 —民族英雄! 作为群岛法国殖民地的总督, 我身边有几份法国最高荣誉的副本, 还有... 不过, 顺便说一句, 请你读一下这份文件。 ";
			link.l1 = "为了表彰对法国的杰出贡献... 以法国国王陛下的名义... 授予为法国服务的海军军官, 亨利.德.蒙特皮的儿子查尔斯.德.莫尔船长... 骑士先生, 你在开玩笑吗? ";
			link.l1.go = "patria_57_2";
		break;
		
		case "patria_57_2":
			dialog.text = "一点也不, 我的朋友。 我很荣幸地以你应得的方式奖励你, 授予你法国的最高荣誉 —圣路易勋章! 我们国家的每个公民都应该知道他们的英雄! 圣皮埃尔欠你的! 你值得这个勋章, 查尔斯。 ";
			link.l1 = "说真的, 我不知道该说什么... 谢谢您, 总督先生! 我发誓将继续自豪地为法国服务, 在敌人面前绝不退缩! ";
			link.l1.go = "patria_57_3";
		break;
		
		case "patria_57_3":
			GiveItem2Character(pchar, "talisman9");
			Log_Info("你获得了圣路易勋章! 你是民族英雄! ");
			PlaySound("interface\important_item.wav");
			DoQuestCheckDelay("sea_victory", 0.5);
			dialog.text = "这才是真正的军官说的话! 我真的为你感到骄傲, 查尔斯。 现在休息一下吧。 这是你应得的。 同时, 我会去和斯特伊弗桑特谈判 —也许他已经意识到, 与我们为敌比与我们为友更不划算。 不要离开这座城市, 两天后我会需要你。 ";
			link.l1 = "非常好, 先生。 我会等待进一步的指示。 ";
			link.l1.go = "patria_58";
		break;
		// < —legendary edtion
		case "patria_58":
			DialogExit();
			AddQuestRecord("Patria", "36");
			pchar.questTemp.Patria = "epizode_7_end";
			pchar.quest.Patria_siege_begin.win_condition.l1 = "Timer";
			pchar.quest.Patria_siege_begin.win_condition.l1.date.hour  = 9.00;
			pchar.quest.Patria_siege_begin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l2 = "location";
			pchar.quest.Patria_siege_begin.win_condition.l2.location = "Charles_town";
			pchar.quest.Patria_siege_begin.function = "Patria_SiegeBegin";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_59":
			dialog.text = "是的。 看来斯特伊弗桑特已经开始与西班牙结盟采取军事行动了。 一支荷兰-西班牙联合中队已经围攻了圣克里斯托弗。 哨兵堡垒每小时都会向我报告他们的每一个动向。 ";
			link.l1 = "围攻? ";
			link.l1.go = "patria_60";
		break;
		
		case "patria_60":
			dialog.text = "显然是这样。 他们没有直接进攻, 这其实是好事。 我们需要迅速行动, 船长, 趁敌人还没来得及封锁整个岛屿。 ";
			link.l1 = "我们需要做什么? ";
			link.l1.go = "patria_61";
		break;
		
		case "patria_61":
			dialog.text = "在安提瓜的圣琼斯, 驻扎着多伊利上校的英国海军中队。 现在, 他正在拜访乔纳森.福克斯爵士。 你必须穿过敌舰到达安提瓜。 在那里, 你会见到上校, 把我的信交给他, 并请求他的帮助。 ";
			link.l1 = "你认为上校会同意帮助我们吗? ";
			link.l1.go = "patria_62";
		break;
		
		case "patria_62":
			dialog.text = "我希望如此。 这封信应该能说服他, 他的帮助会得到相当可观的回报... 另外, 我们需要给目前在瓜德罗普海岸附近的‘辉煌号’船长送一封信, 他必须赶紧前往圣克里斯托弗。 ‘辉煌号’的火力将在战斗中给我们很大帮助。 由于你不能同时出现在两个地方, 我们的信使双桅小船将加入你的中队 —你必须完好无损地穿过敌人的包围圈, 它将在‘辉煌号’前往南方之前出发前往瓜德罗普... ";
			link.l1 = "我明白了。 穿过包围圈, 护送信使双桅小船, 并带着你的信赶紧去圣琼斯见多伊利上校。 ";
			link.l1.go = "patria_63";
		break;
		
		case "patria_63":
			dialog.text = "正是如此。 你准备好让你的中队接受另一艘船了吗? ";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "我会处理掉一艘船, 然后回来找你。 ";
				link.l1.go = "patria_63_1";
			}
			else
			{
				link.l1 = "是的。 ";
				link.l1.go = "patria_64";
			}
		break;
		
		case "patria_63_1":
			DialogExit();
			pchar.questTemp.Patria = "epizode_8_wait";
		break;
		
		case "patria_64":
			dialog.text = "太好了。 拿着这封信, 双桅小船已经准备好等待你的命令了。 ";
			link.l1 = "我们别浪费时间了, 骑士先生! ";
			link.l1.go = "patria_65";
		break;
		
		case "patria_65":
			DialogExit();
			AddQuestRecord("Patria", "38");
			pchar.questTemp.Patria = "epizode_8_continue";
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_3");
			Patria_SiegeCreateSquadron();
		break;
		
		case "patria_66":
			dialog.text = "是是, 我的朋友, 我知道你一向谦虚。 你是真正的军官! 我向你保证, 你会得到奖励的! 我想, 在这场恶战之后, 你需要休息一下吧? 你有整整一周的时间。 七天后到我房间来谈谈 —这座城市会为它的英雄准备奖励。 ";
			link.l1 = "好的, 先生。 我可以走了吗? ";
			link.l1.go = "patria_67";
		break;
		
		case "patria_67":
			dialog.text = "去吧, 好好休息。 稍后我们需要处理一些严肃的问题 —如你所见, 目前与荷兰人讲和是不可能的。 现在, 上校和我将讨论一些重要的问题。 ";
			link.l1 = "那我们一周后见, 骑士先生。 ";
			link.l1.go = "patria_68";
		break;
		
		case "patria_68":
			DialogExit();
			AddQuestRecord("Patria", "45");
			pchar.questTemp.Patria = "epizode_8_end";
			Patria_SiegeEnd();
			ChangeCharacterNationReputation(pchar, FRANCE, 20);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_69":
			pchar.quest.Patria_BastionTimeOver.over = "yes"; //снять таймер
			dialog.text = "我们和多伊利上校讨论过了, 他同意帮助我。 英国将帮助我们对抗荷兰人。 你和我需要反击并伸张正义 —圣马丁岛需要归还给法国。 我把这个任务交给最优秀的海军船长 —你, 查尔斯.德.莫尔! 敌人尚未从他们中队的失败中恢复过来, 我们将进攻飞利浦堡并占领它。 \n这场战斗不会轻松。 首先, 我们需要摧毁堡垒, 然后打破驻军的防御... (耳语) 你还需要强行穿过丛林, 到达我告诉你的盐矿, 并杀死在那里扎营的敌人... ";
			link.l1 = "任务相当艰巨, 骑士先生... ";
			link.l1.go = "patria_70";
		break;
		
		case "patria_70":
			dialog.text = "我完全理解你, 我的朋友。 你的中队将得到加强。 巴斯特尔和圣皮埃尔的总督现在应该已经各准备了一艘船 —一艘护卫舰。 你只需要访问瓜德罗普和马提尼克, 并将这些护卫舰纳入你的指挥之下。 当然, 如果你自己想要它们的话 —我不会坚持让你选择船只。 我还以两万比索的形式给你补贴, 用于为你的旗舰购买给养和装备。 拿着... ";
			link.l1 = "非常好, 先生。 ";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_71";
			else link.l1.go = "patria_71_1";
		break;
		
		case "patria_71_1":
			dialog.text = "此外, 像往常一样, ‘辉煌号’船归你指挥。 它已经修好并装备好了, 在锚地等着, 和船长谈过之后, 你随时可以接管它。 ";
			link.l1 = "太棒了! ";
			link.l1.go = "patria_71";
			pchar.questTemp.Patria.Ecliaton_Bastion = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_7";
			sld.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "patria_71":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "我们不能浪费时间, 船长。 正如我的间谍告诉我的, 荷兰人明白圣马丁面临的危险, 他们打算加强防御。 但你还有两个月的时间。 你必须按时完成任务! ";
			link.l1 = "我会的... (耳语) 圣马丁的盐矿在哪里? 岛上的任何地图上都没有标记... ";
			link.l1.go = "patria_72";
		break;
		
		case "patria_72":
			dialog.text = " (耳语) 当你进攻这座城市时, 审问飞利浦堡的总督, 马丁.托马斯先生, 他会告诉你的。 我保证那个荷兰人是个懦夫, 不会反抗你。 ";
			link.l1 = "我明白了。 那我可以出发了吗? ";
			link.l1.go = "patria_73";
		break;
		
		case "patria_73":
			dialog.text = "等一下, 查尔斯。 你还没有收到拯救圣克里斯托弗的奖励。 从市民那里拿走这些装满黄金的箱子, 以及我们最诚挚的感谢, 这是任何金钱都无法表达的! ";
			link.l1 = "谢谢您, 先生! ";
			link.l1.go = "patria_74";
		break;
		
		case "patria_74":
			TakeNItems(pchar, "chest", 10);
			Log_Info("你获得了10箱达布隆金币");
			PlaySound("interface\important_item.wav");
			dialog.text = "现在你可以走了。 祝你好运, 船长! 我们都在等待你的胜利! ";
			link.l1 = "再见, 骑士先生。 ";
			link.l1.go = "patria_75";
		break;
		
		case "patria_75":
			DialogExit();
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Bastion")) sTemp = "战舰‘辉煌号’也将归我指挥。 ";
			AddQuestRecord("Patria", "48");
			AddQuestUserData("Patria", "sText", sTemp);
			pchar.questTemp.Patria = "epizode_9_continue";
			SetFunctionTimerCondition("Patria_BastionSturmTimeOver", 0, 0, 62, false);
			// вернуть Синт-Маартен в норму
			int n = FindIsland("SentMartin");
			Islands[n].reload.l1.radius = 600.0;
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
			sld = CharacterFromID("Marigo Fort Commander");
			LAi_SetImmortal(sld, false);
			Character_SetAbordageEnable(sld, true);
			// атрибут квестовой высадки десанта
			pchar.TempPerks.QuestTroopers = true;
		break;
		
		case "patria_76":
			dialog.text = "谁能想到仅仅一年前, 你就被晋升为海军中将了呢, 我的朋友? 我只能猜测, 当这个消息传到法国时, 你的父亲会有多么骄傲! ";
			link.l1 = "我亲爱的父亲对此一定会非常高兴。 ";
			link.l1.go = "patria_77";
		break;
		
		case "patria_77":
			dialog.text = "你在舰队中赢得了自己的位置! 圣马丁已归还给法国, 施托伊弗桑特也得到了深刻的教训。 这是一场伟大的胜利! 但我们不能停止, 我们不能让荷兰人有片刻的休息。 他们将为自己的背叛负责! 多伊利上校现在正在皇家港, 准备他的海军中队: 我们将通过袭击库拉索来摧毁敌人的脊梁。 但那是以后的事, 现在我们必须一石二鸟, 查尔斯。 \n公司并非全靠贸易赚取了无数财富。 荷兰人在该地区的主要收入来源是种植园中的奴隶劳动。 如果你不知道的话, 查尔斯: 荷兰是最大的奴隶拥有和奴隶贸易国家。 运载着‘黑色象牙’的东印度人定期从西非来到库拉索。 不幸的是, 我恰好对此有所了解, 这对施托伊弗桑特来说可不是什么好事。 \n现在, 两艘荷兰东印度商船正从几内亚驶向加勒比海。 它们的货舱里装满了黑人囚犯。 大约十天后, 这支商队将绕过特立尼达岛, 朝库拉索方向航行。 你的任务是找到这支商队, 俘获这两艘东印度商船及其货物。 你必须摧毁护航船只, 并将奴隶带到我们在牙买加的盟友多伊利上校那里。 这非常重要, 查尔斯, 这样我们才能赢得他的信任... 我希望你能理解。 \n很抱歉没有给你留下任何休息时间, 但这项任务既重要又微妙, 我只能把它托付给你。 ";
			link.l1 = "为国家服务本就不是轻松差事, 骑士。 这一点我比谁都清楚。 我会尽快备好船只启程。 ";
			link.l1.go = "patria_78";
		break;
		
		case "patria_78":
			dialog.text = "祝你一帆风顺, 海军中将。 当你返回圣克里斯多夫时, 我们共同的朋友诺埃尔.福盖先生将完成对菲利普斯堡的检查, 我会确保从荷兰人那里缴获的部分战利品将亲自交给你。 ";
			link.l1 = "不胜感激, 骑士。 我这就告退? ";
			link.l1.go = "patria_79";
		break;
		
		case "patria_79":
			dialog.text = "去吧。 祝你好运, 我的朋友! ";
			link.l1 = "... ";
			link.l1.go = "patria_80";
		break;
		
		case "patria_80":
			DialogExit();
			Items[sti(pchar.EquipedPatentId)].TitulCur = 5; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.questTemp.Patria = "epizode_10_start";
			AddQuestRecord("Patria", "52");
			Patria_SlaveShipsStart();
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_81":
			dialog.text = "太棒了! 你从不知‘不可能’为何物, 查尔斯。 我曾以为你兄长是加勒比海最出色的海军军官, 但恕我直言, 如今他也得向你学习了。 我想你已经知道谁将代表我们与尊敬的上校共赴威廉斯塔德之战了吧? ";
			link.l1 = "绝无此事, 先生! 我对此毫不知情! ";
			link.l1.go = "patria_82";
		break;
		
		case "patria_82":
			dialog.text = "啊, 你这闻名的幽默感, 我亲爱的朋友! 哈哈! 当然是你, 海军中将。 你是不二人选。 准备好了吗? ";
			link.l1 = "自然, 骑士。 只需稍作修缮补充装备, 即可出征。 ";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_83";
			else link.l1.go = "patria_83_1";
		break;
		
		case "patria_83_1":
			dialog.text = "别忘了将‘辉煌号’纳入麾下。 它已修缮完毕整装待发, 正在码头恭候。 于贝尔.达西埃侯爵早已迫不及待, 渴望与你再度并肩作战。 ";
			link.l1 = "甚好。 配备远程射石炮的巨舰, 正是轰击堡垒的不二之选。 ";
			link.l1.go = "patria_83";
			pchar.questTemp.Patria.Ecliaton_Curacao = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_11";
			sld.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "patria_83":
			dialog.text = "稍等, 查尔斯。 我们的朋友福盖男爵从圣马丁带来了消息。 ";
			link.l1 = "... ";
			link.l1.go = "patria_84";
		break;
		
		case "patria_84":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_25";
			sld.greeting = "noel_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
		break;
		
		case "patria_85":
			dialog.text = "我从巴黎带来了喜讯。 国王已签署你的海军中将任命书, 相关文书即将送达。 特此祝贺! ";
			link.l1 = "多谢先生! 愿为法国与国王效犬马之劳! ";
			link.l1.go = "patria_coat";
		break;
		
		case "patria_coat":
			dialog.text = "我也一如既往, 乐于听闻你的忠诚誓言。 查尔斯, 可愿与我共饮一杯? 这可是巴黎直运的佳酿, 方圆一日路程内绝无仅有! ";
			link.l1 = "多谢骑士美意, 还是免了吧。 稍后需返舰履职, 身为法国海军中将, 若在舰尾甲板醉态可掬, 成何体统。 ";
			link.l1.go = "patria_coat_01";
			link.l2 = "也好! 能与总督大人同席共饮, 实乃难得之幸! ";
			link.l2.go = "patria_coat_02";
		break;
		
		case "patria_coat_01":
			dialog.text = "也罢, 你大可稍作休憩, 不必急于返舰。 既为你所愿, 自当尊重。 那便言归正传吧。 ";
			link.l1 = "洗耳恭听。 ";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_02":
			dialog.text = "并非每位总督都有此等福分 —麾下海军中将既是军中翘楚, 又是能同桌共饮家乡美酒的挚友! ";
			link.l1 = "为法兰西! ";
			link.l1.go = "patria_coat_03";
			link.l2 = "敬骑士安康! ";
			link.l2.go = "patria_coat_04";
		break;
		
		case "patria_coat_03":
			dialog.text = "也为国王! ";
			link.l1 = "... ";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_04":
			dialog.text = "也敬你, 查尔斯! ";
			link.l1 = "... ";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_05":
			LAi_Fade("", "");
			if(LAi_GetCharacterHP(pchar) == LAi_GetCharacterMaxHP(pchar))
			pchar.chr_ai.hp = stf(pchar.chr_ai.hp) - 1.0;
			GiveItem2Character(pchar, "potionwine");
			DoCharacterUsedItem(pchar, "potionwine");
			npchar.dialog.currentnode = "patria_coat_06";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorSetHuberMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 1.2);
		break;
		
		case "patria_coat_06":
			dialog.text = "嗯, 果然是琼浆玉液! 你觉得如何? ";
			link.l1 = "所言极是。 这让我想起加斯科尼家乡的葡萄酒... ";
			link.l1.go = "patria_coat_07";
		break;
		
		case "patria_coat_07":
			dialog.text = "你记错了, 朋友 —这是波尔多佳酿。 不过加斯科尼的葡萄酒想必也不遑多让! ";
			link.l1 = "怕是快要忘了它的滋味... 离开法国多久了? 一年? 还是两年? ";
			link.l1.go = "patria_coat_08";
		break;
		
		case "patria_coat_08":
			dialog.text = "啊, 查尔斯, 恍如昨日... 尽管初遇时的情景算不上愉快。 请恕我提及往事, 若当时有人说这牢房里站着的会是我未来在法属殖民地的左膀右臂, 我定会嗤之笑之。 ";
			link.l1 = "Inscrutabiles sunt viae Domini.";
			link.l1.go = "patria_coat_09";
		break;
		
		case "patria_coat_09":
			dialog.text = "抱歉, 你说什么? ";
			link.l1 = "是拉丁语, 骑士。 意为‘主的道路玄妙难测’。 无人知晓命运走向。 ";
			link.l1.go = "patria_coat_10";
		break;
		
		case "patria_coat_10":
			dialog.text = "你总给我惊喜, 查尔斯。 竟不知你还通晓拉丁语。 不过从某种意义上说, 命运也由自己书写, 不是吗? ";
			link.l1 = "两者皆有吧。 前路唯有主知晓, 但祂亦眷顾坚韧之人。 ";
			link.l1.go = "patria_coat_11";
		break;
		
		case "patria_coat_11":
			dialog.text = "深以为然。 犹记当年授你海军军官委任状。 赠予制服的情景。 而今眼前已是堂堂海军中将! ";
			link.l1 = "光阴荏苒, 骑士。 ";
			link.l1.go = "patria_coat_12";
		break;
		
		case "patria_coat_12":
			dialog.text = "可不是嘛... 就连你这身制服, 剑痕累累: 有些缝补过, 有些显然是新伤。 得好好拾掇拾掇了。 ";
			link.l1 = "总督大人有何打算? ";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_13":
			dialog.text = "除了加勒比法属舰队海军中将这一新职, 我还有份礼物要送你。 ";
			link.l1 = "令我汗颜了, 骑士。 是何礼物? ";
			link.l1.go = "patria_coat_14";
		break;
		
		case "patria_coat_14":
			dialog.text = "我已嘱托私人裁缝 —法属殖民地首屈一指的匠人! —为你缝制一套与军衔匹配的新制服。 费用无需操心, 我已全权负责。 ";
			link.l1 = "感激不尽! 定当拜访你的裁缝。 他在哪里? ";
			link.l1.go = "patria_coat_15";
		break;
		
		case "patria_coat_15":
			dialog.text = "此刻应在港口办公室 —刚有一艘信使船从大陆运来小件包裹。 我们的裁缝总要订购些本地难寻的料子。 ";
			link.l1 = "那我这就去港口办公室。 再次致谢, 先生! ";
			link.l1.go = "patria_86";
		break;
		
		case "patria_86":
			dialog.text = "如今你亟需好生休养。 准你一月假期, 务必尽兴度过。 卸下所有事务, 交由属官打理, 安心休憩。 可入住我的官邸客房, 仆役会悉心照料你的假期。 一月后再会 —届时有要事与你相商。 ";
			link.l1 = "遵命, 骑士。 告辞! ";
			link.l1.go = "patria_87";
		break;
		
		case "patria_87":
			npchar.dialog.currentnode = "First time";
			LAi_Fade("","");
			LAi_SetHuberType(npchar);
			DialogExit();
			AddQuestRecord("Patria", "65"); // далее коллизия Пуанси-Инспектор-Шарль
			pchar.questTemp.Patria = "epizode_12_start";
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			SetFunctionLocationCondition("Patria_Tailor", "Charles_PortOffice", false)
			Patria_CondotierStart();
			ChangeCharacterComplexReputation(pchar, "nobility", 15); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 15);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
		break;
		
		case "patria_88":
			dialog.text = "没错, 查尔斯。 我本想亲自处理此事, 但... 唉, 不得不再次借助你的才能。 不过首先, 我要给你些东西: 三十万比索和五箱达布隆金币。 这是施托伊弗桑特按协议支付给我的大部分款项。 你承担了大部分工作, 这些理应属于你。 收下吧。 你满意吗, 我的朋友? ";
			link.l1 = "先生, 金钱从不会伤人, 这是我早已明白的道理。 ";
			link.l1.go = "patria_89";
		break;
		
		case "patria_89":
			AddMoneyToCharacter(pchar, 300000); 
			TakeNItems(pchar, "chest", 5);
			dialog.text = "啊, 海军中将, 希望你不会对过去的事耿耿于怀... 你如今已是国家英雄, 知道吗? 身居新职感觉如何? 记住: 许多优秀军官花了数十年攀爬军衔阶梯, 但若没有得力相助... 他们可能一辈子只是指挥官。 而你, 我的朋友, 拥有总能完成不可能之事的独特能力! 何况你在高层有位既是朋友又是庇护者的人, 今后若遇麻烦, 我定会为你排忧解难。 ";
			link.l1 = "感谢大人美言。 我感觉在这地区几乎已功成名就 —当然是在您的帮助下。 现在我能安心处理个人事务了吧? 我得为家人考虑。 ";
			link.l1.go = "patria_90";
		break;
		
		case "patria_90":
			dialog.text = "你想结婚了, 查尔斯? 哈哈哈! 在巴黎随便指一位美女, 她都会立刻投入你怀抱! 但可惜, 这事得先搁置。 至少目前, 我需要你留在这里, 朋友。 ";
			link.l1 = "看来法国在群岛的势力空前强大: 与英格兰结盟, 和东印度公司休战, 也没有难缠的‘勒瓦瑟’之流了, 对吗? ";
			link.l1.go = "patria_91";
		break;
		
		case "patria_91":
			dialog.text = "国家如同人类, 永远欲求不满... 而我们确实有了新的‘勒瓦瑟’, 海军中将... ";
			link.l1 = "真的? 是谁? ";
			link.l1.go = "patria_92";
		break;
		
		case "patria_92":
			dialog.text = "是我们的老熟人, 诺埃尔.福盖男爵。 你还记得他为何来此吗? ";
			link.l1 = "嗯... 您说过与西印度贸易公司有关。 巴黎打算效仿荷兰建立类似机构? ";
			link.l1.go = "patria_93";
		break;
		
		case "patria_93":
			dialog.text = "正是如此, 仿照荷兰东印度公司。 但白手起家谈何容易。 你知道, 施托伊弗桑特有数十年跨大陆贸易经验。 成熟的代理网络和庞大的商船队。 法国却没有这些, 而且查尔斯, 你可能不知道, 国王目前财政极为拮据。 他们想通过掌控这里的贸易改善宗主国财务状况, 却不了解我们将面临的局面 --\n英法荷的竞争。 西班牙的领土野心。 前所未有的海盗肆虐。 每艘贸易商船都需军舰护航, 否则极可能有去无回。 而我们既没有荷兰东印度公司那样的强大舰队, 也没有西班牙那样的巨型盖伦帆船。 ";
			link.l1 = "但您向男爵解释过这些吗? 包括海盗问题? ";
			link.l1.go = "patria_94";
		break;
		
		case "patria_94":
			dialog.text = "当然解释过。 还提到你清除勒瓦瑟后, 海盗被逐出托尔图加但始终对我们怀恨在心。 我组织了多方会谈印证我的担忧, 但可惜对男爵毫无作用。 他是大臣们派来的, 自然要听命于他们... 现实就是如此。 ";
			link.l1 = "呵... ";
			link.l1.go = "patria_95";
		break;
		
		case "patria_95":
			dialog.text = "而且不必讳言, 巴黎直接掌控群岛的贸易公司... 你我, 海军中将... 在这里不需要它。 ";
			link.l1 = "我明白。 ";
			link.l1.go = "patria_96";
		break;
		
		case "patria_96":
			dialog.text = "你看, 朋友, 我对你毫无保留... 我曾满心希望福盖先生能放弃成立贸易公司的想法, 但... 事与愿违。 我已用尽对男爵的影响力, 现在该你登场了。 ";
			link.l1 = "嗯... 就像对付勒瓦瑟那样? ";
			link.l1.go = "patria_97";
		break;
		
		case "patria_97":
			dialog.text = "哦上帝, 你把我当成什么人了, 查尔斯? ! 男爵是 influential 人物, 还是财政大臣的朋友! 况且, 除掉他毫无意义: 巴黎会立刻派来新的政客。 我们需要从根本上摧毁成立公司的想法, 明白吗, 查尔斯? 要让男爵回法国报告说这事在财务上风险极高。 毫无意义... ";
			link.l1 = "先生有什么计划吗? ";
			link.l1.go = "patria_98";
		break;
		
		case "patria_98":
			dialog.text = "唉, 没有, 查尔斯。 我试过所有办法: 用船只资金短缺。 荷兰人。 海盗吓唬他... 都没用。 ";
			link.l1 = "看来光靠嘴说不够。 嗯... 您刚才说海盗? ";
			link.l1.go = "patria_99";
		break;
		
		case "patria_99":
			dialog.text = "我就知道你有主意, 朋友! 从无怀疑, 你才智过人。 说服这位男爵, 我保证让你父亲富可敌国, 家中财富能填满卢浮宫。 我向你承诺, 查尔斯。 ";
			link.l1 = "好的, 骑士。 任务清楚了。 ";
			link.l1.go = "patria_100";
		break;
		
		case "patria_100":
			dialog.text = "我发誓, 查尔斯, 若你成功必不会后悔。 这点毋庸置疑。 我何时背叛过你, 朋友? ";
			link.l1 = "从未有过, 先生。 在哪里能找到男爵? ";
			link.l1.go = "patria_101";
		break;
		
		case "patria_101":
			dialog.text = "他现在在太子港。 他说觉得伊斯帕尼奥拉岛的广袤田野山谷十分迷人... ";
			link.l1 = "很好。 现在请允许我告辞。 ";
			link.l1.go = "patria_102";
		break;
		
		case "patria_102":
			DialogExit();
			AddQuestRecord("Patria", "67");
			pchar.questTemp.Patria = "epizode_12_pirates";
			Patria_CondotierSail();
		break;
		
		case "patria_103":
			dialog.text = "正是如此。 男爵把一切都告诉我了。 经历了这一切后... 不过, 海军中将, 你总能把事情解释得无比透彻, 无人能及! 我该向你学习! ";
			link.l1 = "我从您身上学到了很多, 骑士。 ";
			link.l1.go = "patria_104";
		break;
		
		case "patria_104":
			dialog.text = "朋友, 我欠你的。 我保证你父亲此生所需应有尽有, 你家将成为全省乃至全法国最华美的宅邸之一... 另外, 我会付你10万比索, 希望能弥补你与海盗的债务... ";
			link.l1 = "听到这些太高兴了, 先生! ";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_105add":
			AddMoneyToCharacter(pchar, 100000); 
			dialog.text = "我还为你准备了一份特殊礼物。 相信你能理解这件物品的价值, 以及我对您忠诚服务的诚挚谢意! 那么, 海军中将查尔斯.德.莫尔, 我将马耳他骑士团的私人礼仪佩剑赠予你! 这把珍贵的武器与你的制服相得益彰。 若你决定返回巴黎, 诺埃尔.福盖男爵已承诺将你引荐给国王 —届时你应身着制服。 佩戴此剑盛装出席! 法国海军还有更辉煌的前程等待你! ";
			link.l1 = "这把剑美得无与伦比! 谢谢您, 先生, 我实在不配这份殊荣... ";
			link.l1.go = "patria_105";
		break;
		
		case "patria_105":
			ref itm = ItemsFromID("blade_36");
			itm.picIndex = 16;
			itm.picTexture = "ITEMS_17";
			itm.price = 10000;
			itm.Weight = 3.0;
			itm.lenght = 1.05;
			itm.curve = 1.0;
			itm.Balance = 1.9;
			GiveItem2Character(pchar, "blade_36");
			Log_Info("你获得了马耳他之剑");
			PlaySound("interface\important_item.wav");
			dialog.text = "你配得上! 而且你在此期间, 将迎来重大转机 —好的转机。 查尔斯.德.莫尔海军中将, 我任命你为圣马丁总督! ";
			link.l1 = "哈! 我没听错吧? ";
			link.l1.go = "patria_106";
		break;
		
		case "patria_106":
			ChangeCharacterComplexReputation(pchar, "nobility", 12); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 12);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
			dialog.text = "没错, 朋友。 你现在是圣马丁总督, 这片你悉心守护的土地。 ";
			link.l1 = "骑士, 请允许我拒绝这份荣誉。 我不想被束缚在这个贫瘠的小岛上! 还有那些内政事务... 那不是我该做的! ";
			link.l1.go = "patria_107";
		break;
		
		case "patria_107":
			dialog.text = "我不接受拒绝。 朋友, 别担心: 你可以像以前一样生活。 所有乏味的事务都由现任代理总督处理, 你将是实际掌权的总督。 查尔斯, 你不明白为何偏偏任命你为圣马丁总督吗? 现在是最佳时机, 无人会质疑。 我需要一个‘自己人’担任那里的总督, 你懂我的意思吧? ";
			link.l1 = "盐矿? ";
			link.l1.go = "patria_108";
		break;
		
		case "patria_108":
			dialog.text = "当然! 还有第二个好消息: 从现在起, 每月15日你将从盐矿和多伊利的贸易中获得分成, 每月被动收入将达10万比索。 ";
			link.l1 = "哈! 听着真让人高兴! 谢谢您, 骑士。 好吧, 如果不用一直待在那里, 我接受总督职位。 要是我决定航行去法国呢? ";
			link.l1.go = "patria_109";
		break;
		
		case "patria_109":
			dialog.text = "你决定了就可以走, 我虽会失望但会找人接替你。 但不止这些, 我这里有你父亲的一封信, 看看吧。 ";
			link.l1 = "我父亲的信? 太让人激动了! ... 好的, 先生, 就这么定了。 我现在可以走了吗? 我想读信... 没有新任务了吧? ";
			link.l1.go = "patria_110";
		break;
		
		case "patria_110":
			dialog.text = "现在没有, 总督。 但如果有工作, 我知道去哪找你。 祝你好运, 查尔斯! ";
			link.l1 = "也祝您好运, 骑士! ";
			if (pchar.questTemp.Patria == "epizode_12_baronwin") link.l1.go = "patria_119";
			else link.l1.go = "patria_111";
		break;
		
		case "patria_111":
			DialogExit();
			AddQuestRecord("Patria", "77");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_112":
			dialog.text = "该死, 真是灾难! 现在我们有更多麻烦要处理。 这是你干的吗, 查尔斯? 说实话, 是意外吗? ";
			link.l1 = "呃... 出了点意外... ";
			link.l1.go = "patria_113";
		break;
		
		case "patria_x112":
			dialog.text = "该死, 真是灾难! 现在我们有更多麻烦要处理。 男爵选了个极糟的地方赴死! 你确定没帮他‘离开人世’? ";
			link.l1 = "您说什么呢, 骑士? ! 当然没有! ";
			link.l1.go = "patria_x113";
		break;
		
		case "patria_y112":
			dialog.text = "该死, 真是灾难! 现在我们有更多麻烦要处理。 你确定没帮他‘离开人世’? ";
			link.l1 = "您说什么呢, 骑士? ! 当然没有! ";
			link.l1.go = "patria_y113";
		break;
		
		case "patria_x113":
			dialog.text = "好吧。 不过, 朋友, 或许还没到不可收拾的地步。 发烧就是发烧, 对吧? 在部里派来新监察官之前, 我们会清理这里的烂摊子, 武装好等待‘客人’... 现在, 查尔斯, 我们需要切断所有联系, 你明白为什么吧? ";
			link.l1 = "当然明白。 ";
			link.l1.go = "patria_114";
		break;
		
		case "patria_y113":
			dialog.text = "好吧。 不过, 朋友, 或许还没到不可收拾的地步。 加勒比海发生战斗很正常, 对吧? 在部里派来新监察官之前, 我们会清理这里的烂摊子, 武装好等待‘客人’... 现在, 查尔斯, 我们需要切断所有联系, 你明白为什么吧? ";
			link.l1 = "当然明白。 ";
			link.l1.go = "patria_114";
		break;
		
		case "patria_113":
			dialog.text = "好吧。 不过, 朋友, 或许还没到不可收拾的地步。 海盗就是海盗, 对吧? 在部里派来新监察官之前, 我们会清理这里的烂摊子, 武装好等待‘客人’... 现在, 查尔斯, 我们需要切断所有联系, 你明白为什么吧? ";
			link.l1 = "当然明白。 ";
			link.l1.go = "patria_114";
		break;
		
		case "patria_114":
			dialog.text = "无论如何, 朋友, 你已尽了全力, 这总比什么都不做好。 很高兴命运让我们相遇。 你可以保留职位, 相信你在法国会有大好前程。 我想你也该回巴黎了, 这是你父亲的信, 拿着吧。 ";
			link.l1 = "我父亲的信? 太让人高兴了! ... 好吧, 先生, 我明白: 切断联系, 完全保密, 尽快回巴黎。 现在可以走了吗? 我想读信... ";
			link.l1.go = "patria_115";
		break;
		
		case "patria_115":
			dialog.text = "走吧, 查尔斯。 祝你好运! ";
			link.l1 = "也祝您好运, 骑士! ";
			link.l1.go = "patria_116";
		break;
		
		case "patria_116":
			DialogExit();
			AddQuestRecord("Patria", "78");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_117":
			dialog.text = "正是如此。 海军中将, 你解释事情的能力无人能及! 我真该向你学习! ";
			link.l1 = "我从您身上学到了很多, 骑士。 ";
			link.l1.go = "patria_118";
		break;
		
		case "patria_118":
			dialog.text = "我的朋友, 我欠你一份人情。 我向你保证, 你亲爱的父亲余生所需的一切都将得到满足, 你的家族宅邸将成为全省最好的... 甚至是全法国最好的之一。 此外, 我会付给你10万比索 —希望这能支付你的旅行费用, 并让你好好休息一下, 你确实该休息了。 ";
			link.l1 = "听到这些真是太好了, 先生! ";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_119":
			DialogExit();
			AddQuestRecord("Patria", "87");
			pchar.questTemp.Patria = "europe";
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			SetFunctionTimerCondition("Patria_EuropeTime", 0, 0, 175+rand(10), false); // таймер
		break;
		
		case "patria_prison":
			dialog.text = "你怎么能这样, 查尔斯! 你怎么能这样对我? ! ";
			link.l1 = "呃... ";
			link.l1.go = "patria_prison_1";
		break;
		
		case "patria_prison_1":
			dialog.text = "我知道是你干的! 就是你! 别否认! 没有你的帮助, 福盖男爵永远也得不到矿场经理的报告, 找不到矿场的位置, 甚至连彼得.施托伊弗桑特的文件都拿不到。 虽然没人提到你的名字, 但我可以肯定: 就是你。 为什么, 查尔斯? ... 回答我... 为什么? 为了米歇尔? 一百万比索? 为了勒瓦瑟? 还是为了总督的职位? ";
			// belamour legendary edition -->
			link.l1 = "你还记得我们第一次见面吗, 骑士? 你是怎么羞辱我的? 你是怎么敲诈我一百万比索的? 我只希望有一天我们能互换位置。 我没什么可说的了。 ";
			link.l1.go = "patria_prison_2";
			link.l2 = "为了勒瓦瑟。 一百万的债务, 我还能理解。 我工作, 我杀人, 我赚钱, 我抢劫, 但我已经赔偿了你所有的损失。 但这对你来说还不够。 你, 骑士, 派我去执行对抗王室的自杀任务, 只是为了进一步巩固你自己的权力! 你的背叛必须付出代价。 而你已经得到了! ";
			link.l2.go = "patria_prison_2";
			link.l3 = "野心, 骑士。 在这个陌生的新世界里, 我几乎已经实现了所有可能的目标。 总督的职位对我来说似乎是一个值得追求的目标。 我从你身上学到了很多。 再见! ";
			link.l3.go = "patria_prison_2";
			link.l4 = "说实话, 我自己也不知道。 也许是因为我被男爵和他对国家的忠诚服务所打动? 无论如何, 你现在有足够的时间替我思考这个问题了。 再见! ";
			link.l4.go = "patria_prison_2";
			// < —legendary edition
		break;
		
		case "patria_prison_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			SetFunctionTimerCondition("Patria_EuropePuancieClear", 0, 0, 5, false); // таймер
			pchar.quest.Patria_Europe_final.win_condition.l1 = "location";
			pchar.quest.Patria_Europe_final.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Europe_final.function = "Patria_EuropeFinal";
		break;
		
		case "patria_patentfail":
			DialogExit();
			pchar.questTemp.Patria = "fail";
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			// убрать Эклятон, если есть
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton"))
			{
				sld = characterFromId("Ecliaton_Cap");
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeday = 0;
				DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
			}
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ1":
			SetTimerCondition("PZ_NormanBackToStreets", 0, 0, 1, false);	//Вовзращаем Акулу или Тиракса в Шарптаун
			// ставим сразу прерывание, чтобы потом по тысячу раз не копировать
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang") || CheckAttribute(pchar, "questTemp.PZ.LongwayTorero") || CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))
				{
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1 = "location";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1.location = "Charles_town";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition = "PZ_AfterPoincyLongwayDialog";
				}
			}
			
			if (!CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva")) 
			{
				dialog.text = "很高兴见到你, 查尔斯。 我听说了你的壮举。 干得漂亮! ";
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "这还不是全部, 阁下。 ";
					link.l1.go = "PZ2";
				}
				else
				{
					link.l1 = "您能给我一份书面命令, 让我哥哥现在就被释放吗? ";
					link.l1.go = "serve";
				}
			}
			else 
			{
				dialog.text = "你好, 查尔斯。 进来吧, 我已经得到消息了。 ";
				link.l1 = "消息? 可能有些误会, 阁下。 我是来报告您交给我的任务已成功完成的, 但我看您心情不太好。 ";
				link.l1.go = "PZ_PoincyAngry1";
			}
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube");
		break;
					
		case "PZ2":
			dialog.text = "是吗? 你是什么意思, 船长? ";
			link.l1 = "我成功活捉了勒瓦瑟, 并把他带来见您。 我们一结束谈话, 我就下令把他带来。 ";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "我从没想过这种事是可能的! 真的, 干得漂亮, 查尔斯! 我怀疑即使你那位杰出的哥哥也未必能做得更好。 你的父亲会为你骄傲的, 我的朋友。 ";
			link.l1 = "谢谢您的夸奖, 菲利普先生。 ";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "PZ5":
			dialog.text = "非常好, 查尔斯。 我对你很满意。 ";
			link.l1 = "您能给我一份书面命令, 让我哥哥现在就被释放吗? ";
			link.l1.go = "serve";
			LAi_SetHuberType(npchar);
		break;
		
		case "PZ_PoincyAngry1":
			dialog.text = "也许我应该想到, 你不像你哥哥 —不是军人, 不是特工, 在 delicate 行动方面也没有经验。 你不该在托尔图加的街道上与士兵公开对抗。 会有人调查的, 也会调查到我。 你知道, 这些人很严肃。 ";
			link.l1 = "请原谅, 骑士。 您知道, 勒瓦瑟不会不战而降的。 ";
			link.l1.go = "PZ_PoincyAngry2";
		break;
		
		case "PZ_PoincyAngry2":
			dialog.text = "没错, 但是... 算了。 第一次行动能做到这样已经不错了。 我会报告说他在官方检查期间袭击了皇家审计官和他的护送队。 ";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
			{
				link.l1 = "阁下, 如果有帮助的话, 我可以把勒瓦瑟带来见您。 我和我的手下很幸运, 在他的手下试图在街上逮捕我们之后, 在一个隐蔽的地方抓住了他。 ";
				link.l1.go = "PZ_PoincyAngry3";
			}
			else
			{
				link.l1 = "您能给我一份书面命令, 让我哥哥现在就被释放吗? ";
				link.l1.go = "serve";
			}
		break;
				
		case "PZ_PoincyAngry3":
			dialog.text = "你说什么, 查尔斯? 再说一遍。 ";
			link.l1 = "弗朗索瓦.勒瓦瑟现在在我手里, 随时可以交给您, 菲利普先生。 ";
			link.l1.go = "PZ_PoincyAngry4";
		break;
		
		case "PZ_PoincyAngry4":
			dialog.text = "忘了我之前说的一切吧。 我确实反应过度了。 干得漂亮。 我不确定即使你那位杰出的哥哥能否做到这一点。 ";
			link.l1 = "谢谢您, 骑士。 ";
			link.l1.go = "PZ_PoincyAngry5";
		break;
		
		case "PZ_PoincyAngry5":
			dialog.text = "你很有前途, 我的朋友。 我希望你的才能更多地用于国家的利益。 但是请, 从现在起尽量更加... 谨慎。 我们的工作通常需要 delicate 的方法。 哦, 对了, 还有一件事。 ";
			link.l1 = "是的, 阁下? ";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}