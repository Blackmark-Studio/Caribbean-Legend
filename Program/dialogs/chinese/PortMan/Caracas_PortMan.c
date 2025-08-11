// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么问题? ", "你想要什么, " + GetAddress_Form(NPChar) + "? "), "你已经试过问我问题了, " + GetAddress_Form(NPChar) + "... ", "你今天已经第三次谈论某个问题了... ",
                          "听着, 如果你没有关于港口事务的事情告诉我, 就别用问题打扰我。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了。 ", "我没什么可谈的。 "), "没关系。 ", "确实, 已经第三次了... ", "抱歉, 但我现在对港口事务不感兴趣。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// belamour 传奇版与阿库拉联动任务 -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toCarPortOffice" || pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik" || pchar.questTemp.SharkGoldFleet == "buyincar")
				{
					link.l1 = "事实上, 我打算过几天带着从你们殖民地购买的货物前往贝洛港。 我想: 也许你有什么货物或事情可以让我顺路帮忙... 当然是有偿的。 ";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "LightVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "又见面了。 我把你的信送到了贝洛港。 那里的人让我给你一个答复。 ";
					link.l1.go = "SharkGoldFleet_09";
				}
				if(pchar.questTemp.SharkGoldFleet == "DifficultVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "你好。 我从贝洛港来找你。 当地港务局的同事让我把这封信交给你。 ";
					link.l1.go = "SharkGoldFleet_13";
				}
			}
			//< —与阿库拉联动任务
		break;
		
		// belamour 与阿库拉联动任务 -->
		case "SharkGoldFleet":
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.Fail21"))
			{
				pchar.questTemp.SharkGoldFleet = "toCurierDie";
				AddQuestRecord("SharkGoldFleet", "5");
				SGF_CreateCurierInWorld("");
				dialog.text = "感谢你的关心, 但我没有这样的差事。 实际上有过一个任务, 但你真的晚了几天: 我为此派了一艘高速信使双桅帆船。 ";
				link.l1 = "知道了... 好吧, 谢谢你。 ";
				link.l1.go = "exit";
			}
			else
			{
				if(!bImCasual) pchar.quest.SharkGoldFleet21.over = "yes"; 
				if(!bImCasual) pchar.quest.SharkGoldFleet30.over = "yes"; 
				if(GetCompanionQuantity(pchar) > 1)
				{
					pchar.questTemp.SharkGoldFleet = "toCurierWait";
					AddQuestRecord("SharkGoldFleet", "10");
					SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
					dialog.text = "我看你连一艘船都没有。 你一定是个富有的商人。 嗯... 但我认识所有当地有船队的商人, 却不认识你。 所以别怪我, 我不能把重要的事情托付给你。 ";
					link.l1 = "知道了... 好吧, 谢谢你。 ";
					link.l1.go = "exit";
				}
				else
				{
					if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
					{
						pchar.questTemp.SharkGoldFleet = "toCurierWait";
						AddQuestRecord("SharkGoldFleet", "11");
						SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
						dialog.text = "嗯... 我有个任务。 只是你的船不合适。 我需要一艘既快又强大的船, 而你的船不完全符合这些要求。 至少不能同时满足。 所以请原谅我。 ";
						link.l1 = "知道了... 好吧, 谢谢你。 ";
						link.l1.go = "exit";
					}
					else
					{
						if(!CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk"))
						{
							pchar.questTemp.SharkGoldFleet = "toCurierWait";
							AddQuestRecord("SharkGoldFleet", "12");
							SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
							dialog.text = "我有事要做... 而你有一艘好船。 它只是看起来不像商船。 而且, 据我所见, 你没有荷兰西印度公司的长期许可证。 别生气, 但你看起来不像商人。 我不能冒这个险。 ";
							link.l1 = "知道了... 好吧, 谢谢你。 ";
							link.l1.go = "exit";
						}
						else
						{
							if(pchar.questTemp.SharkGoldFleet != "toCarPortOffice" || GetSquadronGoods(pchar, GOOD_COFFEE) < 300 || GetSquadronGoods(pchar, GOOD_CHOCOLATE) < 300)
							{
								pchar.questTemp.SharkGoldFleet = "toCurierWait";
								AddQuestRecord("SharkGoldFleet", "13");
								SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
								dialog.text = "我有事要做... 而你有一艘好船。 只是现在我不明白你打算做什么贸易... 你说你要去贝洛港卖货, 但据我所知, 你没在我们殖民地买货。 别生气, 但你看起来不像商人。 我不能冒这个险。 ";
								link.l1 = "知道了... 好吧, 谢谢你。 ";
								link.l1.go = "exit";
							}
							else
							{
								dialog.text = "我有事要做。 当然, 我不认识你... 但说实话, 我只记得有名有姓的商船队商人。 其余的 —不记得了。 而且你有长期许可证, 一看就是经验丰富的商人。 不过, 你的船很有趣。 你为什么要用护卫舰做贸易? ";
								link.l1 = "哈, 这不是普通的护卫舰。 即使满载货物, 它也能达到很高的速度。 逃离海盗总是比与他们战斗更容易, 不是吗? 虽然我的船容量比普通商船小, 但风险要低得多。 ";
								link.l1.go = "SharkGoldFleet_01";
							}
						}
						
					}
					
				}
			}
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "嗯, 但你说得对! 西班牙人知道如何造船, 不是吗? 是的, 是的, 我一眼就看出这艘漂亮的船是我们造船厂生产的。 而且, 今天确实有人告诉我, 你从我们的商人那里买了一批咖啡和可可, 准备在贝洛港转售。 我告诉你, 这是一笔好交易。 不熟悉贸易的人不知道, 由于种植园的存在, 这些货物在这里很便宜, 而在贝洛港, 它们的需求量很大, 因为从那里它们会运往大都市。 ";
			link.l1 = "嗯, 事情就是这样, 先生。 为了几个比索, 我不会把船开那么远。 ";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "嗯, 说实话, 我确实有事情要你做。 而且很高兴你有这样一艘快速的船, 在紧急情况下还能反击。 ";
			link.l1 = "等等, 先生... 你的事情意味着我必须战斗... ? ";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "不, 不! 事实上, 我的任务再简单不过了。 我需要你把一封信送到贝洛港的港务局。 信是密封的, 不能打开。 也不需要和任何人谈论它, 通信... 私人的。 亲自交付。 期限是十天。 过了期限就没用了。 ";
			link.l1 = "就这么简单? 我能得到多少钱? ";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "五千比索。 就当是不用派信使双桅帆船去贝洛港了。 ";
			link.l1 = "你之前问我和我的船是怎么回事? ";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "别介意。 只是信件足够重要, 我必须确保它能到达收件人手中。 所以没什么特别的。 官僚主义... 对普通人来说, 这些文件没什么意思。 ";
			link.l1 = "好吧, 我同意。 把你的文件拿来。 我一到贝洛港, 就把它们带给你的同事。 十天内我会处理好, 别担心。 ";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "等一下。 对不起, 我完全忘了你的名字。 能告诉我吗? 我需要把它写在文件里。 ";
			link.l1 = "我叫安德烈亚斯.加西亚。 ";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "谢谢。 那么... 太好了。 记住, 必须是你亲自递交这份文件, 并且直接交到收件人手中。 给你。 奖金将由贝洛港的港务局局长发放给你。 祝你旅途愉快! ";
			link.l1 = "谢谢! 现在, 请原谅我。 ";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToPB10", 0, 0, 10, false);
			else NewGameTip("探索模式: 计时器已禁用。 ");
			AddCharacterSkillDontClearExp(pchar, SKILL_LEADERSHIP, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_SNEAK, 1);
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_SharkGoldFleet_1");
			AddQuestRecord("SharkGoldFleet", "14");
			pchar.questTemp.SharkGoldFleet = "toPBPortOffice";
		break;
		
		case "SharkGoldFleet_09":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "太好了! 你帮了我大忙。 有什么困难吗? ";
			link.l1 = "不, 没有困难。 不过, 你的同事骂你了: 他说你们这里都是吝啬鬼, 因为你们不派信使船, 而是让过往商人捎带, 甚至把费用挂在收件人身上。 他威胁说要向哈瓦那投诉... ";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "什么? ! 我是吝啬鬼? ! 他在那里把自己当成什么了? 首先, 拿着你的五... 不, 六千比索! 我真心感谢! ";
			link.l1 = "谢谢。 很高兴看到你的同事对你的看法是错误的。 ";
			link.l1.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			AddMoneyToCharacter(pchar, 6000);
			dialog.text = "其次, 这个恶棍似乎忘记了两个月前, 他把从加拉加斯到贝洛港, 再从那里到哈瓦那的商船维护费用都算在我头上了! 我们约定好他会支付第二段旅程的费用! 可他至今未还债务, 还答应上个月还清! 而我还是吝啬鬼... 是的, 我自己要向哈瓦那投诉他! ";
			link.l1 = "嗯, 当然, 你有马德里宫廷的热情... ";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			pchar.questTemp.SharkGoldFleet = "LightVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "不, 想想看... 太无耻了! 好吧, 我会再和他算账... 现在请原谅我: 我有急事要处理。 和你做生意很愉快! ";
			link.l1 = "祝你好运! ";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_13":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "太好了! 你帮了我大忙。 不过, 我派了一艘信使双桅帆船给他们, 他们却用一艘过往的船把答复还给了我。 是啊... 之后他们还抱怨说我们这里都是吝啬鬼。 ";
			link.l1 = "嗯, 也许他们是为了节省信使的费用... ";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			AddMoneyToCharacter(pchar, 5000);
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			pchar.questTemp.SharkGoldFleet = "DifficultVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "不是‘也许’, 而是肯定, 我告诉你! 好吧, 没关系。 给你, 这是你的报酬。 现在我有很多工作要做, 请原谅。 ";
			link.l1 = "嗯, 也许他们是为了节省信使的费用... ";
			link.l1.go = "exit";
		break;
		// <-- 与阿库拉联动任务
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}