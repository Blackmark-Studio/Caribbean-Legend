// 城市对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么样的问题啊, " + GetSexPhrase("年轻人", "姑娘") + "? ", "你需要什么, " + GetSexPhrase("帅哥", "美女") + "? 问吧。 "), "又问问题", "嘻嘻, 如果你不介意的话 --问题... ",
                          "" + GetSexPhrase("嗯, 你怎么不自己挑个美人呢? 我开始怀疑你了... ", "嗯, 你怎么不自己挑个美人呢? 恐怕我们这儿没有男孩子, 嘻嘻... ") + "", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了, 抱歉。 ", "其实, 算了。 "), "我... 抱歉, 目前我没有问题了。 ",
                      "你说得对, 这已经是第三次了。 请原谅我。 ", "也许下次吧, 夫人。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> 加斯科涅之重
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				DelLandQuestMark(npchar);
				link.l1 = "听着, 奥罗拉, 我今晚需要一个女孩。 我想带她回家。 你能安排一下吗? ";
                link.l1.go = "Gigolo";
			}	
			//<—— 加斯科涅之重 */
		break;
		
		//--> 加斯科涅之重
		case "Gigolo":
			dialog.text = "当然, 亲爱的。 你已经找到合适的姑娘了, 还是我来帮你找? ";
			link.l1 = "确实找到了。 我看中了一个叫露西尔的女孩。 ";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "你指的是露西尔.蒙田吗? ";
			link.l1 = "说实话, 我没问她的姓。 我只知道她是个年轻漂亮的金发女孩, 名叫露西尔。 ";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "是的, 这确实很符合她的描述。 好吧。 但告诉我, 为什么是她? 其他女孩不合你心意吗? ";
			link.l1 = "嗯, 你看... 她刚来这里工作, 所以我觉得她在‘这一行’还不够有经验, 不会让我的钱包负担太重。 ";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "你知道, 我喜欢白皮肤的金发女郎。 在这方面, 露西尔非常合适。 ";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "先生, 那不是真的! 她年轻漂亮又有经验, 我的客户都很欣赏她。 她会让你花很多钱。 和她过一夜要五千比索, 一分不少。 ";
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = "很贵, 但好吧。 拿你的钱。 ";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "太贵了! 我没有那么多钱。 以后再跟你说。 ";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "唉, 你说得对, 先生, 她漂亮又年轻, 但缺乏经验。 我的客户通常不会注意到她, 所以我才问。 但如果你真的喜欢朴实的女孩, 我觉得她是个不错的选择。 她会收你两千五百比索。 ";
				if (sti(pchar.money) >= 2500)
				{
					link.l1 = "唉, 她也可以。 拿你的钱。 ";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "太贵了! 我没有那么多钱。 以后再跟你说。 ";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "你不会是第一个, 帅哥。 有时我的客户会排队等着她的关注, 因为她和我们岛上的黑皮肤女孩很不一样。 她会收你四千五百比索。 ";
				if (sti(pchar.money) >= 4500)
				{
					link.l1 = "很贵, 但好吧。 拿你的钱。 ";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "太贵了! 我没有那么多钱。 以后再跟你说。 ";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "真的吗, 先生? 已经想家了? 我的克里奥尔人, 尤其是我的穆拉托人, 比这个悠闲的巴黎野猫更热情。 但唉, 这是你的选择。 她会收你三千比索。 ";
				if (sti(pchar.money) >= 3000)
				{
					link.l1 = "很贵, 但好吧。 拿你的钱。 ";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "太贵了! 我没有那么多钱。 以后再跟你说。 ";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "如你所愿, 亲爱的。 露西尔会在晚上十一点急切地等你。 另外, 她不得迟于早上七点回来。 如果你在午夜前不到, 她会接待另一个客户, 然后你就得等到第二天晚上才能带她走。 \n还有, 别想…以任何方式伤害她, 否则你会后悔的。 这是一个公平的警告, 亲爱的。 ";
			link.l1 = "别担心, 我会像对待爱人一样对待她, 而不是野蛮人。 我十一点来接她。 那在那之前我该做什么呢? ";
			link.l1.go = "Gigolo_4a";
		break;
		
		case "Gigolo_4a":
			dialog.text = "嗯, 我也不知道, 亲爱的。 去酒馆看看, 和酒保聊聊…";
			link.l1 = "好主意。 我就这么办。 祝你愉快! ";
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
			QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerDelLoc("fortfrance_brothel", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
			//NewGameTip("可用时间快进功能! 可通过操作菜单 (ENTER) 中的'自言自语'选项使用。 ");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部有通过return退出的情况, 别忘了做卸载
}