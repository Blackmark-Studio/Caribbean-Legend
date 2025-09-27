// 卢卡斯.罗登堡 - 荷兰西印度公司副总裁
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl"))
			{
				dialog.text = "说吧, 小子, 但要快。 我是个忙人。 ";
				link.l1 = "我听说你在雇佣船长。 ";
				link.l1.go = "Holl_start";	
			break;
			}
			dialog.text = "你有什么事找我吗? ";
			link.l1 = "不, 抱歉。 我这就走。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Second_time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "BaltazarEsc")
			{
				dialog.text = "你现在应该已经在去圣马丁的半路上了, 船长。 ";
				link.l1 = "我正在准备起航, 先生。 ";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "BaltazarCom")
			{
				dialog.text = "啊, 船长, 你来了! 我没看见你进来, 我刚读完里德布罗克的信。 你给人留下了深刻印象。 他称你为‘商人的守护者和海盗的 scourge。 公司的天赐之才! ’你对此怎么说? ";
				link.l1 = "我宁愿只是做一个普通的船长。 一个普通但富有的船长。 ";
				link.l1.go = "SantiagoTrip";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				dialog.text = "你为什么还在这里, 没有前往古巴? ! ";
				link.l1 = "是的, 是的, 我这就走, 先生。 ";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripFinal")
			{
				sld = characterFromId("Santiago_usurer");
				dialog.text = "啊, 船长! 我承认我开始担心了。 怎么样? ";
				link.l1 = "虽然有麻烦, 但我稍后再告诉你。 先谈正事。 " + GetFullName(sld) + "先生让我跟你说: ‘这个人必须死’。 然后杰拉迪会认为事情解决了。 另外, 他说这个决定是他们家族的意愿。 ";
				link.l1.go = "SantiagoTrip_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripComplete")
			{
				dialog.text = "很高兴见到你, 船长! 你来看我太好了。 ";
				link.l1 = "日安, 先生。 我想你还有另一份公司的工作给我? ";
				link.l1.go = "JacobBerg";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobTakeShip")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					dialog.text = "我告诉过你把船停泊好。 你是太蠢还是无知, 连直接的命令都不遵守? ";
					link.l1 = "都不是, 先生。 我这就去。 ";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "那么, 你已经把船停泊好了。 现在我把我的小型三桅船‘美凤’借给你。 你准备好立即开始执行这个任务了吗? 我的船装备精良, 随时可以起航, 所以你没什么可担心的。 ";
					link.l1 = "是的, 当然。 我准备好了, 罗登堡先生。 ";
					link.l1.go = "JacobBerg_6";
					DelLandQuestMark(npchar);
				}
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobLongway")
			{
				dialog.text = "你为什么还在这里? 马上去找隆威。 ";
				link.l1 = "抱歉, 我这就去。 ";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MirageTake")// 现在开始处理船只选择
			{
				int iMir = 0;
				int iMef = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG) iMef = 1;
				}
				}// 设置舰队中存在船只的标志。 
				RemoveItems(PChar, "JacobJournal", 1);// 删除范伯格的日志
				pchar.quest.MirageConvoyOver.over = "yes"; // 移除计时器
				if (iMir == 1 && iMef == 0)// 失去美凤号
				{
					dialog.text = "船长... 我已经知道你的航行情况了。 ";
					link.l1 = "哦, 真的吗? 那你一定知道... ";
					link.l1.go = "Jacob_lostMef";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 1)// 失去蜃楼号
				{
					dialog.text = "船长... 我已经知道你的航行情况了。 ";
					link.l1 = "是吗? 那你一定知道... ";
					link.l1.go = "Jacob_lostMir";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 0)// 这真的很糟糕
				{
					dialog.text = "船长... 我已经知道你的航行情况了。 ";
					link.l1 = "是吗? 那你一定知道... ";
					link.l1.go = "Jacob_failFull";
					DelLandQuestMark(npchar);
					break;
				}
					dialog.text = "你来了, 船长... 我已经知道你这次旅行的一切了。 ";
					link.l1 = "是吗? 那你一定知道... ";
			link.l1.go = "Jacob_complete";
			DelLandQuestMark(npchar);
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "去安提瓜。 现在。 ";
				link.l1 = "抱歉, 我这就去。 ";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink" || pchar.questTemp.HWIC.Holl == "FleetwoodCapture")
			{// 再次开始检查船只
				iMir = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					}
				}// 设置舰队中存在蜃楼号的标志。 
				pchar.quest.ToAntiguaOver.over = "yes"; // 移除计时器
				if (iMir == 0)// 失去蜃楼号
				{
					dialog.text = "我已得知你的到来, 船长。 我也知道你在战斗中失去了我的蜃楼号。 ";
					link.l1 = "你消息很灵通, 罗登堡先生。 尽管我尽了全力, 还是没能救下她。 ";
					link.l1.go = "Fleetwood_fail";
					DelLandQuestMark(npchar);
				}
				else
				{
					dialog.text = "我已得知你的到来, 船长。 我看到蜃楼号已安全靠岸。 这很好。 ";
					link.l1 = "一切都是按照你的指示, 先生。 你命令我杀了弗利特伍德, 他死了。 你命令我把蜃楼号带回当地港口, 她就在这里。 ";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
				}
				pchar.quest.Meifeng_fail.over = "yes";
				Group_DeleteGroup("Meifeng_Empty");
				sld = characterFromId("MeifengCap");
				sld.lifeday = 0;// 清理没有中国人的美凤号
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "Abby_prepare")
			{
				dialog.text = "啊, 你来了。 很高兴见到你。 正如承诺的, 我有另一个任务给你。 ";
				link.l1 = "我在听, 先生。 ";
				link.l1.go = "Abby";
				DelLandQuestMark(npchar);
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "啊, 很高兴见到你, 我的孩子。 你来得晚了, 我开始担心了。 你从阿比盖尔那里得到什么了吗? ";
				link.l1 = "不仅如此, 我还解决了你其他的问题。 我找到了那个岛和施努尔家丢失的财富。 所罗门很高兴, 阿比盖尔会同意你的求婚。 恭喜你, 先生! ";
				link.l1.go = "Abby_2";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "NotFindAbbyIsland")
			{
				dialog.text = "啊, 很高兴见到你, 我的朋友。 你从阿比盖尔那里得到什么了吗? ";
				link.l1 = "是的。 我和阿比盖尔以及她父亲谈过了。 有个问题, 先生: 她父亲丢失的财富。 阿比盖尔觉得自己配不上你, 她担心如果她这个没有嫁妆的女孩嫁给像你这样的绅士, 人们会八卦和窃窃私语。 我希望你能理解。 ";
				link.l1.go = "Abby_6";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "啊, 我的朋友! 我相信你带来了好消息? ";
				link.l1 = "你的计划成功了。 阿比盖尔会同意的。 恭喜你, 先生。 ";
				link.l1.go = "Abby_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokStart")
			{
				dialog.text = "我一直在等你。 我的孩子, 你处于极大的危险之中。 ";
				link.l1 = "你是什么意思? ";
				link.l1.go = "Merdok";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokDie")
			{
				dialog.text = "我在码头的特工告诉我你到了。 约汉.范.默登死了吗? ";
				link.l1 = "是的。 他和他的同伙都没了。 这是一场艰苦的战斗, 但我坚持下来了。 ";
				link.l1.go = "Merdok_4";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "我们没什么可谈的了, 船长。 ";
			link.l1 = "明白, 我这就走。 ";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "什么事? 时间就是金钱。 ";
		link.l1 = "抱歉, 我这就走。 ";
		link.l1.go = "exit";
		break;
		
//------------------------------------------------1 任务--------------------------------------------
		case "Holl_start":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "也许吧。 你是谁? 快说, 时间就是金钱。 ";
			link.l1 = "我是" +pchar.name+ "船长, 我的船可能对你有用。 ";
			link.l1.go = "Holl_start_0";			
		break;
		
		case "Holl_start_0":
			dialog.text = "嗯, 一块有待在坩埚中检验的未知合金。 ";
			link.l1 = "所以我才来这里, 先生。 ";
			link.l1.go = "Holl_start_1";			
		break;
		
		case "Holl_start_1":
			pchar.questTemp.HWIC.Holl.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "很好, 我们会看看你的成色。 好吧, 不管你叫什么船长, 你知道巴尔塔萨.里德布罗克吗? 不知道? 真幸运。 像他这样贪婪。 脾气暴躁的白痴是罕见的景象。 \n但似乎这些杰出的品质对这个人来说还不够, 所以他很聪明地在当地酒馆冒犯了一个名叫" + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + "的海盗, 当被冒犯的一方一摸到剑, 他就立刻叫了卫兵... ";
			link.l1 = "... 然后他们用第一根可用的绳子把海盗绞死了? ";
			link.l1.go = "Holl_start_2";			
		break;
		
		case "Holl_start_2":
			dialog.text = "没那么简单。 " + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + "不是普通的海盗, 而是荷兰私掠船船长, 经历过与英国人的最后两场战争的老兵。 当地纳税人相当喜欢他。 我对里德布罗克就不能这么说了。 ";
			link.l1 = "所以我们的私掠船船长还活着? ";
			link.l1.go = "Holl_start_3";			
		break;
		
		case "Holl_start_3":
			dialog.text = "是的, 但他非常生气。 这就是为什么里德布罗克吓得屁滚尿流。 ";
			link.l1 = "我想, 我的好运快要结束了。 我什么时候见里德布罗克先生? ";
			link.l1.go = "Holl_start_4";			
		break;
		
		case "Holl_start_4":
			dialog.text = "马上。 菲利普斯堡的好人正在等待一批糖的装运, 我们共同的熟人里德布罗克承诺运送这批糖。 我认为这个人连他靴子的皮革都不值, 但唉, 他为我们工作, 所以你去港口办公室。 在那里找到里德布罗克, 告诉他我命令他立即起航。 \n你要跟踪他, 并... 护送他安全到达菲利普斯堡。 我不想让" + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + "把公司的声誉和他的货物一起沉入加勒比海。 ";
			link.l1 = "呃, 护航任务。 这个... 不愉快的任务怎么支付? ";
			link.l1.go = "Holl_start_5";			
		break;
		
		case "Holl_start_5":
			dialog.text = "船长, 先做工作。 巴尔塔萨到达目的地后会付钱给你。 在菲利普斯堡! 不是戴维.琼斯的储物柜! 完成工作后向我汇报。 如果你成功了, 你可以指望我和公司的进一步资助。 解散。 ";
			link.l1 = "再见, 先生。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Create_Baltazar");
			pchar.questTemp.HWIC.Holl = "BaltazarEsc";
			NextDiag.TempNode = "Second_time";
			pchar.quest.HWIC_ReturnOfficer.over = "yes";// 让军官不再打扰
			pchar.questTemp.HWIC.CanTake.Holl = "true";// 标志荷兰任务已接取
		break;
		
//----------------------------------------------任务 1а--------------------------------------------	
		case "SantiagoTrip":
			dialog.text = "是的, 里德布罗克即使对荷兰人来说也是个吝啬的混蛋。 不管怎样, 他不再是我的 concern 了。 我们来谈谈你, 不管你叫什么船长。 我喜欢你的风格, 所以我要给你另一份工作。 这次我自己付钱。 ";
			link.l1 = "我在听, 先生。 ";
			link.l1.go = "SantiagoTrip_1";			
			AddSimpleRumourCity("啊, 所以你就是护送那个恶棍里德布罗克的勇敢船长? 我们都听说了... 他只付了你五千比索! 他在菲利普斯堡的酒馆里喝得烂醉, 不停地吹嘘。 如果我是你, 船长, 我会把他拖到街上揍一顿。 ", "Villemstad", 20, 3, "");// 关于1任务的传闻
		break;
		
		case "SantiagoTrip_1":
			dialog.text = "我需要一个人做一件非常重要的事。 你在里德布罗克的事情上做得很好, 所以公司认为我可以把这件事交给你。 ";
			link.l1 = "我想我很荣幸。 什么事? ";
			link.l1.go = "SantiagoTrip_2";
		break;
		
		case "SantiagoTrip_2":
			sld = characterFromId("Santiago_usurer");
			dialog.text = "我不能给你确切的细节, 但要知道这不是我的工作, 这是公司的, 所以你有机会得到我们的好感, 我向你保证这是非常有利可图的。 \n航行到古巴的圣地亚哥, 把这个包裹交给唐" + GetFullName(sld) + "。 他在杰拉迪的银行有很高的职位, 也是我的... 我们的商业伙伴。 你要把我现在给你的这些黄金交给他。 我相信你的诚实, 船长。 嗯, 如果不是你的诚实, 那就是你的生存本能。 公司总是能找到那些试图偷我们东西的人。 ";
			link.l1 = "你怀疑我吗, 先生? ";
			link.l1.go = "SantiagoTrip_3";
		break;
		
		case "SantiagoTrip_3":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) sTemp = " 我还会给你这张公司的短期贸易许可证, 以免你与西班牙人发生任何外交纠葛。 这将允许你在一段时间内停靠西班牙殖民地。 ";
			else sTemp = "";
			dialog.text = "目前, 我不怀疑你。 相信我, 如果我怀疑, 我甚至不会和你谈论这件事。 要知道我们为这个工作排了很长时间的队, 所以你只有十五天的时间交付。 " + sTemp + "\n我的口信和包裹必须按时交付。 这很重要, 小子。 快点, 但要小心, 这不是一次轻松的航行。 ";
			link.l1 = "还有别的吗? 你为什么警告我, 罗登堡先生? ";
			link.l1.go = "SantiagoTrip_4";
		break;
		
		case "SantiagoTrip_4":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) GiveNationLicence(HOLLAND, 20);
			dialog.text = "这么说吧, 我有我的怀疑。 别担心, 如果你像上次一样快, 那么你将有机会成为公司处理微妙事务的有价值的代理人。 ";
			link.l1 = "我所要做的就是在十五天内把这封信和钱交给圣地亚哥的银行家? 表面上听起来不算太难。 ";
			link.l1.go = "SantiagoTrip_5";
		break;
		
		case "SantiagoTrip_5":
			dialog.text = "别急, 小子... 我想你并没有真正理解这种情况的严重性。 做这个工作会让我非常感激你。 另一方面, 失败会让我非常生气。 在那种情况下, 我会对你撒尿。 我们互相理解吗, " +GetFullName(pchar)+ "船长? ";
			link.l1 = "明白了。 我向你保证。 我会尽力让你保持好心情。 ";
			link.l1.go = "SantiagoTrip_6";
		break;
		
		case "SantiagoTrip_6":
			dialog.text = "很好。 现在, 拿着这封信, 这些箱子, 记住条款和条件。 还有一件事: 在圣地亚哥不要惹麻烦。 ";
			link.l1 = "好的。 ";
			link.l1.go = "SantiagoTrip_7";
		break;
		
		case "SantiagoTrip_7":
			DialogExit();
			GiveItem2Character(pchar, "NPC_Letter");
			ChangeItemDescribe("NPC_Letter", "itmdescr_NPC_Letter4");
			TakeNItems(pchar, "chest", 5); 
			if(bImCasual)
			{
				NewGameTip("探索模式: 任务持续时间加倍");
				SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 32, false);
			}
			else SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 16, false); // 计时器
			AddQuestRecord("Holl_Gambit", "1-43");
			pchar.questTemp.HWIC.Holl = "SantiagoTripBegin";
			AddMapQuestMarkCity("Santiago", true);
			AddLandQuestMark(characterFromId("Santiago_usurer"), "questmarkmain");
		break;
		
		case "SantiagoTrip_8":
			dialog.text = "‘必须死’... 就这样。 我没想到会这样。 嗯。 你做得很好, 船长。 现在给我做个汇报。 ";
			link.l1 = "没什么特别的... 很轻松。 ";
			link.l1.go = "SantiagoTrip_9";
			link.l2 = "我在圣地亚哥被一个人打晕并绑架了。 他对你和杰拉迪的生意很感兴趣。 我设法逃脱了, 但不得不先杀了他。 他唯一透露的线索是一个叫加斯顿的人的名字, 我不知道这一切是怎么回事。 ";
			link.l2.go = "SantiagoTrip_10";
			link.l3 = "我在圣地亚哥被一个人打晕并绑架了。 他对你和杰拉迪的生意很感兴趣。 我设法逃脱了, 但不得不先杀了他。 在送他下地狱之前, 我没能从他那里得到任何信息。 ";
			link.l3.go = "SantiagoTrip_11";
		break;
		
		case "SantiagoTrip_9":
			dialog.text = "公司的感激不仅仅是口头上的。 拿着你的奖励, 你应得的。 ";
			link.l1 = "为公司工作相当有利可图。 ";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_10":
			dialog.text = "什么! 绑架... 等等, 不过... 加斯顿! 我明白... 我想。 唉, 我的孩子, 你被卷入了一件肮脏的事情。 我们处于未知的水域, 所以我们必须看看它如何发展。 很高兴你活着回来。 \n让我们谈些更愉快的事情 —接受这个奖励, 这是你应得的。 ";
			link.l1 = "为公司工作相当有利可图";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_11":
			dialog.text = "胡说! 绑架你... 不过我有一些怀疑。 如果你继续为我工作, 你会了解更多。 你很幸运, 我很高兴你能回来。 \n让我们谈些更愉快的事情 —接受这个奖励, 这是你应得的。 ";
			link.l1 = "为公司工作相当有利可图";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_12":
			AddMoneyToCharacter(pchar, 25000);
			dialog.text = "正是如此, 我的孩子! 如果你继续和我们合作, 你可以成为公司报酬丰厚的代理人。 现在去吧, 从你的航行中休息一下。 你没有辜负我的期望。 如果你一周后回来, 我会非常感激, 我们还有很多工作要做。 ";
			link.l1 = "你可以指望我, 罗登堡先生。 ";
			link.l1.go = "SantiagoTrip_13";
		break;
		
		case "SantiagoTrip_13":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "true";
			AddQuestRecord("Holl_Gambit", "1-46");
			AddCharacterExpToSkill(pchar, "Sailing", 100);// 导航
			AddCharacterExpToSkill(pchar, "Sneak", 100);// 隐蔽性
			AddCharacterExpToSkill(pchar, "Leadership", 80);
			AddSimpleRumourCity("我在公司的兄弟说罗登堡先生对你的表现非常满意, 船长。 别失去机会, 卢卡斯很少表现出这样的好感。 ", "Villemstad", 10, 3, "");
			SetTimerFunction("GollandGambit_2_ZadanieStart", 0, 0, 7);
		break;
		
