void ProcessDialogEvent()
{
	ref NPChar, her;
	aref Link, NextDiag;
	bool bOk = false;
    bool bOk2;
    
	int Sum, nRel, nDay, iChurchQuest2_Summ;
	ref sld;
	
	// Церковный квест № 2 -->
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra"))
	{
		iChurchQuest2_Summ = sti(PChar.rank)*100 + (rand(3)+1)*100;
		PChar.GenQuest.ChurchQuest_2.Summ_To_Contra = sti(iChurchQuest2_Summ);
	}
	// <-- Церковный квест № 2
	
	string sColony;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	// belamour legendary edition
	bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
	bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	//тереть нафиг аттрибут при прошествии дней (navy fix)
	if (CheckAttribute(pchar, "GenQuest.contraTravel.days") && GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
	{
		DeleteAttribute(pchar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
	}

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Smuggling_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlaceSmugglersOnShore(Pchar.quest.contraband.CurrentPlace);
			Pchar.quest.Contraband.active = true;
			pchar.GenQuest.Contraband.GuardNation = npchar.nation;
			pchar.GenQuest.Contraband.SmugglerId  = npchar.id;				
			SetAllContraGoods(&Stores[sti(Pchar.GenQuest.Contraband.StoreIdx)], npchar);
			ReOpenQuestHeader("Gen_Contraband");
            if (GetIslandByCityName(npchar.city) == "Mein")
            {
            	AddQuestRecord("Gen_Contraband", "t1_1");
            }
            else
            {
	            AddQuestRecord("Gen_Contraband", "t1");
				if (Pchar.quest.contraband.CurrentPlace == "shore30" || Pchar.quest.contraband.CurrentPlace == "shore31")
				{
					AddQuestUserData("Gen_Contraband", "sIsland", "Marie Galante");
				}
				if (Pchar.quest.contraband.CurrentPlace == "shore59")
				{
					AddQuestUserData("Gen_Contraband", "sIsland", "Tobago");
				}
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetLocationNameByID(Pchar.quest.contraband.CurrentPlace));
				
			DialogExit();
		break;
		
		case "First time":											
			//--> Jason если идёт первая часть квеста Шарля
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
            {
				dialog.text = "旦那、ここをお立ち去りください。私たちに話し合うことなど何もないと思います。";
				link.l1 = "「へえ、そうかい？俺の顔が気に入らねえのか？いいさ、もう行くぜ……」";
				link.l1.go = "exit";
				break;
			}
			//<-- идёт первая часть квеста Шарля
			//--> Addon-2016 Jason блокировка контры во избежание конфликтов с квестами
			if (CheckAttribute(pchar, "GenQuest.SmugglersBlock") && pchar.GenQuest.SmugglersBlock == npchar.location)
            {
				dialog.text = "今日は商売なしだ。";
				link.l1 = "なるほど。";
				link.l1.go = "exit";
				break;
			}
			//--> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
				dialog.text = "俺と仲間たちは今日はめちゃくちゃ忙しいんだ。";
				link.l1 = "でも俺には……";
				link.l1.go = "SantaMisericordia_1";
				break;
			}
			//<-- прибыла инспекция на Святом Милосердии
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.Consumption.Contra"))
            {
				dialog.text = "何の用だ、船長？";
				link.l1 = "少し話せるかい？";
				link.l1.go = "Consumption";
				break;
			}
			//<-- Цена чахотки
			
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "何の用だ、船長？お前の名前は知らねえし、俺の名前も教えられねえ。";
				Link.l1 = "俺が船長だ "+GetFullName(pchar)+".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1"; 
			}
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 1)
				{
					if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
					{
						pchar.GenQuest.CaptainComission.SpeakContra = true;
						dialog.text = "今日は商売にならねえ。どの湾にも巡回がいてな、うちの総督が、とある船長に押収された積荷を探してるんだ。"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" そいつはどこかに隠したんだ。";
						link.l1 = "「それで、その船長はどこにいるんだ」"+pchar.GenQuest.CaptainComission.Name+"?";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "今日は商売なしだ。";
						link.l1 = "なるほど。";
						link.l1.go = "exit";					
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "今日は商売なしだ。";
					link.l1 = "なるほど。";
					link.l1.go = "exit";
					break;
				}
				
				if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
				{
					dialog.text = "今日は商売なしだ。";
					link.l1 = "なるほど。";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "何の用だ、船長？";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("「急げ」 "+GetSexPhrase("相棒","娘")+"、何の用だ？奴らはお前を狙ってるぞ！","用件を手短に言え！兵士たちがお前を追っているし、時間がないんだ……");
				}
				// belamour legendary edition
				bOk2 = MCGovernon || MCAdmiral;
				if(FindContrabandGoods(PChar) != -1 && !bOk2)
				{
					Link.l1 = "何かを買いたいか売りたいんだ。";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "「航海のことだが……」";
				else
					Link.l2 = "俺は一か所に行く必要があるんだ。";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "俺にはちょっと“特別な”品があるんだが、あんたも興味あるだろう。見ていきな！";
						link.l3.go = "SM_ShipLetters_1";
					}	
				}				

				//Jason --> мини-квест Бесчестный конкурент
				if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
				{
					Link.l8 = "お前にちょっと変わった仕事があるんだ。";
					Link.l8.go = "Shadowtrader_smugglers";
				}
				// <-- мини-квест Бесчестный конкурент
				//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "聞いてくれ、相棒。ワインとラムの積荷が必要なんだ。多ければ多いほど、早ければ早いほどいい。";
					Link.l8.go = "TPZ_smugglers_1";
				}
				// <-- Торговля по закону
				//Jason --> генератор сбыта бакаута
				if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
				{
					Link.l9 = "マイケル・ローゼンクラフトに会う必要がある。あいつが興味を持つ貨物を持ってきたんだ。";
					Link.l9.go = "bakaut";
				}
				// <-- генератор сбыта бакаута
				
				// Церковный генератор №2 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "ちょっと知りたいことがあるんだ、相棒。";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}
				
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = "あなたの同僚であり、私の親しい友人が  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" 「何かの商売について知っていると聞いた。」";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <-- Церковный генератор №2
				
				Link.l7 = "何もない。またな。";
				Link.l7.go = "Exit";				
			}
		break;
		
		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "砦の地下室さ、他にどこがある？あの船長はいつでも当局に隠し場所をバラすかもしれねえ、 そしたら俺たちには何も残らねえんだ。騒ぎが収まるまでは商売のことなんか考えるなよ。";
				link.l1 = "聞けよ、お前はこの島の隅々まで知ってるだろう。船長がどこにいるか、本当に心当たりはないのか "+pchar.GenQuest.CaptainComission.Name+"隠し場所は？";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "天国にいるんだろうな。奴は仲間と一緒に絞首刑にされたんだ。だが、 死刑判決にはその船が海賊船だとは書かれていなかったぜ。";
				link.l1 = "「それで、なぜその船が海賊船だとそんなに確信しているんだ？」";
				link.l1.go = "CapComission_2";
			}	
		break;
		
		case "CapComission_2":
			dialog.text = "俺たちは岩場から戦いを見ていたんだ。望遠鏡で、あの船がジョリー・ロジャーを掲げているのが見えた。\nそれから五時間ほど経った頃、暗闇の中で閃光が走った――火薬庫で爆発が起きたように見えたぜ。\n荷を陸に運ぶには十分な時間だったな。";
			link.l1 = "船長がどこにいるか知らねえのか "+pchar.GenQuest.CaptainComission.Name+"「の隠し財産か？お前はこの島の隅々まで知ってるだろう。」";
			link.l1.go = "CapComission_3";
		break;
		
		case "CapComission_3":
			dialog.text = "いいや。俺たちもそれを探してるが、総督の道楽のためじゃねえ……";
			link.l1 = "なるほど……良い一日を。";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
		break;
		
		case "CapComission_4":
			dialog.text = "いいや。俺たちも探してるが、総督の道楽のためじゃねえ……へへ";
			link.l1 = "なるほど……良い一日を。";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;
				
		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "なぜそう決めたんだ？俺は正直な沿岸商人だ。他の買い手を探してくれ。";
				link.l1 = "「ありがとう……」";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "なぜだ？お前の「積み荷」が役に立つかもしれねえ。受け取れ "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" コインのことは忘れちまえ。";
					link.l1 = "いや、結構だ。";
					link.l1.go = "SM_ShipLetters_2";	
					link.l2 = "そしてその通りだ、俺もそれを忘れかけているんだ！";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "その通りだ！ますます気になってきたぜ。もし俺が金を払えば\n "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" コインさえあれば、その書類なんて全く気にしねえだろう。";
						link.l1 = "いや、結構だ。";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "「お前の言う通りだ。もうあいつらのことなんて忘れちまったぜ。」";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "さて、あの生意気な奴を捕まえるチャンスだぜ！俺は本当に、本当に気になってるんだ。ほら、金は払うぜ "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" 金で、机の上の書類のことなんてすっかり忘れてしまうんじゃないか？";
						link.l1 = "俺はやらねえ。";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "よし、取引成立だ！";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;
		
		case "SM_ShipLetters_2":
			dialog.text = "わかった、わかったが、これ以上敵を増やすのはやめろよ。";
			link.l1 = "「お前もな！」";
			link.l1.go = "exit";
		break;
		
		case "SM_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "7");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Meeting":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 2)
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
				{
					pchar.GenQuest.CaptainComission.SpeakContra = true;
					dialog.text = "今日は商売はなしだ。どの入り江にも巡回がいてな、我々の総督がある船長に押収された積荷を探しているんだよ"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" そして、どこかに隠したんだ。";
					link.l1 = "「で、その船長はどこにいるんだ」"+pchar.GenQuest.CaptainComission.Name+"?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "今日は商売なしだ。";
					link.l1 = "なるほど。";
					link.l1.go = "exit";					
					break;
				}
			}
			
			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "今日は商売なしだ。";
				link.l1 = "なるほど。";
				link.l1.go = "exit";
				break;
			}
			
			if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
			{
				dialog.text = "今日は商売なしだ。";
				link.l1 = "なるほど。";
				link.l1.go = "exit";
				break;
			}
			
			Dialog.Text = "「どうされましたか、船長？」";
			
			bOk2 = MCGovernon || MCAdmiral;
			if(FindContrabandGoods(PChar) != -1 && !bOk2)
			{
				Link.l1 = "品物を買いたいか売りたいんだ。";
				Link.l1.go = "Meeting_1";
			}
			
			Link.l2 = "俺はある場所に行く必要があるんだ。";
			Link.l2.go = "Travel";				
			
			//Jason --> мини-квест Бесчестный конкурент
			if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
			{
				Link.l8 = "お前にちょっと変わった仕事を頼みたいんだ。";
				Link.l8.go = "Shadowtrader_smugglers";
			}
			// <-- мини-квест Бесчестный конкурент
			//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "聞いてくれ、相棒。ワインとラムの積荷が必要なんだ。多ければ多いほど、早ければ早いほどいい。";
					Link.l8.go = "TPZ_smugglers_1";
				}
			// <-- Торговля по закону
			//Jason --> генератор сбыта бакаута
			if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
			{
				Link.l9 = "マイケル・ローゼンクラフトに会う必要がある。あいつが興味を持つ貨物があるんだ。";
				Link.l9.go = "bakaut";
			}
			// <-- генератор сбыта бакаута
			
			// Церковный генератор №2 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "ちょっと知りたいことがあるんだ、相棒。";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = "「あなたの同僚で、私の親しい友人が」  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" 「何か商売のことを知っていると言っていた。」";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- Церковный генератор №2

			Link.l5 = "何もない。じゃあな。";
			Link.l5.go = "Exit";				
		break;

		// Церковный генератор №2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "俺はお前の友達じゃねえ。しかも、それが命取りになるかもしれねえぞ。";
				link.l1 = "ふむ。俺が知りたいのは、せいぜいこのくらいの値段のことだ "+FindRussianMoneyString(iChurchQuest2_Summ)+".";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;
			
		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "コインをよこせ。こんな額じゃ大したものは手に入らねえってことを覚えとけよ。";
				link.l1 = "ほら、仲間たちに会い損ねたんだ。集まりに遅れてしまって、みんな待っててくれなかったんだよ……";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "ははっ、お前は一文無しじゃねえか！金を持ってから出直して来いよ。";
				link.l1 = "確かに、すぐに取りかかる。";
				link.l1.go = "exit";
			}
			break;
			
		case "Contra_GenQuest_Church_2_3":
				dialog.text = "「それで、俺が必要な理由は何だ？」";
				link.l1 = "奴らは町にはいないし、船も持っていない。だからこう考えたんだ――もしかしてお前の商売仲間が奴らに何か便宜を図ったんじゃねえか？";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;
			
		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "なるほどな……何人かの男に会ったが、島から逃げたいと言っていて、行き先なんてどうでもいい様子だった。そういう場合、 理由なんて聞かねえさ、支払いのことだけだ。俺たちは航海に出たんだ\n "+XI_ConvertString("Colony"+sColony+"Acc")+" , "+XI_ConvertString(locations[FindLocation(sColony+"_Town")].IslandID+"Dat")+" 。金の話がまとまれば、そこまで連れて行ってやるぜ。";
			link.l1 = "ありがとう、でも俺には自分の船があるんだ。";
			link.l1.go = "exit";
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "8");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + sColony + "Acc"));
			AddQuestUserData(sQuestTitle, "sIsland", XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Voc"));
			PChar.GenQuest.ChurchQuest_2.AskContra_2 = true;
			PChar.GenQuest.ChurchQuest_2.Contra_Colony = sColony;
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_1":
			dialog.text = "俺はお前と取引したことはねえ。";
			link.l1 = "直せるさ。お前は少し前に俺の仲間をここに連れてきただろう。俺は会合を逃したんだが "+GetSexPhrase("奴ら","奴ら")+".";
			link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "ふむ、俺たちはやつらを上陸させたのは "+XI_ConvertString(sGenLocation+"Gen")+"…なあ、あいつらがあんたの仲間ならいいが、そうじゃねえなら、ちょっかい出すのはやめといた方がいいぜ。";
			link.l1 = "ご心配ありがとうございますが、私は十分に武装しているし、かなり魅力的なんですよ。";
			link.l1.go = "exit";
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "9");
			AddQuestUserData(sQuestTitle, "sShore", XI_ConvertString(sGenLocation + "Gen")); // belamour gen
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			SetFunctionTimerCondition("Church_GenQuest2_TimeIsLeft", 0, 0, 1, false);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2");
		break;
		// <-- Церковный генератор №2

		case "Meeting_1":
			Dialog.Text = "ふん……それが俺に何の関係があるんだ？道に迷ったんじゃねえか、船長。店に行って、 好きなものを買うなり売るなりしてこいよ。";
			Link.l1 = "いいや、お前が必要だ。";
			Link.l1.go = "Meeting_2";				
			Link.l2 = "ご助言ありがとうございます。良い一日をお過ごしください。";
			Link.l2.go = "exit";				
		break;

		case "Meeting_2":
			Dialog.Text = "何のためだ？";
			Link.l1 = "もしかして特別な品に興味があるかい？それとも、代わりに俺に何か持ってきたのか？"Link.l1.go ="Meeting_3";				
		break;

		case "Meeting_3":
			int iTmp = false;
			int iChIdx, i;
			
			float fMaxClass = ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5);
			if (IsEquipCharacterByArtefact(pchar, "talisman21")) fMaxClass = 2.0;
			
			if (GetCompanionQuantity(pchar) > 1) iTmp = true;
			if (GetCharacterShipClass(pchar) < fMaxClass) iTmp = true;

			// поиск мин.  те старшего класса
			/* for (i=0; i<COMPANION_MAX; i++)
			{
				iChIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iChIdx>=0)
				{
					sld = GetCharacter(iChIdx);
            		if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
				}
			} */
			
			if (iTmp)
			{
				dialog.text = NPCStringReactionRepeat("次は王立軍艦でも奪ってきたらどうだ？お前の船は砦からすぐに見つかっちまうぜ。俺たちの首が危ねえんだ。 次は小さい船一隻で来いよ。","もう一度言わせるのか？もっと小さい船を見つけてから話そう。","本当にそんなに間抜けなのか？スクーナーかブリッグを手に入れろ。そうすりゃ初めて取引になるんだぜ。","「ああ、なんて間抜けなんだ……」","ブロック",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("わかった、君の言うことは理解した。","分かりました、ちょっと確認したいことがあっただけです。","いや、バカじゃねえ、ただのケチだ。何か変わったかと思ったがな。もう何隻かピナスをもらいたいもんだぜ…","鏡を見ろ……",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
				break;
			}
			bOk  = CheckAttribute(pchar, "GenQuest.contraTravel.active") && (sti(pchar.GenQuest.contraTravel.active) == true);
			bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
			bool bOk3 = CheckAttribute(Pchar, "questTemp.pirateStartQuest") && (Pchar.questTemp.pirateStartQuest == "3");
			if (bOk)
			{
			    if (GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
				{  // просрочка
					DeleteAttribute(PChar, "GenQuest.contraTravel");
					CloseQuestHeader("Gen_ContrabandTravel");
					bOk = false;
				}
			}

//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "「すまない」 "+GetSexPhrase("相棒","娘")+"、もう忙しいんだ。数日後にまた来てくれ。";
				Link.l1 = "残念だな……";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--

			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "まずは今の用件を片付けてからにしないか？";
				Link.l1 = "そうかもしれねえな。";
				Link.l1.go = "Exit";				
			}
			else
			{
                if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;
                    
                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
                        if (Pchar.quest.contraband.CurrentPlace != "None")//boal fix
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = "お前さんとは商売ができると分かってるぜ。俺たちはここで待ってるからな "+GetLocationNameByID(Pchar.quest.contraband.CurrentPlace)+".";
                            }
                            else
                            {
            				    Dialog.Text = "ふむ……買い手を見つけてやれるかもしれねえ。俺たちはそこで待ってるぜ\n "+GetLocationNameByID(Pchar.quest.contraband.CurrentPlace)+".";
            				}
            				Link.l1 = "わかった。そこで会おう。";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
                            Dialog.Text = "今日は商売はない。明日また来な。";
            				Link.l1 = "「いいだろう。」";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "あんなことをした後で、誰があんたと一緒に働きたいと思うんだ？\n賞金稼ぎを差し向けなかっただけでも感謝しな。";
        				Link.l1 = "残念だな。俺が密輸業者になるチャンスはなしか。";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    Dialog.Text = "今日は商売はない。明日また来い。";
    				Link.l1 = "「いいだろう。」";
    				Link.l1.go = "Exit";
				}
			}
		break;
