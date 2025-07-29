// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("说吧, 你想要什么? ",
                          "我们刚聊过这个。 你肯定是忘了... ", "这已经是今天你第三次问这类问题了... ",
                          "听着, 这是商店。 人们来这儿买东西。 别打扰我! ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("你知道吗, " + Npchar.name+ ", 或许下次吧。 ", "对, 不知怎么就忘了... ",
                      "是啊, 真的是第三次了... ", "嗯, 我不会了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			//Jason --> ----------------------------------迷你任务 不公平竞争------------------------------------
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "谢谢你, 船长, 感谢你完成我的请求。 现在" + pchar.questTemp.Shadowtrader.Guardername + "在这里, 我至少能感到放松一点了。 ";
					link.l1 = "嗯... 我不想显得太冒昧, 但我觉得你好像有麻烦。 能告诉我怎么回事吗 —也许我能帮你? "; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "那么? 你把我的信交出去了吗? ";
					link.l1 = "交了。 指挥官口头回复说, 你信中的证据不足以让城防卫队采取任何措施。 "; 
					link.l1.go = "Shadowtrader_trouble";
					pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && CheckAttribute(pchar, "questTemp.Shadowtrader.EndFort"))
				{
					dialog.text = "我已经听说了 —今晚卫兵发现了一个走私者的非法贸易点, 并将他们全部逮捕。 领头的是个十足的混蛋, 现在没事了, 他短期内不会再对任何人做坏事了\n指挥官告诉了我你在这件事里的作用, 我很感激! 你信守了承诺! 拿着这些钱 —15000比索。 你救了我。 现在我的生意没有任何威胁了! ";
					link.l1 = "不客气。 这很容易。 "; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "那么, 有什么好消息吗, " +pchar.name+ "? ";
					link.l1 = "我找到你的竞争对手了。 他不会再给你添麻烦了 —我设法说服他... 离开了这个岛。 他的‘商店’在靠近城门的一所房子里。 那些被遗弃的货物该怎么处理, 由你决定。 你可以交给当局, 或者试着自己收集。 "; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "我已经听说了 —今晚卫兵在一所房子下面发现了走私者的一个据点。 发现两名恶棍死亡。 干得好, " +pchar.name+ ", 我很佩服你! 拿着奖励 —15000比索。 你刚救了我! 现在我可以真正做生意了! \n满足一下我的好奇心 —他们的头目... 也在那两个死者之中吗? ";
					link.l1 = "没有。 但他再也不会在你的镇上露面了。 我相信我们说话的时候, 他应该已经离这个岛几十英里远了。 "; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "我已经听说了 —今晚卫兵在一所房子里找到了一个秘密的走私者商店。 发现三名恶棍死亡。 干得漂亮, " +pchar.name+ ", 我佩服你! 拿着奖励 —15000比索。 你刚救了我! 现在我可以真正做生意了! \n满足一下我的好奇心 —他们的头目... 也在那两个死者之中吗? ";
					link.l1 = "是的。 你永远摆脱了你的竞争对手。 他再也不会给你添麻烦了。 "; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//< —迷你任务 不公平竞争
		break;
		
		// --> 迷你任务 不公平竞争
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader_Block = true;
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "你能去酒馆找一个叫" + pchar.questTemp.Shadowtrader.Guardername + "的人, 让他尽快来这里吗? 我不能离开商店, 而这个笨蛋坐在酒馆里灌朗姆酒, 尽管在值班, 肯定不会想到来这里。 ";
			link.l1 = "我总是乐于助人, 伙计 —更何况我本来就打算去酒馆。 ";
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = "你在嘲笑我吗? 我看起来像你的跑腿吗? 酒馆离这儿只有几步之遥 —你可以自己去。 ";
			link.l2.go = "exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = "谢谢! 请告诉他马上来这里。 哦, 天哪, 他为什么非要这么麻烦... ";
			link.l1 = "别担心。 我会让他来你这儿的。 ";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = sti(npchar.nation);
			//创建守卫
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, sti(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = "哦, 船长, 我真的需要你的帮助。 你能尽快把这封信交给指挥官吗? 我会为这个小事付你300枚硬币 —正如我已经说过的, 我不能离开我的商店。 ";
			link.l1 = "没问题。 把信给我。 ";
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = "不, 我的朋友, 我没有时间做那种废话。 ";
			link.l2.go = "Shadowtrader_fort_end";
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = "给你。 请今天交给他, 并把他的回复带给我。 ";
			link.l1 = "别担心, 我会的。 ";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = "好吧, 显然我得问问别人了。 抱歉打扰你了, 船长。 ";
			link.l1 = "没问题。 再见! ";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = "他是这么说的? 那他需要我提供什么证据? ! 我的尸体吗? 如果继续这样下去, 很快就会有一具了! ..";
			link.l1 = "嘿, 嘿, " + npchar.name+ ", 冷静点, 不然你会中风的。 来, 喝点水... 现在告诉我, 怎么了 —也许我能帮你? ";
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = "哦, 船长! 请拿上你的300比索 —我差点忘了... 当然, 我会告诉你, 但我不确定你能帮我什么。 我的生意几乎毁了 —都是因为那些该死的走私者和那个领导他们的不知名混蛋。 ";
			link.l1 = "走私者? ";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = "就是这样! 那些无赖显然是想把我赶出 town! 在那之前, 一切都很正常 —他们转售违禁品, 当巡逻队抓到他们时, 他们就躲起来或贿赂。 但最近他们在某个后街开了家店, 开始以难以置信的低价出售最受欢迎的商品! \n我负担不起这种奢侈 —事实上我必须纳税 —我逐渐 impoverish 自己, 水手们几乎不想要我的货物 —他们所有的货物都是从这些流氓那里买的。 ";
			link.l1 = "但你应该向当局上诉! 毕竟, 阻止这种无法无天是他们的工作。 ";
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = "你自己也看到了上次上诉的结果。 总督太忙了, 指挥官不相信走私者组织了后街商店, 或者假装不相信 —我想就是这种情况\n当然, 他们为什么要这么做? 我说: 我敢肯定, 某个想摧毁并把我赶出 town 的流氓想出了这一切, 然后他会悄悄地收拾我的生意, 来洗干净他们的脏手。 ";
			link.l1 = "嗯... 你的观点并非没有根据。 商人的本性就是 —让别人当替罪羊... 哦, 对不起, 我当然不是指你。 ";
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = "哦, 没什么... 最近有个衣衫褴褛的人来找我, 厚颜无耻地说如果我继续吵闹, 他们就会烧了我的商店\n所以我雇了个保镖。 " + pchar.questTemp.Shadowtrader.Guardername + "不便宜, 但他是个专业人士, 在他的保护下, 我能感到稍微平静一点。 ";
			link.l1 = "我明白了... 确实是个不愉快的故事。 显然, 你是对的 —我帮不了你什么。 但我仍然相信事情会自行解决 —这种阴暗的机构通常不会持续太久。 好吧, 祝你好运! ";
			link.l1.go = "Shadowtrader_end";
			link.l2 = "我明白了。 好吧, 也许我还是能帮你... ";
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = "你还是要帮我? 但你打算怎么做? ";
			link.l1 = "我会试着找到你那个‘同事’, 然后... 说服他不再找你麻烦。 你知道, 我在说服别人方面有一定的技巧。 ";
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = "你是认真的吗? 愿上帝保佑你正义的事业! 如果你能帮我摆脱那个垃圾, 我会欠你人情的。 ";
			link.l1 = "好的, 就这么定了。 那我开始找了。 ";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase("ся","ась"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = "是真的吗? 现在我可以毫无顾虑地做生意了? 哦, 太感谢你了! 这是你的奖励 —15000比索。 至于他们房子里的货物, 我想最好交给指挥官。 再次感谢! ";
			link.l1 = "不客气。 这并不难。 我告诉过你我很擅长说服别人。 ";
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = "船长, 再次光临 —我会一直很高兴见到你。 ";
			link.l1 = "当然! 现在请允许我告辞 —我还有事要做! 再见, 祝你生意兴隆, " + npchar.name+ "! ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DeleteAttribute(pchar, "questTemp.Shadowtrader.EndFort");
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		//<-- 迷你任务 不公平竞争
	}
	UnloadSegment(NPChar.FileDialog2);
}