//-----------------------------------------------2 任务--------------------------------------------
		case "JacobBerg":
			dialog.text = "你很聪明, 船长。 正是如此。 好吧, 让我们谈谈即将到来的任务的细节... ";
			link.l1 = "我洗耳恭听。 ";
			link.l1.go = "JacobBerg_1";			
		break;
		
		case "JacobBerg_1":
			dialog.text = "我有一个非常严肃和重要的任务给你, 我希望你按照我的指示去做。 如你所知, 联合省和英国之间的关系... 不友好。 英国人确信他们应该统治世界。 问题是 —不是每个人都倾向于同意这种说法。 无论他们去哪里做生意, 放心, 荷兰西印度公司已经先到了那里。 \n我们荷兰人拥有世界上最大的贸易舰队, 我们的军事中队可以在这里和国外捍卫共和国的利益。 英国人嫉妒我们的贸易实力, 他们正在尽其所能破坏公司的活动。 现在, 有一个名叫理查德.弗利特伍德的英国海军船长。 尽管是英联邦的委任军官, 他目前却像海盗一样活动。 他攻击和掠夺任何在加勒比海悬挂荷兰国旗的船只。 他解释自己的行为是对‘幽灵船’的反击, 这艘船击沉英国商船。 他声称这艘‘幽灵船’是一艘悬挂荷兰私掠许可证的私掠船。 \n你听说过‘幽灵船’吗, 船长? ";
			link.l1 = "你可以在任何酒馆听到这种无稽之谈。 只要给老水手买些朗姆酒, 你就会听到任何你想听的故事... ";
			link.l1.go = "JacobBerg_2";
		break;
		
		case "JacobBerg_2":
			dialog.text = "这不是醉汉的幻想。 我调查了这艘‘幽灵船’的行为。 我发现她是一艘木制帆布船, 由普通人组成, 一艘名为‘幻影’的双桅船。 她由一个名叫雅各布.范.伯格的人指挥, 他把她冒充为传说中的‘飞翔的荷兰人’。 ";
			link.l1 = "范.伯格? 那是荷兰姓氏。 真正的‘飞翔的荷兰人’啊? ";
			link.l1.go = "JacobBerg_3";
		break;
		
		case "JacobBerg_3":
			dialog.text = "正确。 雅各布.范.伯格是荷兰人, 原籍莱顿。 但共和国很久以前就判处他绞刑。 他是一个在逃的罪犯, 一个只按自己利益行事的海盗。 理查德.弗利特伍德正在追捕范.伯格。 这个事实我们将用来对付那个傲慢的英国佬。 \n我不想直接杀了弗利特伍德, 尽管他早就该受死了。 死亡对他来说还不够。 我不仅想杀了他, 还想摧毁他的名声和荣誉。 这就是我想要的。 这也将给其他傲慢的英国猪一个教训。 \n让我们谈谈细节。 ";
			link.l1 = "先生, 这听起来像是私事... ";
			link.l1.go = "JacobBerg_4";
		break;
		
		case "JacobBerg_4":
			dialog.text = "这不关你的事。 你会服从命令, 然后得到报酬。 多亏了我的特工, 我已经知道雅各布.范.伯格和他的‘幻影’号藏在哪里。 他在西班牙大陆南部的一个城市活动。 去找他, 查明他把他的幽灵船停泊在哪里\n然后杀了他, 找到他的‘幻影’号, 把她作为战利品, 并把她带回这里。 你必须捕获‘幻影’号, 甚至不要想击沉她。 ";
			link.l1 = "听起来足够简单。 我该去哪里找范.伯格? ";
			link.l1.go = "JacobBerg_5";
		break;
		
		case "JacobBerg_5":
			dialog.text = "所有细节将由我的特工提供给你。 他叫隆威, 一个中国人。 我把我个人的船, 小型三桅船‘美凤’号交给你执行这个任务。 隆威是她的船长, 但他会听从你的命令。 \n去当地的港口办公室, 把你所有的船只停泊在那里。 完成后回来见我。 ";
			link.l1 = "好的, 我会去见港口主管。 我不会让你等太久。 ";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Holl = "JacobTakeShip";
			AddLandQuestMark(characterFromId("Villemstad_portman"), "questmarkmain");
		break;
		
		case "JacobBerg_6":
			dialog.text = "隆威在外面等你。 他会带你去看你的新船, 并给你一些关于范.伯格位置的信息。 祝你好运, 船长, 别让我失望。 记住你必须把‘美凤’号还给我, 所以在夺取‘幻影’号时尽量不要击沉她。 ";
			link.l1 = "我这就去! ";
			link.l1.go = "JacobBerg_7";	
		break;
		
		case "JacobBerg_7":
			DialogExit();
			pchar.quest.Create_Longway.win_condition.l1 = "location";
			pchar.quest.Create_Longway.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Create_Longway.function = "Create_Longway";
			pchar.questTemp.HWIC.Holl = "JacobLongway";
			AddQuestRecord("Holl_Gambit", "1-7");
			pchar.questTemp.HWIC.TakeQuestShip = "true";// 所有港口不可用直到任务完成, 船也不能卖
			pchar.questTemp.HWIC.HollEquip = "true";// 士兵装备
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");// 其他选项不再可能
		break;
		
		// 混乱继续
		case "Jacob_lostMir":
			dialog.text = "你这个无能的傻瓜。 你未能完成捕获海盗船的任务。 我所有的计划都毁了。 我要把‘美凤’号从你那里拿走。 出去, 我们不再需要你了。 ";
			link.l1 = "对不起。 再见, 罗登堡先生。 ";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
		break;
		
		case "Jacob_lostMef":
			dialog.text = "你这个该死的白痴。 你失去了‘美凤’号。 这是不可接受的... 我要把‘幻影’号从你那里拿走, 并扣留你的报酬作为我损失的补偿。 出去, 我们不再需要你了。 ";
			link.l1 = "对不起。 再见, 罗登堡先生。 ";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MIRAGE;
		break;
		
		case "Jacob_failFull":
			dialog.text = "我的上帝, 你真是个罕见的标本。 一个无能的笨蛋和白痴。 你没能捕获蜃楼号, 还把美凤号也弄丢了。 滚出我的办公室! ";
			link.l1 = "我这就走。 ";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");// 从军官中移除隆威
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");// 开放港口
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Jacob_complete":
			dialog.text = "做得好。 你成功的消息已经传到我耳朵里了。 范.伯格死了, 你捕获了他的船。 你的报酬是5万比索, 拿着。 \n我要把‘美凤’号从你那里收回。 现在你该指挥‘幻影’号了, 她将在下一阶段扮演重要角色。 你准备好了吗? ";
			link.l1 = "是的, 罗登堡先生。 ";
			link.l1.go = "Fleetwood";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			AddSimpleRumourCity("他们说你正在为罗登堡先生本人执行特殊任务。 关于把那些英国人沉入海底的事情。 看来你是个上升的人, 船长。 ", "Villemstad", 15, 3, "");
		break;
		
		case "Jacob_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			sld = characterFromId("Longway");
			sld.lifeday = 0;
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");// 开放港口
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumourCity("他们说你让罗登堡先生失望了。 祝你好运, 你会需要的。 ", "Villemstad", 20, 3, "");
		break;
		