////////////////////////////////////////////////////////////////////////////////
//	Корсарское метро
////////////////////////////////////////////////////////////////////////////////
		case "Travel":
//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "「すまない」 "+GetSexPhrase("相棒","少女")+"、今はもう忙しいんだ。数日後にまた来てくれ。";
				Link.l1 = "残念だな。";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--
			//если нет корабля у ГГ и нет компаньонов все ок
			if (sti(pchar.ship.type) == SHIP_NOTUSED && GetCompanionQuantity(pchar) == 1 && GetPassengersQuantity(pchar) == 0)
			{
				//случай если уже была инфа
				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
				{
					//платил уже
					if (CheckAttribute(pchar, "GenQuest.contraTravel.payed") && sti(pchar.GenQuest.contraTravel.payed) == true)
					{
						Dialog.Text = "もう取引の話はすでにまとまっていたと思ってたんだが？";
						Link.l2 = "「確かに！」";
					}
					//не платил, значит можно запалатить пока не вышел срок.
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "金は持ってきたか？";
							Link.l1 = "ああ。";
							Link.l1.go = "Travel_pay";
							Link.l3 = "気が変わった……";
							Link.l3.go = "Travel_abort";
							Link.l2 = "「まだだ。」";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "もう全部話したぞ。";
								Link.l2 = "「その通りだ。」";
								Link.l1 = "気が変わった……";
								Link.l1.go = "Travel_abort";
							}
							else // просрочка
							{
							    Dialog.Text = "今日は手伝えねえな。二日後にまた来な、そしたら何か用意できるかもしれねえぜ。";
								Link.l2 = "残念だな。";
								DeleteAttribute(PChar, "GenQuest.contraTravel");
								CloseQuestHeader("Gen_ContrabandTravel");
							}
						}
					}
				}
				//если не было договора, обговариваем условия
				else
				{
					nRel = ChangeContrabandRelation(pchar, 0);
					//если нормальные отношения и количество подстав меньше 20, работаем....
					if (nRel > 0 && Statistic_AddValue(PChar, "contr_TravelKill", 0) < 20)
					{
						//бухта...
						pchar.GenQuest.contraTravel.CurrentPlace = SelectSmugglingLocation();
						aref arTmp; makearef(arTmp, pchar.GenQuest.contraTravel);
						SetSmugglersTravelDestination(arTmp);
						//за сколько доставят 
						pchar.GenQuest.contraTravel.price = (sti(PChar.rank)*250 + (100 - nRel)*10 + rand(30)*20) + sti(arTmp.destination.days)*100;
						
						//если метро активно, и нет пассажиров у ГГ, и ещё сегодня не виделись, есть доступная бухта, и ранд ...
						bOk = !bPauseContrabandMetro && CheckNPCQuestDate(npchar, "Travel_Talk") && 
							Pchar.GenQuest.contraTravel.CurrentPlace != "None" && rand(50) < nRel;
                        bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
						if (bOk && !bOk2)
						{
							nDay = 1 + rand(3);
							SetNPCQuestDate(npchar, "Travel_Talk");
							SaveCurrentQuestDateParam("contraTravel");

							Dialog.Text = "まあ、そこまで連れて行ってやるぜ "+GetLocationNameByRef(&locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)])+" 近く "+XI_ConvertString("Colony"+pchar.GenQuest.contraTravel.destination+"Gen")+" のため "+pchar.GenQuest.contraTravel.price+" 金だ。金を持ってこい "+FindRussianDaysString(nDay)+"。船はあなたを で待っている "+GetLocationNameByRef(&locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)])+" ちょうど24時間。";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "俺はそれで構わねえぜ。";
							Link.l1.go = "Travel_agree";
							Link.l2 = "いいえ、結構です。";
						}
						else
						{
							Dialog.Text = "今日は手伝えねえな。二日後にまた来てくれ、そしたら何か用意できるかもしれねえぜ。";
							Link.l2 = "残念だな。";
						}
					}
					//нет, посылаем в сад
					else
					{
                        Dialog.Text = "あれだけのことをしておいて、誰かがお前と一緒に働きたいと思うと本気で思ってるのか？ 俺たちが賞金稼ぎを差し向けなかっただけでも感謝しろ。出ていけ！";
        				Link.l2 = "ふん、また運がなかったな。";
					}

				}
			}
			//корабль есть, посылаем в сад...
			else 
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "いや、お前たち全員は連れて行かねえ。ひとりだけだ。";
					Link.l2 = RandSwear()+"どうせ俺には必要ねえよ！";
				}
				else
				{
					Dialog.Text = "なぜ自分の船を使わないんだ？いや、俺たちはお前を乗せてやらねえ。";
					Link.l2 = "わかった、好きにしな。";
				}
			}
			Link.l2.go = "Exit";
			break;

		//отмена
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "「お前の好きにしろ。」";
			Link.l1 = "";
			Link.l1.go = "Exit";
			break;

		//ГГ согласен ехать
		case "Travel_agree":
			ReOpenQuestHeader("Gen_ContrabandTravel");
			AddQuestRecord("Gen_ContrabandTravel", "1");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetLocationNameByID(pchar.GenQuest.contraTravel.CurrentPlace));
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetLocationNameByID(pchar.GenQuest.contraTravel.destination.loc));
			AddQuestUserData("Gen_ContrabandTravel", "sPlaceTo", XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"));
			AddQuestUserData("Gen_ContrabandTravel", "sDays", FindRussianDaysString(sti(pchar.GenQuest.contraTravel.days)));
			AddQuestUserData("Gen_ContrabandTravel", "sPrice", pchar.GenQuest.contraTravel.price);

			//активируем квест
			pchar.GenQuest.contraTravel.active = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;

		//ГГ согласен платить
		case "Travel_pay":
			//денег хватает?
			Sum = sti(pchar.GenQuest.contraTravel.price);
			if (sti(pchar.money) >= Sum)
			{
				AddMoneyToCharacter(pchar, -1*Sum);
				//ставим флаг оплаты
				pchar.GenQuest.contraTravel.payed = true;
				Dialog.Text = "取引できて嬉しいぜ。船に遅れるなよ。";
				Link.l1 = "やってみるぜ。";
				AddQuestRecord("Gen_ContrabandTravel", "2");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
				
				//ставим контру.
				PlaceSmugglersOnShore(PChar.GenQuest.contraTravel.CurrentPlace);
				//корабль на волнах в бухте....
				Sum = sti(pchar.GenQuest.contraTravel.destination.days);
				sld = GetCharacter(NPC_GenerateCharacter("Abracham_Gray", "citiz_46", "man", "man", 5, PIRATE, Sum + 2, true, "hunter"));
				//воскресим...
				sld.nation = PIRATE;
				SetRandomNameToCharacter(sld);
				SetMerchantShip(sld, rand(GOOD_PAPRIKA));
				SetFantomParamHunter(sld);
				SetCaptanModelByEncType(sld, "pirate");
				SetCharacterShipLocation(sld, PChar.GenQuest.contraTravel.CurrentPlace);

				SetTimerCondition("RemoveTravelSmugglers", 0, 0, 1, false);
			}
			//нет, посылаем в сад...
			else
			{
				Dialog.Text = "金が足りないようだな。";
				Link.l1 ="残念だな、また後で来るぜ。";
				Link.l1.go = "Exit";
			}
		break;  
////////////////////////////////////////////////////////////////////////////////
//	END OF Корсарское метро
////////////////////////////////////////////////////////////////////////////////
				
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_smugglers":
			dialog.text = "とても興味深いな。持っているものを見せてくれ。";
			link.l1 = "とても「特別」な品物を魅力的な値段で取引できる地下商店があると聞いたんだが、 その店の立ち上げにあんたが関わっていたとも耳にした。その店の主人と話がしたいんだ。";
			link.l1.go = "Shadowtrader_fail";
			link.l2 = "「とても“特別”な品物を魅力的な値段で取引できる地下の店があるって聞いたんだ。\n数日後には出航しなきゃならないし、地元の店じゃ必要なもの全部を買う金が足りなくてな……だから、少しでも金を節約したいし、しなきゃならねえ……お前がその手助けをしてくれるって話を何人かから聞いたぜ。」";
			link.l2.go = "Shadowtrader_smugglers_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.seeksmugglers");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fail":
			dialog.text = "何を言ってるんだ？お前の言ってることが分からねえな。ここで店なんか開いてねえし、そんなのデタラメだ、ははっ！ 取引したいなら、品物を持ってきな。そしたらいつも通り話をしようじゃねえか……店だとよ、はっ！";
			link.l1 = "ふむ……";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			AddQuestRecord("Shadowtrader", "3");
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_smugglers_1":
			dialog.text = "割引が欲しいのか？簡単だ。日が暮れたら港長の部屋の前に来い。うちの者が迎えに行って、 しかるべき場所へ案内するぜ。 ";
			link.l1 = "よし。俺も行くぜ！";
			link.l1.go = "Shadowtrader_smugglers_2";		
		break;
		
		case "Shadowtrader_smugglers_2":
			pchar.questTemp.Shadowtrader.SeekTrader = "true";
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
			AddQuestRecord("Shadowtrader", "5");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			SetFunctionTimerCondition("ShadowtraderTimeSmugglers_Over", 0, 0, 2, false);
			int iNation = pchar.questTemp.Shadowtrader.nation;
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+3;
			sld = GetCharacter(NPC_GenerateCharacter("ShadowAgent_1", "citiz_"+(rand(9)+41), "man", "man", iRank, iNation, 2, true, "quest"));
			SetFantomParamFromRank(sld, iRank, true);
			GiveItem2Character(sld, "blade_04");
			EquipCharacterbyItem(sld, "blade_04");
			LAi_SetCitizenType(sld);
			sld.dialog.Filename = "Common_citizen.c";
			sld.dialog.currentnode = "First time";	
			sld.greeting = "cit_common"; 
			sld.city = pchar.questTemp.Shadowtrader.City;
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City +"_town", "goto", "goto1");
			pchar.quest.Shadowtrader_SMG.win_condition.l1 = "locator";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.location = pchar.questTemp.Shadowtrader.City + "_town";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator_group = "reload";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator = "reload10_back";
			pchar.quest.Shadowtrader_SMG.win_condition.l2 = "Night";
			pchar.quest.Shadowtrader_SMG.function = "ShadowAgent";
			DialogExit();
		break;
		// <-- Бесчестный конкурент
		//--> Торговля по закону
		case "TPZ_smugglers_1":
			dialog.text = "はは、カウンターの向こうにいるあの野郎がお前を寄越したんだろう？";
			link.l1 = "関係あるか？お前にできるのか、それとも他の奴を探した方がいいか？";
			link.l1.go = "TPZ_smugglers_2";
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_smugglers_2":
			dialog.text = "欲しいもんは何でも手に入れてやるぜ、わかったか？金さえ合えばな。だが、あの忌々 しい総督が厳しく取り締まりやがってよ。今じゃ酒には手を出さねえ――瓶がガチャガチャ鳴って、遠くからでもバレちまうし、儲けは雀の涙、首吊り台行きのリスクは天井知らずだ。だから、 悪く思うなよ。";
			link.l1 = "ふむ……それで、あんたは何でも手に入れられるって言うんだな。";
			link.l1.go = "TPZ_smugglers_3";		
		break;
		
		case "TPZ_smugglers_3":
			dialog.text = "できるさ！ただ、やりたくねえだけだ。知ってるか？総督邸のすぐ隣に住んでる奴がいるんだぜ、信じられるか？ははっ。 まったく間抜けな野郎だよ……何の話だっけ？ああ、そうだ。そいつはこっそり酒を闇で売ってるんだ。総督のカツラの真下でな、ははっ。 そいつに聞いてみな、何か手がかりをくれるかもな。量は少ねえし、子供の遊びみたいなもんだが、まあ何かにはなるさ。 ";
			link.l1 = "あまり役には立たなかったが、とにかく礼を言うぜ。";
			link.l1.go = "TPZ_smugglers_4";		
		break;
		
		case "TPZ_smugglers_4":
			DialogExit();
			AddQuestRecord("TPZ", "3");
			DeleteAttribute(pchar, "questTemp.TPZ_ContraInfo");
			
			// проведаем дом Кристиана
			sld = GetCharacter(NPC_GenerateCharacter("TPZ_Kristian", "citiz_17", "man", "man", 1, FRANCE, -1, false, "quest"));
			sld.name = "Christian";
			sld.lastname = "Deluce";
			LAi_SetOwnerType(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			sld.City = "BasTer";
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону

		//--> Цена чахотки
		case "Consumption":
			dialog.text = "ここには酔っぱらいがたくさんいるぜ、用がねえなら旦那、飲むか話すかしな。ここは賑やかな場所だ。";
			link.l1 = "もう一度やってみよう。君の時間と俺の好奇心のために金を払うぜ。俺には答えが必要なんだ。";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			if (sti(pchar.money) >= 3002)
			{
				dialog.text = "あいつには払わせるさ、はっ！俺の時間は安くねえんだ、旦那、三千ペソと、このクソまずい酒――ラムとやらも込みだぜ。";
				link.l1 = "取引成立だ！さて、お前の仲間で半年もこの土地の牢屋に入れられて、その後亡くなった奴について教えてくれ。 そいつに何があったんだ？";
				link.l1.go = "Consumption_2";
			}
			else
			{
				dialog.text = "銀貨で懐を膨らませた方がいいぜ、いや、金貨ならなおさらだ。そしたら話を聞いてやるよ。 タダで話す暇なんてねえんだ。";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3002);
			dialog.text = "それは覚えているが、なぜあんたがこんなことに興味を持つのかは分からねえな。 あのガキは牢の中で本当に気が狂っちまった。酒浸りになって、いつも人を連れ去る消耗病のことや、 誰もそれから逃れられねえっていう戯言ばかり言ってたよ。その消耗病には名前があって、 それを口に出してはいけねえとも言ってた。もし口にしたら――お前も連れていかれるってな。";
			link.l1 = "「それで、その後彼はどうなったんだ？」";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "話の結末は妙なんだ、旦那。最初は地元の連中や船乗りたちも彼の話を面白がってたが、やがてみんな飽きちまった。 どんな作り話でも、いつもそうさ。だから連中は彼をけしかけて、その名前を言わせたんだ。男は必死に抵抗してたが、 嘲笑に耐えきれず、ついに叫んじまったんだよ\n誰も特別なことは感じなかったし、ロウソクも消えなかった。だが翌朝、 哀れな奴は酒場の裏で喉を切られて死んでるのが見つかったんだ。";
			link.l1 = "ここには魔法なんて見当たらねえ。名前を言え。";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "名前は覚えてるが、くそっ、口には出さねえよ。どうもこの一件には不気味なものを感じるんだ。お前もそう思わねえか？ ";
			link.l1 = "おい、相棒、俺から小銭の詰まった財布を受け取ったよな、覚えてるか？それじゃあ、名前を教えてくれねえか？";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "ああ、うまくはいかねえよ、旦那、信じてくれ……（声をひそめて）奴が言ったんだ――フアンだってよ……";
			link.l1 = "くそっ！フアン？ただの普通の名前だし、ここじゃよくある名前だぜ。なんでそんなに特別なんだ？";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "知らねえが、その名前を口にした男は殺されたんだ。俺の勘だが、その名前には何かとんでもねえことがある。\nそれだけ知りたかったのか？";
			link.l1 = "そうだな。自分で酒でも買えよ。またな！";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Consumption.Contra");
			pchar.questTemp.Consumption.AskJuan = 0;
			pchar.questTemp.Consumption = "current";
			AddQuestRecord("Consumption", "6");
		break;
		//<-- Цена чахотки
		
		//Jason --> генератор сбыта бакаута
		case "bakaut":
			dialog.text = "そうかい？いいだろう。ローゼンクラフト旦那がアイアンウッドの一山を必要としてるが、量は最低でも "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+"。積み荷は十分あるか？";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "ああ、知っている。ローゼンクラフト旦那はどこにいるんだ？";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "ふむ。今はそんなに持っていないんだ。";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			dialog.text = "ローゼンクラフト旦那を邪魔するな。荷が十分に集まったら来い。";
			link.l1 = "「いいだろう。」";
			link.l1.go = "exit";
		break;
		
		case "bakaut_1":
			dialog.text = "奴のガレオン船はこの岸辺の近くを巡航しているだろう "+XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen")+" 数日間だ。だから遅れるなよ――あいつは別の群島に出航しちまうかもしれねえぞ。";
			link.l1 = "わかった、急ぐよ。ありがとう！";
			link.l1.go = "bakaut_2";
		break;
		
		case "bakaut_2":
			DialogExit();
			sld = characterFromId("Rozencraft");
			sld.DeckDialogNode = "bakaut";
			DeleteAttribute(sld, "DontDeskTalk"); // можно выслать шлюпку
			pchar.GenQuest.Bakaut.Info = "true";
			ReOpenQuestHeader("Bakaut");
			AddQuestRecord("Bakaut", "1");
			AddQuestUserData("Bakaut", "sIsland", XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen"));
			AddQuestUserData("Bakaut", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Bakaut.DaysQty)));
			AddQuestUserData("Bakaut", "sQty", FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)));
			// таймер
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1 = "Timer";
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.function = "Bakaut_RozencraftRemove";
		break;
		// <-- генератор сбыта бакаута
		
		//--> прибыла инспекция на Святом Милосердии
		case "SantaMisericordia_1":
			dialog.text = "俺は明日まで生き延びなきゃならねえんだ。あの忌々しい「マーシー」が町に来てるんだ。出て行け。";
			link.l1 = "なんて大げさなんだ……";
			link.l1.go = "exit";
		break;
		//<-- прибыла инспекция на Святом Милосердии
	}
}
