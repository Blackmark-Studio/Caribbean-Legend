void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1, iColony, crewWhoreCost, charWhoreCost = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
		
	// 按城市调用对话框 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// 按城市调用对话框 <--
	crewWhoreCost = 50 + 7 * MOD_SKILL_ENEMY_RATE - hrand(40);
	charWhoreCost = 2460 + sti(pchar.rank) * 40;
	
	switch(Dialog.CurrentNode)
	{
		// ============= 妓院老板娘 =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(""+ GetSexPhrase("亲爱的, 哪来的姑娘? 半个卫戍部队都在追你, 你还敢直接来妓院! ","滚蛋吧你? 半个卫戍部队都在追你! ") +"", "每个城镇卫兵都在找你。 我可不会傻到现在为你提供服务... ", "你在这儿根本没什么事可做! "), 
					LinkRandPhrase(""+ GetSexPhrase("敢动我的姑娘, 我就活剥了你的皮! ","滚蛋, 你这讨厌鬼! ") +"", "肮脏的"+ GetSexPhrase("","") +"凶手, 马上离开我的地盘! 卫兵!! ", "我可不怕你, "+ GetSexPhrase("恶棍","老鼠") +"! 很快你就会在我们的堡垒被吊死, 你跑不远的... "));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("呵, 警报对我来说从来不是问题... ", "他们永远抓不到我。 "), 
					RandPhraseSimple("闭嘴, 愚蠢的老太婆。 ", "不想惹麻烦就闭嘴... "));
				link.l1.go = "exit";
				break;
			}
			//--> 肮脏的鸡神
			if (CheckAttribute(pchar, "questTemp.ChickenGod.HostessDialog")) {
				dialog.text = "哦, 我的上帝! 你怎么进来的? 亲爱的船长, 请离开 —我求你了! 我们的场所现在关闭了! ";
				link.l1 = "很高兴见到你, 亲爱的" + npchar.name+ "。 我在客人名单上。 不过在这种地方, 就算是客人也得付钱, 所以... 请别让我为难, 但我想付房费。 ";
				link.l1.go = "chicken_god";
				
				DeleteAttribute(pchar, "questTemp.ChickenGod.HostessDialog");
				break;
			}
			//< —肮脏的鸡神
			//--> 马提尼克教程
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start" && npchar.location == "FortFrance_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				link.l1 = "听着, 奥罗拉, 我需要一个姑娘过夜。 我想带她回家。 你能安排吗? ";
                link.l1.go = "Gigolo";
				break;
			}
			//< —马提尼克教程
			//Jason --> 讨厌的贵族
			if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && !CheckAttribute(pchar, "questTemp.ZA.Block") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
			{
				dialog.text = "你真是个庄重的男人。 而且, 我的姑娘们都很喜欢你。 我想请你为我的场所帮个小忙。 ";
				link.l5 = "我受宠若惊, 当然可以。 你需要我帮什么忙? ";
				link.l5.go = "Badboy";
				link.l8 = "抱歉, 我现在很忙。 ";
				link.l8.go = "exit";
				npchar.quest.Badboy = "true";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
			{
				if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
				{
					dialog.text = "哦, 你回来了! 你安排好那个"+pchar.GenQuest.Badboy.Brothel.Name+"不再骚扰我的姑娘们了吗? ";
					link.l5 = "是的。 他不会再出现在这里了。 ";
					link.l5.go = "Badboy_complete";
				break;
				}
			}
			// < —讨厌的贵族
			
			//--> Jason 葡萄牙人
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (!CheckAttribute(pchar, "questTemp.Portugal") && bOk && !CheckAttribute(npchar, "quest.Portugal") && npchar.location == "Marigo_SecBrRoom" && makeint(environment.time) > 6.0 && makeint(environment.time) < 22.0)
				{
					DelMapQuestMarkCity("marigo");
					DelLandQuestMark(npchar);
					dialog.text = "船长, 我能请你帮个忙吗? ";
					link.l5 = "为你效劳, 夫人, 任何事都行! 我听候差遣! ";
					link.l5.go = "Portugal";
					link.l8 = "抱歉, 我现在很忙。 ";
					link.l8.go = "exit";
					npchar.quest.Portugal = "true";
					DelLandQuestMark(npchar);
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				dialog.text = "你和雨果谈过了吗, 船长先生? ";
				if (sti(pchar.money) >= 10000)
				{
					link.l1 = "不仅谈过, 夫人, 这是你的钱。 一切都进行得非常顺利... ";
					link.l1.go = "Portugal_3";
				}
				else
				{
					link.l1 = "是的, 我转达了你的请求。 ";
					link.l1.go = "Portugal_exit";
				}
				break;
			}
			//<--葡萄牙人
			// Addon 2016-1 Jason 海盗线
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "哦天哪, 看看这是谁! 查理.普林斯, 著名的海盗! 真人! ";
				link.l1 = RandSwear()+"你好, 珍妮特。 我是为马库斯.泰雷克斯而来。 ";
				link.l1.go = "mtraxx_R";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "你准备好接受难忘的恢复治疗了吗, 我勇敢的海盗? ";
				if (sti(pchar.money) >= 31000)
				{
					link.l1 = "准备好了! 查理.普林斯从不废话, 花钱也一样, 哈哈! ";
					link.l1.go = "mtraxx_R2";
				}
				else
				{
					link.l1 = "差不多... 我想我在你这里丢了个钱包... 我会带钱回来的! ";
					link.l1.go = "exit";
				}
				break;
			}
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + "。 欢迎来到我的爱之屋。 我叫" + npchar.name+ ", 是这里的老板。 "+ GetSexPhrase("我能为你做什么, " + GetAddress_Form(NPChar) + "?","坦白说, " + GetAddress_Form(NPChar) + ", 在这里见到你我有点惊讶, 但我向你保证我们不仅为男人提供服务。 ") +"",
				TimeGreeting() + "。 欢迎你, "+ GetSexPhrase("陌生人","年轻女士") +", 来到我简陋的场所。 请允许我介绍自己, 我是"+ Npchar.name+ " —这家渴望女人抚摸的男人庇护所的主人。 "+ GetSexPhrase("我能为你做什么? ","不过我们也为女士提供一些服务... ") +"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + "。 我能帮你什么, " + GetAddress_Form(NPChar) + "?",
				TimeGreeting() + "。 我能为你做什么, " + GetAddress_Form(NPChar) + "?");
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))//没有女孩任务
			{
				if (!CheckAttribute(pchar, "GenQuest.BrothelLock"))// 没有玛丽的禁止 280313
				{
					link.l2 = npchar.name+ ", 我想和你的一个姑娘共度美好时光。 ";
					link.l2.go = "Hostess_1";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // 没有夏莉的开始
			{
				if (sti(pchar.ship.type) != SHIP_NOTUSED && GetCrewQuantity(pchar) > 0) // Rebbebion - 如果既没有船也没有船员, 有什么意义? 
				{
					link.l3 = "我的手下好久没放松过了。 我能为他们批量预订姑娘吗? ";
					link.l3.go = "ForCrew";
				}
			}
			link.l4 = "我有个问题。 ";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// 生成器 "找到的文件"
				}
				else
				{
					link.l4.go = "quests";
				}	
			}
			else
			{
				link.l4.go = "quests";//(转发到城市文件)
			}	
			//-->> 寻找市长戒指任务
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = "听着, " + npchar.name+ ", 我在找市长的戒指。 他在你这里休息时可能弄丢了。 ";
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<< —寻找市长戒指任务

			// belamour 夜间冒险 -->
			if(CheckAttribute(pchar, "GenQuest.NightAdventureVar") && pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleWhoreMoney")
			{
				link.l8 = "听着, 我想带走你这里最好的姑娘。 ";
				link.l8.go = "NA_Girl";
			}
			// < —冒险家
			link.l9 = "没关系, 我这就走。 ";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("你想要什么, 帅哥? ","我在听你说, 船长。 ");
				link.l1 = "听着, " + npchar.name+ ", 我在你机构的一个私人房间里发现了这些文件... ";
				link.l1.go = "ShipLetters_2";				
		break;
		
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "让我看看! 嗯... 某个船长弄丢了文件, 对吧? 我想你应该问问港口主管。 ";
				link.l1 = "也许吧... ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "让我看看! 哦! 从名字看, 它们属于我尊贵的顾客和我们城镇的杰出公民。 我可以亲自把这些文件交给他。 ";
				link.l1	= "可能不行... ";
				link.l1.go = "exit";
				link.l2 = "太好了! 总是很高兴帮助好人与好机构。 ";
				link.l2.go = "ShipLetters_3";										
			}	
		break;
		
		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //移除计时器 
			AddQuestRecord("GiveShipLetters", "2");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = ""+ GetSexPhrase("我们总是很高兴为顾客服务。 现在告诉我, 帅哥 - 你已经有喜欢的人了, 还是不太在意? ","嗯, 我的姑娘们当然能够... 帮助你。 你已经有喜欢的人了, 还是不太在意? ") +"";
					Link.l1 = ""+ GetSexPhrase("呵, 我现在就需要一个妓女, 马上。 我不在乎是哪个, 你的姑娘们看起来都不错... ","只要她知道自己的职责, 谁都行... ") +"";
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = "是的, 有一个, "+ GetSexPhrase("她很合我心意... ","她是最合适的... ") +"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "今天我没有空闲的姑娘给你, 我们的顾客已经太多了。 明天来吧, 你不会后悔的! ";
					Link.l1 = "真可惜, 我才刚开始有兴趣。 ";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "嗯。 你已经为姑娘付过钱了。 请不要打扰我。 ";
				Link.l1 = "好吧, 我这就来。 ";
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = "我现在没有空闲的姑娘, 你得几天后再来看看。 ";
				Link.l1 = "好吧, 如你所说。 ";
				Link.l1.go = "exit";	
			}
			else
			{
				// belamour 传奇版 圣路易勋章 -->
				if(IsEquipTalisman9() && npchar.nation == FRANCE)
				{
					dialog.text = ""+ GetSexPhrase("好吧, 猛男, 太棒了! ","我可以肯定, 她们都很熟练。 ") +"我可以给你推荐一个名叫" + GetFullName(sld) + "的漂亮姑娘, 她现在有空。 \n哦, 你那么谦虚地藏在那里的是什么? ! 这是法国的最高荣誉吗? 据说佩戴这个徽章的人不仅在战场上传奇... 嗯, 你知道我的意思, 我的海盗... 此外, 任何人都会认为触摸你的'勋章'是一种荣誉, 所以今天你在我的场所休息由我买单。 不接受拒绝, 帅哥。 ";
					Link.l1 = "我当然同意, 这有什么可问的? ! ";
					Link.l1.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
					break;
				}
				// < —传奇版
				dialog.text = ""+ GetSexPhrase("好吧, 太棒了, 我的猛男! ","她们都非常擅长自己的工作, 毫无疑问。 ") +"我可以给你推荐一个非常好的姑娘, 她叫" + GetFullName(sld) + ", 现在有空。 那次享受将花费你" + FindRussianMoneyString(sti(sld.quest.price) + charWhoreCost) + "。 同意吗? ";
				Link.l1 = "不。 我想不是。 太贵了... ";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
				{
					Link.l2 = "当然, 我怎么能拒绝? ! ";
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "哦, 该死, 我身上没那么多钱... ";
					Link.l1.go = "exit";
				}
			}
		break;
		
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
			{
				dialog.text = "好的, "+ GetSexPhrase("帅哥","美女") +"。 " + sld.name + "会在二楼的私人房间等你。 ";
				Link.l1 = ""+ GetSexPhrase("好的, 那我来了","好的, 那我来了") +"... ";
				Link.l1.go = "exit";
				// belamour 传奇版 只有没有勋章或舰队司令制服时才给钱
				if(IsEquipTalisman9())
				{
					if(npchar.nation != FRANCE) AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				else
				{
					AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				sld.dialog.currentnode = "Horse_ReadyFack";			
				//--> 返回计时器, 以免无限等待
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";	
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//< —返回计时器, 以免无限等待
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //打开房间
				npchar.quest.selected = true; //从老板娘那里选了姑娘的标志
				SetNPCQuestDate(npchar, "quest.date"); //记录领取日期
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}
				
				// 生成找到的文件
				
				// belamour 传奇版 不给总督和舰队司令任务
				bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor");
				bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4;
				
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10 && !MCGovernon && !MCAdmiral ) 
				{					
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;	
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // 至少给一天
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;
									
					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//把文件放入物品								
					sTemp = "_Brothel_room";	
					sTemp1 = "_town";					
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4)+1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //标志 - 文件散落在物品中
					Log_QuestInfo("文件在位置 " + sld.startLocation + ", 定位器 " + sld.startLocator + " p1 : " + p1);
					
					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";
					
					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //释放迷你任务的许可
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");					
				}
				// 生成器 - "匆忙的理由"
				if((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !MCGovernon && !MCAdmiral) // Addon-2016 Jason
				{
					iColony = FindColony(npchar.city);	
					if( sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";					
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");	
					}	
				}				
			}
			else
			{
				dialog.text = "哦, 你看, 问题是" + sld.name + "不是便宜的姑娘, 她的价格是" + FindRussianMoneyString(sti(sld.quest.price) + charWhoreCost) + "。 我看你现在根本付不起。 等你有钱了再来吧"+ GetSexPhrase(",亲爱的","") +"... ";
				Link.l1 = "我就这运气... ";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "我总是很高兴看到姑娘和顾客之间产生温暖的感情... 告诉我她的名字。 ";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
		
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "嗯... 你一定弄错了。 我这里没有这样的姑娘。 也许你记错了名字。 ";
				Link.l1 = "嗯... 但我刚和她聊过。 ";
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = "也许吧。 最好再问一次她的名字, 确认一下。 我以后再和你谈这个。 ";
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld) + ", 你说的是她? ";
				Link.l1 = "是的, 就是她。 ";
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = "不, 不是她。 ";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
		
        case "Hostess_Choice_2":
			dialog.text = "那也许你应该再告诉我一次她的名字, 也许我就知道你说的是谁了。 ";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "也许吧。 最好再问一次她的名字, 确认一下。 我以后再和你谈这个。 ";
			Link.l2.go = "exit";	
		break;
		//==> 船员
		case "ForCrew":
			dialog.text = "嗯... 想帮你的手下'释放一下压力'? 你看, 我的场所是有名望的, 我有这附近最好的姑娘。 但我认识几个港口妓女, 她们会很高兴取悦你所有的水手。 这将花费你" + FindRussianMoneyString(GetCrewQuantity(pchar)*crewWhoreCost) + "。 ";			
			link.l1 = "好的, 我同意。 ";
			link.l1.go = "ForCrew_1";
			link.l2 = "我想他们没有也能应付... ";
			link.l2.go = "exit";
		break;
		
		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*crewWhoreCost && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*crewWhoreCost));
	            AddCrewMorale(Pchar, 10);
				ChangeCharacterComplexReputation(pchar,"authority", 1);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
				dialog.text = "这不关我的事, 但我认为你应该先赚足够的钱来雇佣船员, 然后再担心他们的精神状态。 ";
				link.l1 = "你可能是对的... ";
				link.l1.go = "exit";
			}
		break;
		
		case "Woman_FackYou":
			dialog.text = "亲爱的, 你到底在做什么? ! 你看起来像个体面的船长... 这次你可跑不掉了, 帅哥。 卫兵会砍断你的翅膀... ";
			link.l1 = "闭嘴, 老巫婆。 ";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		
		//寻找市长戒指
		case "TakeMayorsRing_H1":
			dialog.text = "我没找到任何戒指。 ";
			link.l1 = "你的姑娘们呢? ";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		
		case "TakeMayorsRing_H2":
			dialog.text = "她们也没有。 如果顾客遗忘或丢失任何东西, 我的姑娘们会交给我。 但没人给我带来市长的戒指。 ";
			link.l1 = "我明白了... 但会不会是她们决定自己留着? ";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		
		case "TakeMayorsRing_H3":
			dialog.text = "不太可能。 姑娘们可以保留顾客的礼物, 但仅此而已。 ";
			link.l1 = "我明白了。 好吧, 谢谢你, " + npchar.name+ "。 ";
			link.l1.go = "exit";
		break;
		
		case "Hostess_inSexRoom":
			dialog.text = "哦, 你来了... ";
			link.l1 = "我来了, 女士! ";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //重置未到计时器
			NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
			{
				sld = CharacterFromID(pchar.RomNaTroih_Shluha);
				dialog.text = "" + sld.name + "! 我的英雄, 看来你在楼下没浪费时间! ";
				link.l1 = "希望你能原谅我的这个弱点, 我的女王? ";
				link.l1.go = "RomNaTroih_2";
			}
			AddDialogExitQuestFunction("SexWithHostess_fack");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.RomNaTroih");
            if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 10);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 5);
		break;
		
		// ================================== 普通角色 =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("你最好离开这里! ", "镇上所有卫兵都在找你! 你最好离开... ", "你惹了麻烦现在还敢来? ! 不, 这次不行... "), 
					LinkRandPhrase("滚出去! ", "肮脏的凶手, 滚出去! 卫兵! ", "我不怕你, "+ GetSexPhrase("恶棍","老鼠") +"! 很快你就会在我们的堡垒被吊死, 你跑不远的... "));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("呵, 警报对我来说从来不是问题... ", "他们永远抓不到我。 "), 
					RandPhraseSimple("呵, 你这蠢女人... ", "闭嘴, 婊子, 不然我就用别的东西让你闭嘴... "));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("你好, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase("",", 嘻嘻..") +"。 你得去见老板娘并填写订单。 ", 
				"你又来了? 请和管理员谈。 她在办公室。 ", 
				"听着, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase(", 我希望你在其他事情上也像说话一样固执... 我再次",", 再一次") +"请你去见场所的主人。 ", 
				"哦, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase(", 你不是很固执吗! ",", 嘻嘻... 你很固执, 不是吗? ") +" 你得去见老板娘并填写订单。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("好吧, "+ GetSexPhrase("美女, ","") +"我知道了"+ GetSexPhrase("","") +"。 ", "是啊, 对... ",
					  ""+ GetSexPhrase("毫无疑问, 我漂亮的姑娘, 我像公牛一样固执和强壮! ","是啊, 是啊... ") +"", ""+ GetSexPhrase("哦, 该死, 我一定是漏掉了什么... 对不起, 亲爱的。 ","好吧, 好吧。 ") +"", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "她在哪里? ";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+ GetSexPhrase("哦, 美女, 我敢打赌我能在你那双眼睛里沉沦... ","你看起来真美, 宝贝! ") +"", ""+ GetSexPhrase("你知道吗, 我以前从未见过这么美丽的女人! ","你知道吗, 我以前从未见过这么好的妞! ") +"", ""+ GetSexPhrase("亲爱的, 你看起来真美。 ","该死, 我厌倦了所有那些乡巴佬... 而你如此迷人! ") +"");
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> 寻找市长戒指任务
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase("听着, "+ GetSexPhrase("美女","亲爱的") +", 你碰巧在这里找到过结婚戒指吗? 好像有个男人弄丢了... ", 
					"亲爱的, 你在附近见过结婚戒指或类似的东西吗? ", 
					"听着, "+ GetSexPhrase("我的小猫咪","宝贝") +", 你在这附近见过结婚戒指吗? ");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<< —寻找市长戒指任务
			
			// Addon 2016-1 Jason 海盗线
			if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_"+reload_location_index+"_2")
			{
				link.l6 = "嘿, 甜心。 马库斯.泰雷克斯派我来的, 看看这条琥珀项链... ";
				link.l6.go = "mtraxx";
			}
			NextDiag.TempNode = "Horse_talk";
		break;
		
        case "Horse_1":
			dialog.text = "她在办公室。 你可以从这里穿过临街出口对面的门过去, 或者从房子另一边的街道过去。 她叫" + characters[GetCharacterIndex(npchar.city + "_Hostess")].name + "。 ";
			Link.l1 = "我知道了, "+ GetSexPhrase("甜心","亲爱的") +", 谢谢。 ";
			Link.l1.go = "exit";			
		break;
		
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("哦, 听到这样的话真好! 嘿, 我现在有空, 所以如果你选我, 你不会后悔的... ", "你真的这么认为吗? 你知道, 这太可爱了... 听着, 我现在有空, 所以你可以选我。 "+ GetSexPhrase("我保证给你爱的海洋和抚摸的海洋... ","") +"", ""+ GetSexPhrase("你这么认为吗? 哦, 我真的受宠若惊。 你知道, 我很少听到这样的赞美... ","哦, 女孩... 如果你知道我有多厌倦乡巴佬... ") +" 嘿, 听着, 我现在有空, 所以你可以选我让你开心。 我保证不会让你失望... ");
				if (CheckAttribute(pchar, "questTemp.RomNaTroih") && !CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
				{
					link.l1 = "我亲爱的, 这正是我打算做的! 真幸运你的老板娘已经在楼上安排了私人会面。 愿意一起吗? ";
					Link.l1.go = "RomNaTroih_1";
					pchar.questTemp.RomNaTroih_Pogovoril = true;
					break;
				}
				link.l1 = "那么, 我选你了! ";
				Link.l1.go = "Horse_3";		
				Link.l2 = ""+ GetSexPhrase("不, 那只是对一位好女士的赞美","那只是一句赞美") +"。 ";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //有过议价, 但玩家后来拒绝了
			}
			else
			{
				dialog.text = LinkRandPhrase(""+ GetSexPhrase("你知道我怎么说吗, 亲爱的? 我不需要这种廉价的谈话。 要么谈生意要么离开! ","这就是我需要的! 来自女人的赞美! ") +"", ""+ GetSexPhrase("你以为女人是用耳朵恋爱的吗? 好吧, 亲爱的, 那不是真的。 如果你想要我, 就向老板娘付钱, 省省你那些空话。 ","姑娘, 别在空话上浪费自己。 如果你是认真的 —那就付钱... ") +"", ""+ GetSexPhrase("哦, 又一个好色之徒... 你只要付钱, 我就是你的。 就这么简单, 没有那些温柔的废话! ","你怎么了, 亲爱的? 如果你想放纵自己, 那就付钱, 别再胡说八道! ") +"");
				link.l1 = "哦, 真会抓机会! ";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //玩家被送走
			}
		break;
		
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city + "_Hostess")].name + "在她的办公室完成所有手续。 去见她"+ GetSexPhrase(",我的英雄,","") +", 说我的名字 --" + npchar.name+ "。 我会等你... ";
			Link.l1 = "我知道了, 亲爱的, 我很快回来... ";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //她同意了
			SetNPCQuestDate(npchar, "quest.choice");
		break;
		
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat("你已经付过钱了。 ", 
				"我告诉过你'上楼去'。 ", 
				"上楼去, 年轻人。 ", 
				"有些人反应真慢... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("是的, 我知道。 ", "我记得。 ",
                      "哦, 别重复了, 我记得。 ", "嗯, 你什么意思? .", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		
		//===>> 对已经有过调情尝试的反应
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("我只是不太理解你。 "+ GetSexPhrase(" 先是赞美, 然后又食言。 真是个奇怪的人... ","") +"", 
					"又来赞美? .", 
					"管理员在她的办公室。 明白了吗? ", 
					"我们不应该侮辱顾客, 但你真的在自找... ", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("事情就是这样发生的... ", "好吧, 我会去的。 ",
						"是的, 我知道了。 ", "请原谅, 我的爱人。 ", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "谢谢你的赞美。 如果你想带我走, 就去见老板娘。 一切照旧。 ";
				Link.l1 = "我知道了。 ";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("亲爱的, 我们已经谈过了。 ","") +"别让我等太久... ", 
						""+ GetSexPhrase("嗯... 听着, 亲爱的, 我","我") +"觉得你的话很好, 但你能谈正事吗... ", 
						"也许, 你会和老板娘讨论这个, 不是吗? ", 
						"嗯... 我甚至不知道该说什么... ", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("我永远不会那样做, 等我! ", "当然! ",
							"当然, 如你所说! ", "我已经跑去见你的老板娘了... ", npchar, Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "我在等你, 但你没来带我走... 我不能说我喜欢这样... ";
					Link.l1 = "你看, 事情就是这样发生的... ";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //有过议价, 但玩家后来拒绝了
				}
			}
			else
			{
				dialog.text = "哦, 又是你, 我的"+ GetSexPhrase("光荣海盗","漂亮姑娘") +"! 如果还想和我在一起, 就去见老板娘, 你不会失望的... "+ GetSexPhrase(" 顺便说一句, 我认出你了, 亲爱的, 但我们被告知必须平等对待所有顾客, 不应该有最喜欢的, 抱歉... ","") +"";
				Link.l1 = "别担心, 亲爱的。 请稍等我一下, "+ GetSexPhrase("小可爱","小可爱") +", 很快我们就会再次私下见面。 ";
				Link.l1.go = "exit";
				Link.l2 = "你记得我真好, 但我今晚不能和你在一起, 抱歉。 ";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
		
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("那么,"+ GetSexPhrase(" 亲爱的朋友,","") +"你最好从事商业活动。 这比无所事事更有用。 ", 
					""+ GetSexPhrase("嗯, 你为什么","为什么你") +"一遍又一遍地说同样的话? ", 
					"嘿, 这还不够吗? ! ", 
					"嗯, 真令人惊讶, 没什么新鲜的"+ GetSexPhrase(", 又是那些迷人的愚蠢尝试! 如果你想和我上床, 就去见老板娘, 你这个笨蛋! ","... ") +"", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("是的, 我听说"+ GetSexPhrase("","") +"你... ", "嗯, 结果就是这样... ",
						"嗯, 也许这就够了, 也许还不够... ", "注意你的舌头"+ GetSexPhrase(", 山羊","") +"... ", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "哦h, 又是你! "+ GetSexPhrase(" 又是那些愚蠢的赞美。 这世界上什么都没变... 如果","只是提醒: 如果 ") +"你想"+ GetSexPhrase("玩得开心","玩得开心") +"和我在一起, 付钱给场所老板。 我才不在乎你的话。 ";
				Link.l1 = "这并不奇怪... ";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1_Add":
			dialog.text = "我不能说这让我高兴... 真遗憾。 ";
			Link.l1 = "对不起... ";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		
		//===>> 性
        case "Horse_ReadyFack":
			// Addon 2016-1 Jason 海盗线
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Gabriela")
			{
				dialog.text = "啊, 你终于到了! 太好了! 我们可以自由交谈了... 没人在听... ";
				Link.l1 = "那么, 是那个西班牙人给你的蓝色琥珀? ";
				Link.l1.go = "mtraxx_2";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SantoDomingo");
				break;
			}
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("很高兴见到你。 "+ GetSexPhrase("那么, 我们接下来做什么? ","我们好好享受一下如何? ") +"", "别害羞"+ GetSexPhrase(", 至少待两个小时放松一下。 ","。 我保证能让你开心, 毫无疑问。 ") +"");
					Link.l1 = RandPhraseSimple("我不认为会无聊... ", ""+ GetSexPhrase("让我们玩得开心, 宝贝! ","我们别浪费时间了! ") +"");
				break;
				case "1":
					dialog.text = "哦, 又是你, 我的"+ GetSexPhrase("光荣海盗! 我答应过你, 我准备信守诺言","漂亮姑娘! 接下来的两个小时你永远不会忘记") +"... ";
					Link.l1 = "这听起来很诱人... ";	
				break;
				case "2":
					dialog.text = "哦h, 你终于来了。 我们别浪费时间了! ";
					Link.l1 = ""+ GetSexPhrase("别浪费了, 小猫咪... ","现在让我看看你能做什么... ") +"";
				break;
			}
			if (pchar.sex == "woman")
			{
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex";
				AddDialogExitQuest("PlaySex_1");
				// 从妓院获得的加成
				if (CheckNPCQuestDate(pchar, "BrothelSex"))
				{
					if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 10);
					else 												AddCharacterHealth(pchar, 5);
					SetNPCQuestDate(pchar, "BrothelSex");
				}
				// 状态变化
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "FencingS", -15);
				AddCharacterExpToSkill(pchar, "Pistol", -15);
			}
			else
			{
				pchar.horsekiss = npchar.id;
				Link.l1.go = "Horse_Kiss";
			}
			//--> 访问次数
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // 用于丹内克
			Achievment_SetStat(23, 1);
			//< —访问次数
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //计数器
		break;
		
		case "Horse_Kiss":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("Horse_Kiss", "");
		break;

        case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = "船长, 你为什么这么沉默? ";
				link.l1 = LinkRandPhrase("嗯, 我就是这样。 ", "我们下次再谈。 ", RandPhraseSimple("我不是付钱让你说话的。 ", "但你, "+ GetSexPhrase("美女","亲爱的") +", 那段时间可没那么沉默。 "));
				link.l1.go = "exit";
				link.l2 = ""+ GetSexPhrase("你刚才太棒了, 我几乎失去了理智! 很少有女人既漂亮又热情","哦h, 你当然知道如何取悦女人... 我太兴奋了。 ") +"。 ";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("你喜欢吗? ", "那么, 你能说什么? 一切都好吗? ", "那么,"+ GetSexPhrase(" 海盗, 是, 一切"," 一切") +"好吗? ");
						Link.l1 = RandPhraseSimple(""+ GetSexPhrase("当然, 一切都好","你当然知道你的职责") +"。 ", ""+ GetSexPhrase("一切都好, 宝贝","你知道, 我很满意") +"。 ");
						Link.l1.go = "exit";
					break;
					case "1":
						dialog.text = LinkRandPhrase("那么, 我信守诺言了吗? ", "那么,"+ GetSexPhrase(" 你喜欢我",", 你喜欢吗") +"?", "我希望,"+ GetSexPhrase(" 你满意, 因为我非-常-满意"," 你满意, 因为我尽力了") +"... ");
						Link.l1 = RandPhraseSimple("是的, 我非常喜欢。 ", ""+ GetSexPhrase("我们玩得很开心, 你太棒了! ","一切简直太棒了! ") +"");	
						Link.l1.go = "exit";
					break;
					
					case "2":
						dialog.text = RandPhraseSimple("好了, 就这样, 你得走了。 ", "你的时间到了,"+ GetSexPhrase(" 船长,","") +"。 ");
						Link.l1 = RandPhraseSimple("是的, 再见... ", "再见, 谢谢... ");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "那么, 你觉得这里怎么样? ";
				link.l1 = "告诉我美女, 你在附近见过一个旅行袋吗? ";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("有空再来... ", "再见。 我们随时等你... ", "我们很高兴再次见到你... ");
				Link.l1 = "好的... ";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
		case "EncGirl_GetBag":
			dialog.text = "是那个棕色的带把手的箱子吗? ";
			link.l1 = "是的, 差不多... ";
			link.l1.go = "EncGirl_GetBag1";	
		break;
		
		case "EncGirl_GetBag1":
			dialog.text = "因为那个箱子的主人没出现, 老板娘把它拿到她的闺房了。 ";
			link.l1 = "谢谢, 宝贝。 再见。 ";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
		// --> 生成器 - "匆忙的理由"
		case "Horse_ReasonToFast_1":
			dialog.text = "那你随时来, 我总是很高兴见到你。 你真"+ GetSexPhrase("温柔, 不像其他人","温柔, 不像那些乡巴佬") +" 没有问候, 没有告别, 还经常想伤害... ";
			link.l1 = "你那是什么意思? ";
			link.l1.go = "Horse_ReasonToFast_2";
		break;
		
		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "在你之前有个军士长。 他通常不来我们这里, 但这次不知怎么来了。 而且他选了我... 他在我身上呻吟了几分钟, 然后说我技术差, 就冲向某个海湾了。 他走得太急, 差点把裤子落在那里, 哈哈哈... ";
			link.l1 = "你不知道吗, "+ GetSexPhrase("美女","亲爱的") +", 男人到底是什么样的? 他告诉他妻子要去妓院'检查', 然后告诉他情妇说他急着去找妻子, 但他唯一想做的就是去巡逻那个海湾。 "+ GetSexPhrase("哈哈哈! ..","哈哈哈! ") +"";
			link.l1.go = "Horse_ReasonToFast_3";
		break;
		
		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";			
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if(TargetLocation != "")
			{ 
				Locations[FindLocation(TargetLocation)].DisableEncounters = true;
				LAi_LocationDisableOfficersGen(TargetLocation, true);
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		// < —生成器 "匆忙的理由"
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//寻找市长戒指
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //如果散落在物品中
			{
				dialog.text = LinkRandPhrase("不, 亲爱的, 抱歉, 没有。 我很乐意帮助你, 但我不能。 ", 
					"不, "+ GetSexPhrase("帅哥","年轻女士") +", 我没见过任何戒指... ", 
					"抱歉, 没有。 我没见过任何戒指。 ");
				link.l1 = "可惜... 好吧, 还是谢谢你。 ";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "你是说市长的戒指? ";
					link.l1 = "正是, 宝贝! ";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("不, 亲爱的, 抱歉, 没有。 我很乐意帮助你 - 但我不能。 ", 
						"不, "+ GetSexPhrase("帅哥","年轻女士") +", 我没见过任何戒指... ", 
						"抱歉, 没有。 我没见过任何戒指。 ");
					link.l1 = "可惜... 好吧, 还是谢谢你。 ";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "抱歉, 但这枚戒指是作为礼物送给我的, 所以我没有义务归还。 ";
			link.l1 = "礼物? ! 谁送给你的? ";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		
		case "TakeMayorsRing_S3":
			dialog.text = "当然是市长本人! ";
			link.l1 = "但他当时... 至少可以说, 喝醉了。 他什么都不记得了。 ";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		
		case "TakeMayorsRing_S4":
			dialog.text = "这和我有什么关系? 如果他喝醉了, 那是他的问题, 不是我的! ";
			link.l1 = "你真的需要和他争吵吗? 这是一枚结婚戒指, 你知道的... 还给我吧, 这么小的东西不值得麻烦。 ";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "好吧, 我把戒指还你, 但你要付我五千比索。 ";
				link.l1 = "好的, 拿上你的钱, 把戒指给我。 ";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "哦, 好吧。 让他拿去吧! ";
				link.l1 = "那是肯定的, 亲爱的! ";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		
		case "TakeMayorsRing_S6":
			dialog.text = "给你... ";
			link.l1 = "好的, 那么。 谢谢你的帮助, 亲爱的。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
		
//Jason --> 讨厌的贵族
		case "Badboy":
			pchar.GenQuest.Badboy.Brothel.City = npchar.city; //任务发布者的城市
			//log_info(pchar.GenQuest.Badboy.Brothel.City); // patch-6
			pchar.GenQuest.Badboy.Brothel.nation = npchar.nation;
			pchar.GenQuest.Badboy.Brothel.Name = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "你看, 我们这里有个讨厌的顾客 - " + pchar.GenQuest.Badboy.Brothel.Name + "。 他每次来都让我们很烦恼! 首先在酒馆喝醉, 然后到这里来, 挑个姑娘大吵大闹\n最糟糕的是他是贵族出身! 他是我们总督的远亲, 所以我们不得不忍受他的所有荒唐行为。 也许你能让那个年轻的傲慢家伙... 嗯... 冷静一点... 让他不再光顾我的场所? ";
			link.l1 = "你是说总督的亲戚? 嗯... 我不想与当局对抗。 真的很抱歉。 ";
			link.l1.go = "exit";
			link.l2 = "我想我可以安排。 告诉我, 在哪里可以找到那个混蛋? ";
			link.l2.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "这个时候他通常已经在酒馆了。 他在那里喝醉, 然后过来。 ";
			link.l1 = "我知道了。 好吧, 我可能会在那里遇见他。 ";
			link.l1.go = "exit";
			//创建花花公子
			int iRank, iType, b;
			string sBlade, sPistol;
			if (sti(pchar.rank) < 6) iType = 0;
			if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 16) iType = 1;
			if (sti(pchar.rank) >= 16) iType = 2;
			switch (iType)
			{
				case 0:
					iRank = 6;
					sBlade = "blade_12";
					sPistol = "pistol1";
					b = 25;
				break;
				case 1:
					iRank = sti(pchar.rank)+10;
					sBlade = "blade_09";
					sPistol = "pistol1";
					b = 65;
				break;
				case 2:
					iRank = sti(pchar.rank)+5;
					sBlade = "blade_14";
					sPistol = "pistol1";
					b = 40;
				break;
			}
			sld = GetCharacter(NPC_GenerateCharacter("Badboy", "citiz_"+(7+rand(1)), "man", "man", iRank, HOLLAND, -1, true, "citizen"));
			FantomMakeCoolFighter(sld, iRank, b, b, sBlade, sPistol, "bullet", makeint(iRank*5));
			sld.name = pchar.GenQuest.Badboy.Brothel.Name;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Badboy";
			sld.greeting = "noble_male"; // patch-6
			LAi_SetLoginTime(sld, 15, 22);
			LAi_SetSitType(sld);
			FreeSitLocator(pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit", "sit1");
			pchar.GenQuest.Badboy.Brothel.Type = iType; //记住类型
			pchar.GenQuest.Badboy.Brothel = "true";
		break;
		
		case "Badboy_complete":
			dialog.text = "哦, 你真是个男人, 不是吗? 我就知道可以指望你..";
			link.l1 = "能帮助这么好的女士和她的... 姑娘们, 我总是很高兴。 ";
			link.l1.go = "Badboy_complete_1";
		break;
		
		case "Badboy_complete_1":
			dialog.text = "你不仅勇敢, 而且非常勇敢。 我想用一种特殊的方式感谢你 - 一种只有女人才能感谢男人的方式。 你永远不会忘记的, 我保证。 上楼来, 勇敢的水手... ";
			link.l1 = "... ";
			link.l1.go = "Badboy_complete_2";
		break;
		
		case "Badboy_complete_2":
			pchar.questTemp.different.HostessSex.city = pchar.GenQuest.Badboy.Brothel.City;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); 
			DialogExit();
			if (sti(pchar.GenQuest.Badboy.Brothel.Type) != 2)
			{
				DeleteAttribute(pchar, "GenQuest.Badboy");
			}
			else
			{
				pchar.quest.Badboy_Brothel.win_condition.l1 = "location";
				pchar.quest.Badboy_Brothel.win_condition.l1.location = pchar.GenQuest.Badboy.Brothel.City +"_town";
				pchar.quest.Badboy_Brothel.function = "Badboy_friends";
				DeleteAttribute(pchar, "GenQuest.Badboy.Continue"); // patch-6
			}
			SaveCurrentQuestDateParam("questTemp.Badboy");
			if (!CheckAttribute(pchar, "questTemp.RomNaTroih"))
			{
				pchar.questTemp.RomNaTroih = true;
			}
		break;
		// < —讨厌的贵族
		
		//葡萄牙人
		case "Portugal":
			dialog.text = "有一个人欠我一些钱... 我不知该怎么说... ";
			link.l1 = "不用说! 为了看一眼你深邃的眼睛, 我会找到他, 把他榨干到最后一个比索! 告诉我他的名字! ";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "不, 不, 你误解我了, 船长! 这个人... 不要对他做坏事。 只是提醒他欠债。 他叫雨果.阿文德尔, 我想你会在卖非常便宜酒的地方找到他。 看在上帝的份上, 不要对他使用武力! \n就说... 提醒他答应过要付钱。 我不想联系卫兵, 但我有军官朋友, 所以告诉他我在等, 出于对他的尊重, 我最迟明天将被迫采取行动。 只是提醒他的承诺。 ";
			link.l1 = "您的话就是我的法律, 夫人。 我很乐意履行您的请求。 ";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			sld = InitHugo("Hugo","Avendell");
			FreeSitLocator("Marigo_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
			AddLandQuestMark(sld, "questmarkmain");
			SetFunctionTimerCondition("Portugal_BeginOver", 0, 0, 2, false);
			pchar.questTemp.Portugal = "begin";
		break;
		
		case "Portugal_exit":
			dialog.text = "谢谢你, 船长。 我真的希望他会表现出应有的谨慎。 ";
			link.l1 = "我确信如此, 夫人。 现在请允许我告辞。 ";
			link.l1.go = "exit";
			sld = characterFromId("Avendel");
			sld.lifeday = 0;
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "哦不! 别告诉我你对他做了可怕的事... 他没有钱, 我知道! 我们只是在同一个小镇长大, 我永远不会去找卫兵! 我只是想吓唬他一下... 在他醉死之前让他清醒一下! ";
			link.l1 = "嗯... 尽管如此, 这是你的钱。 别担心雨果, 他很好... 至少如果他醒酒的话会没事。 ";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "哦, 船长, 你不明白! 他曾经是... 嗯, 你知道, 他们被称为赏金猎人 - 雇佣兵, 他们追踪海盗和强盗并消灭他们。 但是, 至少可以说, 他并不是最幸运的\n不久前, 他终于挥霍一空, 失去了船员和船只, 从那以后, 他日复一日地沉溺于酒杯中。 为了旧情, 我有时允许他来这里。 他现在太... 太可怜了。 他曾经是拉芒什海岸我们镇上最英俊的男人, 看看他现在\n我知道他答应过你什么, 而你自掏腰包! 我把这钱还给你, 只是请不要对他做坏事, 我求你了, 船长! ";
			link.l1 = "好吧, 好吧, 夫人, 我知道了。 钱你留着, 是你的。 至于你的朋友, 我保证不会伤害他。 现在请允许我告辞, 我还有事要做。 另外, 很高兴能帮助这样一位美丽的女士。 ";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_tavern_7";
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Portugal = "AvendelTavern";
		break;
		
		// Addon 2016-1 Jason 海盗线
		case "mtraxx":
			dialog.text = "嘘, 小声点... 去请洛丽塔夫人和我约会。 然后上楼来, 我们可以自由交谈。 在那之前什么都不要说... 嘿, 水手, 摸我之前先去给夫人付钱! (咯咯笑) ";
			link.l1 = "这就去, 甜心... ";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
           DialogExit();
		   chrDisableReloadToLocation = false;
		   pchar.questTemp.Mtraxx = "jewelry_2";
		break;
		
		case "mtraxx_2":
			pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; //移除计时器
			dialog.text = "不, 不是我。 我会告诉你整个故事, 只是不要打断我。 ";
			link.l1 = "我洗耳恭听! ";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
			dialog.text = "那好吧。 大约一周前, 一艘军舰抵达圣多明各。 它要么在风暴中要么在战斗中受损, 所以立即开始修理, 船员搬到了堡垒。 然而, 它的船长把所有空闲时间都花在了这里。 连续两天, 他在我们一个姑娘的陪伴下喝酒放松。 是她得到了宝石, 而且不止一颗。 她不停地吹嘘 - 洛丽塔让我们保留顾客的礼物\n愚蠢的女孩甚至不知道礼物的真正价值, 而我马上就看出来了。 当她告诉我喝醉的船长如何吹嘘有一座装满琥珀的山时, 我立即给泰雷克斯写了一封信... ";
			link.l1 = "";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
			dialog.text = "船长下次来的时候, 我安排好了让他最喜欢的姑娘忙于另一个客户, 然后自己'接了'这个活。 我试图从他那里套出坐标, 可惜没有成功。 他只是不停地吹嘘自己将变得像克拉苏一样富有, 并返回旧世界\n关于位置一句话也没说。 我唯一知道的是他的船修好了, 打算驶往哈瓦那, 在那里他会尝试安排朝正确方向的任务。 毕竟他不是船主。 ";
			link.l1 = "那么, 他现在在哈瓦那? ";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
			dialog.text = "两天前黎明时启航了。 你是海员, 你算吧。 ";
			link.l1 = "船长的名字, 船的类型和名字, 有什么信息吗? ";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
			dialog.text = "怎么, 你把我当傻瓜吗? 他叫埃斯贝多.卡巴纳斯,'坎塔沃罗'号的船长。 我想水手们称它为纵帆船。 ";
			link.l1 = "这就是你知道的全部? ";
			link.l1.go = "mtraxx_7";
		break;
		
		case "mtraxx_7":
			dialog.text = "你还想要什么? 我确定你可以在到达哈瓦那之前追上他。 不过别浪费时间, 我认为他在离开古巴前往他的藏匿处之前不会休息太久, 到那时就没希望了。 再想想, 你可以待一两个小时, 毕竟你已经付钱了。 ";
			link.l1 = "说得对, 亲爱的。 一两个小时不会有太大区别... ";
			// belamour 传奇版 -->
			link.l1.go = "mtraxx_7S";
			link.l2 = "下次吧, 亲爱的。 考虑给自己放个午餐假。 去教堂, 或者别的什么。 ";
			link.l2.go = "mtraxx_7NS";
			sTotalTemp = npchar.id;
			AddMapQuestMarkCity("Havana", false);
			AddLandQuestMark(characterFromId("Havana_PortMan"), "questmarkmain");
		break;
		
		case "mtraxx_7S":
            DialogExit();
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // 用于丹内克
			Achievment_SetStat(23, 1);
			//< —访问次数
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //计数器
			AddDialogExitQuest("PlaySex_1");
			// 从妓院获得的加成
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 10);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// 状态变化
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;
		
		case "mtraxx_7NS":
            DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			AddQuestRecord("Roger_1", "3");
			pchar.questTemp.Mtraxx = "jewelry_3";
			SetFunctionTimerCondition("Mtraxx_JewelryHavanaOver", 0, 0, 7, false); // 计时器
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			pchar.quest.mtr_jewelry_havana.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_havana.win_condition.l1.location = "Cuba2";
			pchar.quest.mtr_jewelry_havana.function = "Mtraxx_HavanaInfo";
			DeleteAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor");
			DeleteAttribute(pchar, "questTemp.ZA.Block");
		break;
		// < —传奇版
		case "mtraxx_R":
			dialog.text = "哦... 真遗憾。 我还以为你是来度假的。 我的姑娘们非常想念勇敢的海盗。 好吧, 说吧, 什么任务? ..";
			link.l1 = "马库斯派我来你这里狂欢两天, 喝光所有的酒, 和每个姑娘上床。 我们什么时候开始? ";
			link.l1.go = "mtraxx_R1";
		break;
		
		case "mtraxx_R1":
			dialog.text = "啊, 查理.普林斯, 你的幽默和你的军刀一样锋利! 你差点让我不高兴... 姑娘们! 我们有客人, 特别的客人! 拿酒和食物来! ";
			if (sti(pchar.money) >= 31000)
			{
				link.l1 = "把这里每个漂亮姑娘都叫来! 我们要休息和娱乐! 哟吼吼! ..";
				link.l1.go = "mtraxx_R2";
			}
			else
			{
				link.l1 = "等一下, 珍妮特。 我需要从我的船上给你和你的女士们拿金子。 马上回来! ";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
				chrDisableReloadToLocation = false;
			}
		break;
		
		case "mtraxx_R2":
			AddMoneyToCharacter(pchar, -30000);
			dialog.text = "我希望我们所有的顾客都像你一样甜美。 英俊和慷慨... 我们会给你完美的放松。 姑娘们! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
		break;
		// belamour 夜间冒险家
		case "NA_Girl":
			dialog.text = "哦, 原来是个行家啊, 嘻嘻... 好吧, 好吧, 我有这样一个姑娘。 但她不便宜: " + makeint(pchar.GenQuest.NightAdventure_money) + " 比索。 "; 
			link.l1 = "成交。 ";
			link.l1.go = "NA_Girl_1";
		break;
		
		case "NA_Girl_1":
			AddMoneyToCharacter(pchar, -makeint(pchar.GenQuest.NightAdventure_money));
			dialog.text = "太好了, 亲爱的。 爱情女祭司会在楼上等你。 相信我, 你不会后悔的。 "; 
			link.l1 = "我已经不后悔了。 ";
			link.l1.go = "NA_Girl_2";
		break;
		
		case "NA_Girl_2":
			DialogExit();
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhore"; 
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_NobleWhore_7";
		break;
		// < —冒险家
		
		case "chicken_god":
			dialog.text = "给你和阿圭巴纳大人? 当然可以。 船长, 这需要一万。 ";
			if (sti(pchar.money) >= 10000) {
				link.l1 = "等等, 不是这样的! .. 该死的! 不管了, 给你钱。 ";
				link.l1.go = "chicken_god_pay";
			} else {
				link.l2 = "我能贷款吗? ";
				link.l2.go = "chicken_god_notpay";
			}
		break;
		
		case "chicken_god_pay":
			dialog.text = "祝您住宿愉快, 船长。 我们开门时请再来。 我们的场所为贵族男女提供各种休闲娱乐。 ";
			link.l1 = "... ";
			link.l1.go = "chicken_god_pay_1";
		break;
		
		case "chicken_god_pay_1":
			dialog.text = "";
			link.l1 = npchar.name+ "夫人, 你至少能解释一下这里发生了什么吗? 总督甚至知道你让一个本地人负责一个月吗? 我可以告诉你, 没有哪个定居点能忍受妓院关闭一天! ";
			link.l1.go = "chicken_god_pay_2";
		break;
		
		case "chicken_god_pay_2":
			dialog.text = "房间是你的了, 船长。 现在, 请原谅我。 ";
			link.l1 = "真迷人。 再见, 夫人。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_PayForRoom");
		break;
		
		case "chicken_god_notpay":
			dialog.text = "为什么, 主啊, 为什么? 滚出去! 走开, 走开, 我受不了了! 混蛋! ";
			link.l1 = "进展顺利。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotPayForRoom");
		break;
		
		//-->> Sinistra 三人浪漫
		case "RomNaTroih_1":
			dialog.text = "嗯... 我通常不这样做... 但我愿意为你冒险。 今天是你的幸运日, 船长! ";
			link.l1 = "我们走吧! ";
			link.l1.go = "exit";
			pchar.RomNaTroih_Shluha = npchar.id;
		break;
		
		case "RomNaTroih_2":
			dialog.text = "我生你的气了, 船长... 但如果你足够努力, 我会对你仁慈。 ";
			link.l1 = "哦, 我会的。 我们开酒好吗? ";
			link.l1.go = "exit";
			Achievment_Set("ach_CL_105");
		break;
		//<< —Sinistra 三人浪漫
	}
}

ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse" && rCharacter.horse == "HorseStay")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;			
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}