//----------------------------------------------3 任务-------------------------------------------------
		
		case "Fleetwood":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "现在我们对付弗利特伍德。 你要用他一直热衷追捕的‘幽灵船’蜃楼号来引诱他出来。 在多米尼加附近设下陷阱, 蜃楼号将作为诱饵。 \n首先, 你要让弗利特伍德知道蜃楼号在多米尼加附近被发现。 我们勇敢的英国佬会放下手头的一切, 立即冲向多米尼加寻找他的猎物。 不要直接和弗利特伍德说话, 否则你活不下来。 在圣约翰找一家药店。 药剂师约翰.默多克是我的老朋友。 \n告诉他你在我的指挥下行动, 他会帮助你找到当地人, 向他们灌输关于‘幽灵船’在多米尼加附近攻击英国商人的有趣谎言。 ";
			link.l1 = "我能做到。 目标是在多米尼加伏击弗利特伍德, 对吗? ";
			link.l1.go = "Fleetwood_1";
		break;
		
		case "Fleetwood_1":
			dialog.text = "正是。 隆威和‘美凤’号会在多米尼加附近等你。 你们两个可以轻松拿下那只英国狗。 登上他的船, 搜查他的船舱。 我想要他的航海日志。 我会为此额外付钱。 \n但你的首要任务是杀死那个混蛋弗利特伍德, 所以如果登船不切实际 —就把他沉入海底。 最重要的是你必须不惜一切代价保护‘幻影’号。 她在计划的下一阶段有重要作用。 ";
			link.l1 = "明白了。 ";
			link.l1.go = "Fleetwood_2";
		break;
		
		case "Fleetwood_2":
			dialog.text = "建议你, 船长。 不要在圣约翰锚泊。 在岛上的一个海湾登陆, 穿过丛林步行到城市, 否则约翰不会和你说话。 如果你太引人注目, 他会假装不认识你。 另外, 在海上要小心 --‘幻影’号在英国殖民地臭名昭著, 所以如果你不想被一群海狼攻击, 就避开他们的军舰和定居点。 就这样。 上帝与你同在。 ";
			link.l1 = "是, 是。 ";
			link.l1.go = "Fleetwood_3";
		break;
		
		case "Fleetwood_3":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toAntigua";
			AddQuestRecord("Holl_Gambit", "1-15");
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			SetFunctionTimerCondition("ToAntiguaOver", 0, 0, 60, false); // 计时器 2 个月
			AddMapQuestMarkShore("Shore1", false);
			AddMapQuestMarkShore("Shore2", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Fleetwood_complete":
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink")// 弗利特伍德与日志一起沉没
			{
				dialog.text = "你回来了, 船长... 你有理查德.弗利特伍德的航海日志吗? ";
				link.l1 = "不幸的是没有。 在他凿沉船之前, 我没有机会登船。 ";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			if (!CheckCharacterItem(pchar, "FleetwoodJournal"))
			{
				dialog.text = "你回来了, 船长... 你有理查德.弗利特伍德的航海日志吗? ";
				link.l1 = "不幸的是, 没有。 我设法登上了‘瓦尔基里’号, 在肉搏战中杀死了那个人, 但我没有找到他的日志。 他的一个手下点燃了弹药库, 我们只有几秒钟的时间逃生。 ";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			dialog.text = "你回来了, 船长... 你有理查德.弗利特伍德的航海日志吗? ";
			link.l1 = "我有。 给你。 我设法登上了‘瓦尔基里’号, 尽管这很危险。 那混蛋点燃了他的弹药库, 把船炸上了天。 我们侥幸逃生。 ";
			link.l1.go = "Fleetwood_complete_2";
		break;
		
		case "Fleetwood_complete_1":
			AddMoneyToCharacter(pchar, 100000);
			dialog.text = "真该死, 这本来可以回答我们很多问题。 现在没关系了。 你杀了那个傲慢的英国狗, 这才是最重要的。 这是你的奖励 —10万比索。 我要把‘幻影’号从你那里拿走, 我们要把这艘船送回英国。 ";
			link.l1 = "什么鬼? ! 她是一艘好船, 我想留着她! ";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_2":
			AddMoneyToCharacter(pchar, 150000);
			RemoveItems(PChar, "FleetwoodJournal", 1);
			dialog.text = "太好了! 你是个非常有能力的人。 如果我们所有的船长都像你一样, 荷兰共和国将成为历史上最伟大的海洋国家之一。 这是你的奖励 —10万比索, 还有5万比索作为日志的额外奖励。 我要把‘幻影’号从你那里拿走, 我们要把这艘船送回英国。 ";
			link.l1 = "什么鬼? ! 她是一艘好船, 我想留着她! ";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_3":
			dialog.text = "我的孩子, 你是个优秀的士兵, 但相信我和我在政治事务上的经验。 还记得我对弗利特伍德的评价吗? 我要把他的名字和声誉钉在磨石上, 扔进深渊。 而这些来自皇家港的傲慢贵族将不得不吞咽下去, 窒息而死。 \n我们要让理查德.弗利特伍德成为‘幽灵船’蜃楼号的船长, 一个让英格兰和荷兰两国互相争斗的狼人, 掠夺。 抢劫和谋杀两国的和平公民, 只是为了让自己发财! 多么讽刺! 我已经准备了证据和证人, 但‘幻影’号将成为我完美计划的主要事件。 ";
			link.l1 = "好吧, 去他妈的。 你要为了你的计划牺牲我出色的船! ? ";
			link.l1.go = "Fleetwood_complete_4";
			AddDialogExitQuestFunction("Lucas_ExangeShip");
		break;
		
		case "Fleetwood_complete_4":
			dialog.text = "注意你的言辞, 小子, 这是战争。 有时我们不仅要牺牲人, 还要牺牲船只和富裕的定居点来实现我们的政治目标。 每场战争都有损失... 说到损失, 我有个坏消息要告诉你。 \n你不在的时候, 威廉斯塔德遭到了英国私掠船的袭击。 堡垒设法将他们赶走, 但在他们用纵火船进入港口之前。 \n你的船被锚泊在那里, 被烧成了水线以下。 她完全损失了";
			link.l1 = "先生, 你现在一定是在开玩笑。 该死的! 我现在该怎么办? ! ";
			link.l1.go = "Fleetwood_complete_5";			
		break;
		
		case "Fleetwood_complete_5":
			dialog.text = "别这么沮丧, 船长, 我也有好消息。 为了缓解你的愤怒, 我把我的‘美丽的风’, 小型三桅船‘美凤’号给你。 你可以在合理范围内自由使用这艘船。 另外, 明天在总督府见我, 你已被提名获得荷兰共和国和西印度公司的国家奖项。 在你收到之前不要离开城镇, 船长。 ";
			link.l1 = "这确实减轻了我的损失。 我很荣幸。 顺便问一下, 先生, 隆威去哪里了? ";
			link.l1.go = "Fleetwood_complete_6";
		break;
		
		case "Fleetwood_complete_6":
			dialog.text = "我命令隆威驶往多米尼加后, 他突然失踪了。 我怀疑英国特工袭击了他... 或者也许不是。 我正在调查。 ";
			link.l1 = "我明白了。 他在多米尼加的帮助将是非常受欢迎的。 弗利特伍德和他的‘瓦尔基里’号是一对可怕的组合。 我希望隆威还活着... 再见, 先生! ";
			link.l1.go = "Fleetwood_complete_7";
			pchar.questTemp.HWIC.Holl = "Award";
			AddQuestRecord("Holl_Gambit", "1-24");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
		break;
		
		case "Fleetwood_complete_7":
			DialogExit();
			pchar.quest.Award_FromLucas.win_condition.l1 = "Timer";
			pchar.quest.Award_FromLucas.win_condition.l1.date.hour  = 8.00;
			pchar.quest.Award_FromLucas.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l2 = "location";
			pchar.quest.Award_FromLucas.win_condition.l2.location = "Villemstad_townhall";
			pchar.quest.Award_FromLucas.function = "AwardFromFromLucas";
			AddSimpleRumour("告诉我, 船长, 那个该死的英国狗弗利特伍德真的要为掠夺英国‘和’荷兰商人负责吗? 真的吗? 这样一个狡猾的家伙! 你消灭了这个混蛋, 真是太好了。 你是个真正的英雄, 船长! ", HOLLAND, 10, 3);
		break;
		
		case "Fleetwood_fail":
			dialog.text = "你不只是一个普通的小丑, 你是整个马戏团。 我们离最后一幕如此之近, 你却搞砸了... 我会为弗利特伍德的死付给你3万比索。 我没有更多的任务给你, 我们的安排结束了。 出去。 ";
			link.l1 = "如你所愿。 ";
			link.l1.go = "Fleetwood_fail_1";			
		break;
		
		case "Fleetwood_fail_1":
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "我有个坏消息要告诉你。 \n你不在的时候, 威廉斯塔德遭到了英国私掠船的袭击。 堡垒设法将他们赶走, 但在他们用纵火船进入港口之前。 \n你的船被锚泊在那里, 被烧成了水线以下。 她完全损失了。 ";
			link.l1 = "我想我只能去他妈的了! 什么都不感谢! ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");// 可以使用港口
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Holl = "end";
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumour("告诉我, 船长, 你真的击沉了那个该死的英国狗弗利特伍德吗? 真的吗? 你消灭了这个混蛋, 做得好, 船长! ", HOLLAND, 15, 3);
		break;
		
		case "LucasAward":
			dialog.text = ""+ PChar.name+ "船长! 由于你消灭了危险的国家罪犯理查德.弗利特伍德, 揭露了英国对共和国的阴谋, 表现出勇敢和勇气, 代表荷兰共和国授予你一千枚金杜卡特! \n你还将获得这个有价值的导航工具 —任何军事水手的梦想。 ";
			link.l1 = "我很高兴为共和国服务! ";
			link.l1.go = "LucasAward_1";			
		break;
		
		case "LucasAward_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Bek_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			GiveItem2Character(pchar, "bussol");
		break;
		
		case "LucasAward_2":
			dialog.text = "再次恭喜你, 我的朋友。 请在一周后来看我。 我们需要你处理一件极其微妙的事情。 ";
			link.l1 = "明白了, 罗登堡先生。 我一周后来看你。 ";
			link.l1.go = "LucasAward_3";			
		break;
		
		case "LucasAward_3":// 整理一下
			LAi_SetActorType(pchar);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-25");
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_ActorGoToLocator(sld, "goto", "goto6", "BekSitDown", -1);
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("LucasGuard_"+i);
				sld.lifeday = 0;// 清理士兵
			}
			sld = characterFromId("Lucas");
			LAi_ActorGoToLocator(sld, "reload", "reload1", "LucasReturnInCabinet", -1);
			bDisableFastReload = true;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			SetTimerFunction("GollandGambit_4_ZadanieStart", 0, 0, 7);
			AddSimpleRumourCity("他们说你被马蒂亚斯.贝克亲自授予了国家奖项! 共和国应该为有你这样的人感到自豪, 船长! ", "Villemstad", 20, 4, "");
		break;
		
//--------------------------------------------------4 任务----------------------------------------------
		
		case "Abby":
			dialog.text = "让我给你讲个故事。 这将帮助你理解你下一个任务的微妙性。 几个月前, 一艘悬挂英国国旗。 驶往威廉斯塔德的福禄特船遭到了已故雅各布.范.伯格的袭击。 他夺取了这艘船, 并在一个不在我们任何地图上的岛屿附近凿沉了它。 福禄特船上只有两名乘客幸存。 一个名叫所罗门.施努尔的犹太人和他的女儿阿比盖尔。 所有其他乘客都遇难了, 包括他们的其他家人。 我们的两个犹太人通过漂浮在一些残骸上到达了那个岛。 \n所罗门甚至设法拖着一个装满家族黄金的箱子。 他很节俭。 我们故事的另一个角色, 理查德.弗利特伍德, 正在附近航行, 听到了战斗的声音。 他到达时太晚了, 没能抓住范.伯格, ‘幻影’号逃跑了。 弗利特伍德决定检查岛上是否有幸存者\n他从那个荒岛上救了所罗门和阿比盖尔, 使他们免于死亡。 不幸的是, 老犹太人所罗门没有水手的眼光。 他把理查德的‘瓦尔基里’号误认为是雅各布的‘幻影’号 —害怕海盗回来完成任务 —把他的黄金藏在岛上的某个地方。 结果, 他和他的女儿身无分文地来到这里, 被弗利特伍德送到威廉斯塔德附近的布兰卡泻湖, 他们的原定目的地。 \n所罗门告诉我这个故事。 荷兰共和国支持宗教自由实践。 作为该政策的一部分, 公司支持这里的犹太社区。 因此, 我确保他们有地方住, 有吃有穿。 我经常去他们家。 阿比盖尔是一个... 非凡的年轻女子。 真诚而信任他人\n我不会对你撒谎, 船长, 我想要她, 我打算让她成为我的妻子。 她也爱我, 但有件事阻碍了我们。 ";
			link.l1 = "她父亲不太喜欢非犹太女婿? ";
			link.l1.go = "Abby_0";			
		break;
		
		case "Abby_0":
			dialog.text = "哈! 老所罗门如果我娶了阿比盖尔, 会欣喜若狂, 不管我是不是未受割礼的女婿。 事实上, 他催促她接受我的求婚。 不, 不, 这超出了犹太人和非犹太人的范畴。 我请你, 我的孩子, 为我解决这个问题。 和阿比盖尔谈谈, 找出哪里出了问题\n你是个陌生人, 她可能会告诉你一些由于她迷人的谦逊而永远不会告诉熟人的事情。 施努尔的房子位于公司办公室的右边, 如果你背对着它的话。 我知道你是个能言善辩的人\n但记住一件事: 理查德.弗利特伍德是‘幽灵船’的真正船长... 和阿比盖尔谈话时记住这一点。 ";
			link.l1 = "哈! 当然我记得, 罗登堡先生。 毕竟这不是官方承认的事实吗? 我不会浪费时间, 我会立即去拜访你的心上人。 ";
			link.l1.go = "Abby_1";			
		break;
		
		case "Abby_1":
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);// 打开阿比的家
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyInHouse";
			AddQuestRecord("Holl_Gambit", "1-26");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abby_2":
			dialog.text = "你真的找到了所罗门藏黄金的那个岛吗? 这太好了! 我开始认为你能完成任何任务... 你在藏匿处还发现了什么吗? ";
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.ScullnotReturn"))
			{
				link.l1 = "没有, 没别的。 只有钱。 ";
				link.l1.go = "Abby_3";
			}
			else
			{
				link.l1 = "有一个有趣的物品 - 一个玉骷髅。 我把它给了所罗门, 他说那是传家宝。 他还说你打算从他那里买下它... ";
				link.l1.go = "Abby_4";
			}
		break;
		
		case "Abby_3":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "嗯。 那好吧。 不过很奇怪。 不管怎样... 我欠你, 先生, 我永远不会忘记。 我为你准备了一份奖励 - 5万比索和这个护身符。 现在它是你的了。 ";
			link.l1 = "谢谢你, 罗登堡先生! ";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_4":
			pchar.questTemp.HWIC.Holl.LucasItem = "totem_04";
			dialog.text = "太好了! 是的, 我打算从所罗门那里买下这件文物, 他不需要它, 我有一个非常慷慨的买家。 我为你准备了一份奖励 - 5万比索和这个护身符。 现在它是你的了。 ";
			link.l1 = "谢谢你, 罗登堡先生! ";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_5":
			dialog.text = "我目前没有值得你这样的船长做的工作。 但不要离开库拉索太久, 很快我就会再次需要你的服务。 ";
			link.l1 = "我知道了, 先生。 再见! ";
			link.l1.go = "exit";
			GiveItem2Character(pchar, pchar.questTemp.HWIC.Holl.LucasItem);
			AddMoneyToCharacter(pchar, 50000);
			pchar.questTemp.HWIC.Holl = "Merdok_wait";
			AddQuestRecord("Holl_Gambit", "1-34");
			DelMapQuestMarkCity("Villemstad");
			SetTimerFunction("GollandGambit_5_ZadanieStart", 0, 0, 10);
			AddSimpleRumourCity("你听说最新消息了吗? 罗登堡先生要娶老疯犹太所罗门的漂亮女儿阿比盖尔.施努尔了。 我能说什么呢, 她是个幸运的女孩。 愿上帝保佑, 她会在婚礼前受洗成为真正的基督徒! ", "Villemstad", 20, 3, "");
		break;
		
		case "Abby_6":
			dialog.text = "哈, 就这样? 显然荒谬... 太像女人了。 听我说, 我的孩子, 这个问题很容易解决。 我知道所罗门的藏匿处有多少钱: 20万比索。 我准备拿出这笔钱来换取我和阿比盖尔的幸福。 我会把钱给你, 你离开库拉索一两周。 然后你回到所罗门那里, 把钱给他。 假装你找到了藏匿处。 狼会吃饱, 羊也不会受伤。 这里, 拿着所需的金额";
			link.l1 = "一个好而简单的计划。 我们就这样做。 ";
			link.l1.go = "Abby_7";
		break;
		
		case "Abby_7":
			dialog.text = "出海, 十天后回到我这里。 去做些有成效的事。 寻找曼加.罗莎, 制作一些材料, 或者别的什么。 ";
			link.l1 = "随你说, 罗登堡先生。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 200000);
			pchar.questTemp.HWIC.Holl = "GiveLucasMoney";
			SaveCurrentQuestDateParam("questTemp.HWIC.Holl.LucasMoney");
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";
			AddQuestRecord("Holl_Gambit", "1-35");
		break;
		
		case "Abby_8":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "太棒了! 你又一次完美地完成了任务。 我欠你, 先生, 我永远不会忘记。 我为你准备了一份奖励 - 5万比索和这个护身符。 现在它是你的了。 ";
			link.l1 = "谢谢你, 罗登堡先生! ";
			link.l1.go = "Abby_5";
		break;
		
//-------------------------------------------5 任务-------------------------------------------------
		case "Merdok":
			dialog.text = "是的, 正是如此。 我的朋友, 有时很难看清谁是你的朋友, 谁是你的敌人。 有时你会错过最亲密的伙伴变成 nemesis 的时刻。 我们在圣约翰的共同熟人约翰.默多克 - 也被称为约汉.范.默登 - 是公司的前特工, 他已经把自己卖给了英国海军。 \n他的最新任务是消灭公司最耀眼的明星之一... 你。 ";
			link.l1 = "我很荣幸。 很高兴你告诉我, 否则我不会料到。 ";
			link.l1.go = "Merdok_1";
		break;
		
		case "Merdok_1":
			dialog.text = "正是, 船长。 他是个狡猾的狗。 在他动手之前找到那个混蛋并杀了他。 航行到安提瓜, 寻找他药店的秘密入口。 教堂前面有一个舱口, 通向一条秘密隧道。 使用它。 ";
			link.l1 = "我会处理的。 ";
			link.l1.go = "Merdok_2";
		break;
		
		case "Merdok_2":
			dialog.text = "还有一件事, 船长。 一旦约汉死了, 搜查他的尸体。 房子和地下室。 他有一个档案 - 一本厚厚的分类账, 他在为公司工作期间用它写下了一些该死的笔记。 如果我们的敌人找到这些信息, 会摧毁我们所有人。 \n找到那个该死的档案并交给我, 我会为此额外付钱。 现在去吧。 祝你好运, " +pchar.name+ "船长, 尽量完整地回来。 共和国需要你! ";
			link.l1 = "我向你保证, 先生, 我会完整地回来。 这肯定符合我最大的利益! ";
			link.l1.go = "Merdok_3";
		break;
		
		case "Merdok_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "KillMerdok";
			AddQuestRecord("Holl_Gambit", "1-42");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);// 打开从房子到地下洞穴的入口
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);// 打开从地下洞穴到房子的入口
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);// 关闭药店
			pchar.quest.Merdok_inCave.win_condition.l1 = "location";
			pchar.quest.Merdok_inCave.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Merdok_inCave.function = "MerdokInUndergroundCave";
			LAi_LocationDisableOfficersGen("SentJons_TownCave", true);// 不让军官进入洞穴
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		case "Merdok_4":
			dialog.text = "太好了, 船长! 我很高兴, 真的。 你找到他的档案了吗? ";
			if (CheckCharacterItem(pchar, "MerdokArchive"))// 档案
			{
				link.l1 = "是的, 在这里。 药剂师的尸体上和他的箱子里没有其他文件。 ";
				link.l1.go = "Merdok_book";
			}
			link.l2 = "没有。 我到处找了, 但什么也没找到。 ";
			link.l2.go = "Merdok_5";
			DeleteAttribute("SentJons_TownCave", "box2");// 如果没找到密码 - 以后也找不到
		break;
		
		case "Merdok_5":
			dialog.text = "当然很遗憾, 但我对此很满意。 我相信约汉没有足够的时间把它交给英国人, 否则我们的脖子上已经有绞索了... 很可能他把它藏在某个秘密藏匿处... 让它永远留在那里吧! 我祝贺你, 船长, 成功完成了我们的任务! ";
			link.l1 = "感谢! ";
			link.l1.go = "Merdok_6";
			
			SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// 检查未通过, 意味着一周后 Liga 会攻击, 之后开始 30 天 1 阶段计时器
		break;
		
		case "Merdok_book":
			dialog.text = "太棒了! 现在它安全地回到了属于它的地方。 你再次证明了你是最棒的... 把书给我... 这个档案有奖励 - 这把好滑膛枪。 它曾为我服务得很好, 现在它是你的了! ";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.PZ_RodenburgUkradenaStranitsa"))
			{
				link.l1.go = "Merdok_book_2";
			}
			else
			{
				link.l1.go = "Merdok_book_6";
			}
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "Merdok_book_2":
			dialog.text = "你在玩什么把戏, 船长? 有几页不见了 - 对我来说非常重要的几页。 你以为我不会注意到, 所以你可以用它们来对付我? 或者你希望从中得到更多? 恐怕我在这两方面都要让你失望了。 ";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Trustworthy) 我道歉。 我唯一的过错是事先没有自己检查档案。 ";
				link.l1.go = "VD_Merdok_book_3";
				SetTimerCondition("PZ_Etap1_Start", 0, 0, 30, false);	// 1 阶段 30 天后开始
			}
			else
			{
				notification("特质检查失败", "Trustworthy");
				link.l1 = "我真的会撕掉页面, 然后若无其事地交出档案吗? ";
				link.l1.go = "Merdok_book_3";
				SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// 检查未通过, 意味着一周后 Liga 会攻击, 之后开始 30 天 1 阶段计时器
			}
			LAi_Fade("", "");
		break;
		
		case "Merdok_book_3":
			dialog.text = "贪婪。 愚蠢和无耻有时会驱使人们做出最疯狂的行为, 船长。 ";
			link.l1 = "我向你保证, 这三个都不是我的动机。 ";
			link.l1.go = "Merdok_book_4";
		break;
		
		case "Merdok_book_4":
			dialog.text = "所以你是说范.默登撕掉了那些页面, 藏在别处了? ";
			link.l1 = "正是。 如果你认为有必要, 我可以回去找它们 —把整个药店翻个底朝天, 甚至整个圣约翰。 ";
			link.l1.go = "Merdok_book_5";
		break;
		
		case "Merdok_book_5":
			dialog.text = "没必要, 先生。 无论如何, 大部分重要的内容都在这里, 没有丢失的页面, 剩下的对我没有威胁。 ";
			link.l1 = "";
			link.l1.go = "Merdok_book_6";
		break;
		
		case "VD_Merdok_book_3":
			dialog.text = "那么, 这是缺乏关心或好奇心, 而不是不诚实或秘密企图? 你认为你找到它时已经是这样了吗? ";
			link.l1 = "很可能, 罗登堡先生。 也许范.默登事先撕掉了那些页面。 ";
			link.l1.go = "VD_Merdok_book_4";
		break;
		
		case "VD_Merdok_book_4":
			dialog.text = "也许这是最好的结果。 没有那些页面, 档案的其余部分对我没有威胁 —尤其是在无知的人手中。 ";
			link.l1 = "";
			if (IsCharacterPerkOn(pchar, "Trustworthy")) link.l1.go = "Merdok_book_6";
			else link.l1 = "Merdok_6";
		break;
		
		case "Merdok_book_6":
			dialog.text = "这个档案有一个奖励 —这把精良的滑膛枪。 它曾为我效力卓著, 现在是你的了! ";
			link.l1 = "谢谢! ";
			link.l1.go = "Merdok_6";
			GiveItem2Character(PChar, "mushket2");
		break;
		
		case "Merdok_6":
			dialog.text = "我们做得很好, 你和我, 船长。 毫不夸张地说, 没有你, 这一切都不会发生。 如果你继续为共和国服务, 你将达到令人难以置信的职业高度, 也许甚至会被授予贵族身份。 ";
			link.l1 = "我想这是再见了, 罗登堡先生。 ";
			link.l1.go = "Merdok_7";
		break;
		
		case "Merdok_7":
			dialog.text = "再见了, " +pchar.name+ "。 我在这里已经完成了我想要的一切, 所以我一周后要回家去阿姆斯特丹。 我的新妻子阿比盖尔和我的岳父所罗门将陪我一起。 彼得.斯特伊弗桑特已经找到了一位新的公司副总裁, 所以如果你需要什么, 就和他谈谈。 \n为了你的服务, 我把‘美凤’号送给你。 她现在是你的了, 船长, 你值得拥有她。 ";
			link.l1 = "谢谢你, 罗登堡先生。 我已经非常喜欢‘美凤’号了, 已经开始把她当作自己的船了。 ";
			link.l1.go = "Merdok_8";
		break;
		
		case "Merdok_8":
			dialog.text = "现在我得请你离开了, 我的孩子。 在我们起航之前, 我有很多事情要做... 有一天来阿姆斯特丹看我! 我们会喝一杯, 回忆过去的美好时光... ";
			link.l1 = "好的, 先生。 我希望你们在新生活中都幸福繁荣! 再见! ";
			link.l1.go = "Merdok_9";
			// belamour传奇版 -->
			link.l2 = "好的, 先生。 我希望你们在新生活中都幸福繁荣! \n (咬紧牙关) ... 我希望我们再也不要见面, 你这个傲慢的混蛋。 等着瞧吧, 等你发现娶一个‘端庄’的犹太悍妇的乐趣。 ";
			link.l2.go = "Merdok_9a";
		break;
		
		case "Merdok_9a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");// 可以使用港口
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");// 移除阿比
			sld.lifeday = 0;
			sld = characterFromId("Solomon");// 移除所罗门
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";// 卢卡斯退出事件
			pchar.questTemp.HWIC.Detector = "holl_win";
			CheckPortugalHWIC();
			sld = characterFromId("Villemstad_Mayor"); // belamour传奇版
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("罗登堡先生已带着他的年轻妻子和岳父起航前往阿姆斯特丹。 你是新的副总裁吗? ", "Villemstad", 30, 3, "");
			AddSimpleRumour("他们说, 船长, 你很受总督的器重。 据说罗登堡先生任命你为他在公司的继任者, 是这样吗? ", HOLLAND, 30, 3);
		break;
		
		case "Merdok_9":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// < —传奇版
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");// 可以使用港口
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");// 移除阿比
			sld.lifeday = 0;
			sld = characterFromId("Solomon");// 移除所罗门
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";// 卢卡斯退出事件
			pchar.questTemp.HWIC.Detector = "holl_win";
			CheckPortugalHWIC();
			sld = characterFromId("Villemstad_Mayor"); // belamour传奇版
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("罗登堡先生已带着他的年轻妻子和岳父起航前往阿姆斯特丹。 你是新的副总裁吗? ", "Villemstad", 30, 3, "");
			AddSimpleRumour("他们说, 船长, 你很受总督的器重。 据说罗登堡先生任命你为他在公司的继任者, 是这样吗? ", HOLLAND, 30, 3);
		break;
		
//----------------------------------------------前往英国------------------------------------------------------
		case "Lucas_abordage":
			dialog.text = "我的上帝! 弗利特伍德的狗! 你可能赢得了这一天, 但卢卡斯.罗登堡会让你付出高昂的代价。 ";
			link.l1 = "我不这么认为。 你会免费把你的命交给我, 你这个荷兰吝啬鬼。 ";
			link.l1.go = "Lucas_abordage_1";
		break;
		
		case "Lucas_abordage_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "我会从地狱深处往你嘴里拉屎! 我刚刚把货舱点燃了, 火很快就会蔓延到火药库! 我们的船紧紧靠在一起, 所以没有逃脱的希望! 你会被烧死或喂鲨鱼! ";
			link.l1 = "该死! 撤退, 兄弟们, 我们必须撤退! ";
			link.l1.go = "Lucas_abordage_2";
			// belamour传奇版 -->
			link.l2 = "在你的灵魂离开身体之前, 我不会离开。 别动, 这会很疼。 ";
			link.l2.go = "Lucas_abordage_2a";
		break;
		
		case "Lucas_abordage_2a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "Lucas_abordage_2":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// < —传奇版
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
//----------------------------------------------对抗所有人--------------------------------------------------
		case "LucasPrisoner":
			dialog.text = "你为什么在这里, 你这个混蛋? 来嘲笑我吗? 也许你终于可以告诉我你在这场戏中扮演什么角色了。 是你捕获了那艘双桅船, 对吗? 这从一开始就是你的计划吗? ";
			link.l1 = "我来这里是为了给你带些问候, 卢卡斯.罗登堡。 来自约翰.默多克的最好问候, 你背叛了他。 你是我的任务, 我完成了。 现在再见。 ";
			link.l1.go = "LucasPrisoner_1";
		break;
		
		case "LucasPrisoner_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "约翰? 哈哈! 原来幕后黑手是那个老无赖! 但游戏还没有结束。 雅各布.范.伯格正在找你, 你逃不掉的! 你和你的船都完了, 你这个可怜的海乞丐! ";
			link.l1 = "留着你的声音去绞刑架的法庭吧, 罗登堡。 ";
			link.l1.go = "LucasPrisoner_2";
		break;
		
		case "LucasPrisoner_2":
			DialogExit();
			pchar.questTemp.jailCanMove = true; // 允许走过卫兵
			LAi_SetPlayerType(pchar);
			pchar.quest.Login_Joakim.win_condition.l1 = "location";
			pchar.quest.Login_Joakim.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Login_Joakim.function = "Create_Joakim";
			pchar.questTemp.HWIC.Self = "JoakimMeeting";
			SetFunctionTimerCondition("LucasQuit", 0, 0, 7, false);
		break;
	}
}