#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
string sProf;		//  без оффа hasert	
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// доп повека
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (0.06 + frnd()*0.1);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\PortMan\" + NPChar.City + "_PortMan.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    int i, cn, iTemp;
    ref chref, compref; // без оффа hasert
	ref rRealShip;
    string attrL, sTitle, sCapitainId, s1;
	string sColony;
    
	String sLastSpeakDate = LastSpeakDate();
	
	// Warship 25.07.09 Генер "Сгоревшее судно". Даты отказа ГГ - если отказал, то предложит снова только на след сутки
	if(CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate") && NPChar.Quest.BurntShip.LastQuestDate != sLastSpeakDate)
	{
		DeleteAttribute(NPChar, "Quest.BurntShip");
	}
    
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
    string sFrom_sea = "";
	npchar.quest.qty = CheckCapitainsList(npchar); //для списка кэпов

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}
	
	attrL = Dialog.CurrentNode;
	// hasert блок для сторожа ==>
	if(HasSubStr(attrL, "ShipStockManBack11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}
	
	if(HasSubStr(attrL, "ShipStockManBack22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}

	if(HasSubStr(attrL, "ShipStockManBack2_"))
	{
		i = findsubstr(attrL, "_" , 0);
		AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));

		chref = GetCharacter(sti(NPChar.ShipToStoreIdx));//сторож

		////DownCrewExp(chref,GetNpcQuestPastDayParam(chref, "ShipInStockMan.Date"));

        int iChar = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); //выбранный пассажир
		compref = GetCharacter(iChar);

		DeleteAttribute(compref,"ship");//зачем-то стираем корабль офицера, хотя его там и не должно быть
		compref.ship = "";

		aref    arTo, arFrom;

		makearef(arTo, compref.ship);
		makearef(arFrom, chref.Ship);
		CopyAttributes(arTo, arFrom);

		// снимем пассажира -->
		CheckForReleaseOfficer(iChar);//увольнение офицера с должностей, если он не просто пассажир
		RemovePassenger(pchar, compref);
		// снимем пассажира <--
		SetCompanionIndex(pchar, -1, iChar);
		PortmanDelBakSkill(compref);
		DeleteAttribute(chref, "ShipInStockMan");
		if(CheckAttribute(chref, "DontNullShip"))
		{
			DeleteAttribute(chref, "DontNullShip");
			DeleteAttribute(NPChar, "DontNullShipBeliz");
		}
		chref.id = "ShipInStockMan";//сбрасываем индекс к стандартному, чтобы этот номер массива в следующий раз можно было занять
		DeleteAttribute(chref,"ship");//затираем данные корабля у сторожа
		chref.ship = "";
		LAi_SetCurHP(chref, 0.0);//ещё и убивать непися, чтоб точно очистился из массива?

		NPChar.Portman	= sti(NPChar.Portman) - 1;
		pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		Dialog.CurrentNode = "exit";//закрываем диалог, ещё одно подтверждение уже не справшиваем
	}
	
	if(HasSubStr(attrL, "ShipStockMan11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_2";
	}

	if(HasSubStr(attrL, "ShipStockMan22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_2";
	}
    //  <=== hasert
    
	if(HasSubStr(attrL, "BurntShip19_"))
	{
		i = findsubstr(attrL, "_" , 0);
	 	NPChar.Quest.BurntShip.ShipCompanionIndex = strcut(attrL, i + 1, strlen(attrL) - 1); // индех в конце
 	    Dialog.CurrentNode = "BurntShip19";
	}
    
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("町で警報が鳴らされて、今や皆がお前を探している。俺だったら、そこにはとどまらねえな。","街の衛兵たちがみんなお前を探して町中を捜索してるんだ。俺はバカじゃねえからお前なんかと話さねえよ！","「走れ」 "+GetSexPhrase("相棒","娘")+"……兵士たちに蜂の巣にされる前にな……"),LinkRandPhrase("何の用だ、 "+GetSexPhrase("悪党","くせえ野郎")+"！？街の衛兵どもがお前の匂いを嗅ぎつけたぞ、このままじゃ逃げ切れねえぞ、汚ねえ海賊め！","殺人者め、今すぐ私の家から出て行け！衛兵！","俺はお前なんか怖くねえ、 "+GetSexPhrase("ろくでなし","「ネズミ」")+"「もうすぐ砦で吊るされるぞ、お前は遠くへは行けねえ……」"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("へっ、警報なんざ俺には問題じゃねえ……","奴らに俺は絶対捕まらねえ。"),RandPhraseSimple("黙れ "+GetWorkTypeOfMan(npchar,"")+"、下手すりゃその汚ねえ舌を引き抜いてやるかもな！","へっ、 "+GetWorkTypeOfMan(npchar,"")+"、そしてそこにいる全員が「海賊を捕まえろ！」ってな。だから言うんだ、相棒、静かにしてりゃ命は助かるぜ……"));
				link.l1.go = "fight";
				break;
			}
			//Jason, фрахт
			if (CheckAttribute(pchar, "questTemp.WPU"))
			{
				if (pchar.questTemp.WPU.Fraht == "fail" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					dialog.text = "ああ、お前が誰か知ってるぞ。荷物を運ぶ契約だったのに、盗みやがったな！衛兵、衛兵！";
					Link.l1 = "「アーッ！」";
					Link.l1.go = "exit";
					LAi_group_Attack(NPChar, Pchar);
					break;
				}
			}
			//фрахт
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				dialog.text = "旦那、私に何かご用ですか？";
				Link.l1 = "お前に用があるんだ……";
				Link.l1.go = "quests";
				Link.l2 = "申し訳ないが、俺は行かなくちゃならねえ。";
				Link.l2.go = "exit";
				NPChar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			if(NPChar.quest.meeting == "0")
			{
				
				dialog.text = "「ごきげんよう」 "+GetAddress_Form(NPChar)+"。お会いするのは初めてだと思います。私は "+GetFullName(npchar)+" - 港湾長だ。";
				Link.l1 = "「こんにちは。」 "+GetFullName(NPChar)+"。私は "+GetFullName(PChar)+"「、『」の船長"+PChar.ship.name+"「。」";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice")
				{
					dialog.text = "マッカーサー船長、いつも言っているが、毎回私に報告する必要はないんだ。心配しなくていい。";
					link.l1 = "やめろ、旦那 "+npchar.lastname+" 俺も他のみんなと同じだぜ。";
					Link.l1.go = "node_2";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.text = LinkRandPhrase("「ごきげんよう。」 "+GetAddress_Form(NPChar)+"。私に何か用か？","「こんにちは。」 "+GetFullName(Pchar)+"。あなたの船が我々の港に入るのを見て、きっと私に会いに来ると思っていました。","「ああ、船長」 "+GetFullName(Pchar)+"。何の用で俺のところに来たんだ？");
				Link.l1 = "「こんにちは」 "+GetFullName(NPChar)+"。あなたに話がしたかったんだ。";
			}
			Link.l1.go = "node_2";
		break;
		
		case "node_2":
			// Церковный генератор 1
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = "「素晴らしい。私はあなたのお役に立ちます」 "+GetFullName(PChar)+".";
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))	// Получаем полную инфу
				{
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = "それで、金の話はどうなってるんだ？俺にせめて千ペソぐらいはあるのか？";
						if(sti(PChar.Money) >= 1000)
						{
							link.l1 = "ああ、持っている"+GetSexPhrase("","")+"。ちょうど千ペソだ。さあ、情報を話せ！";
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = LinkRandPhrase("いいや、まだだ……","まだだ……","まだだが、すぐに持ってくるぜ……");
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = "どうか、問題の核心を説明させてください。私の古い友人である船長  "+PChar.GenQuest.ChurchQuest_1.CapFullName+"、ほんの数時間違いで行き違いになってしまったんだが、彼に至急の用事があるんだ。 これから追いかけなきゃならないが、どこにいるのか全く見当がつかない"+GetSexPhrase("","")+" 彼の行方についてだ。";
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else	// Полная инфа уже есть
				{
					link.l1 = "港湾長、旦那、俺は「という名の船について情報が必要だ"+PChar.GenQuest.ChurchQuest_1.CapShipName+"「」は船長の所有 "+PChar.GenQuest.ChurchQuest_1.CapFullName+".";
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NextColonyIsLast")) // Он здесь, в этой колонии!		
						link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_1";
					else // Отправляет в рандомную колонию
						link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_1";
				}				
				break;
			}		
//-------------------------------------------//Jason, фрахт---------------------------------------------------
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && CheckAttribute(PChar, "questTemp.WPU.Fraht.LevelUp") && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "「素晴らしい。お任せください。」 "+GetFullName(PChar)+".";
					Link.l1 = "あなたの植民地向けの貨物は俺の船の船倉にあるぜ。";
					Link.l1.go = "Fraht_completeLevelUp";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht != "lost" && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "「素晴らしい。ご用命とあらば、私が承ります」 "+GetFullName(PChar)+".";
					Link.l1 = "あなたの植民地向けの積み荷は俺の船の船倉にあるぜ。";
					Link.l1.go = "Fraht_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht == "lost" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					if (pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
					{
						dialog.text = "おお、ついに来たか。正直、もう戻ってこないと思っていたぞ。すでに当局にお前を指名手配するよう申請してある。 さて、何か言い分はあるか？";
						Link.l1 = "予期せぬ事情で積荷を期限内に届けられなかった。\nだが、この争いは平和的に解決したいんだ。\nちゃんと積荷は持ってきたぜ、どうか話し合いで折り合いをつけられるといいんだが。";
						Link.l1.go = "Fraht_complete_bad";
					}
					else
					{
						dialog.text = "ああ、お前が誰か知ってるぞ。貨物を運ぶ契約だったのに、盗みやがったな！衛兵、衛兵！";
						Link.l1 = "「アーッ！」";
						Link.l1.go = "exit";
						LAi_group_Attack(NPChar, Pchar);
					}
				}
// <-- фрахт
//-------------------------------------------//Jason, почта---------------------------------------------------	
		
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer != "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "「素晴らしい。私はあなたのお役に立ちます。」 "+GetFullName(PChar)+".";
					Link.l1 = "あなたの植民地に郵便を届けた。";
					Link.l1.go = "Postcureer_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer == "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "おお、やっと来たか。正直、もうお前は死んだものと思ってたぜ……まあ、ただの間抜けで死んでなかっただけマシか。";
					Link.l1 = "予期せぬ事情で郵便を時間通りに届けられませんでした。\nですが、これがその郵便です。";
					Link.l1.go = "Postcureer_complete_bad";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.fail") && pchar.questTemp.WPU.Postcureer.StartCity == npchar.city)
				{
					dialog.text = "どうしたんだ？死人みたいな顔してるじゃねえか。";
					Link.l1 = ""+GetAddress_FormToNPC(NPChar)+"、あんたが危険を警告してくれたのは正しかったぜ。港役所のすぐ外で黒服の男二人に襲われて……その、荷物を奪われちまったんだ。";
					Link.l1.go = "Postcureer_complete_fail";
					break;
				}
// <-- почта
//-------------------------------------------//Jason, эскорт---------------------------------------------------	
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "「素晴らしい。お任せください。」 "+GetFullName(PChar)+".";
					Link.l1 = "港湾長にここへ送られた "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"。武器と弾薬を積んだ船の護衛を頼まれたんだ。これが俺の書類だ。";
					Link.l1.go = "Escort_LUGo_0";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0") && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "「素晴らしい。お任せください。」 "+GetFullName(PChar)+".";
					Link.l1 = "約束通り、武器を積んだ船を護衛してきたぜ。";
					Link.l1.go = "Escort_LUGo_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "current" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "「素晴らしい。私はあなたのお役に立ちます。」 "+GetFullName(PChar)+".";
					Link.l1 = "行方不明だった船を見つけて、こちらの港まで連れてきました。船長はすでにあなたに報告しているはずです。";
					Link.l1.go = "Escort_LU1WM_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "「素晴らしい。お任せください。」 "+GetFullName(PChar)+".";
					Link.l1 = "行方不明だった船を見つけて、貴官の港まで連れてきた。船長はすでに貴官に報告しているはずだ。";
					Link.l1.go = "Escort_LU1VSP_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "sink" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "「素晴らしい。お任せください。」 "+GetFullName(PChar)+".";
					Link.l1 = "俺はその島の岸辺で行方不明だった船を見つけた "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+"。彼女の船長は圧倒的な海賊の軍勢と不利な戦いを繰り広げていた。俺もできる限り手を貸したが、 残念ながら無駄だった。あの忌々しい野郎どもが船を沈めやがったんだ。その時俺にできたのは、 せめて彼女の仇を討つことだけだった。";
					Link.l1.go = "Escort_LU1VSP_completeSink";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "「素晴らしい。お任せください。」 "+GetFullName(PChar)+".";
					Link.l1 = "俺はその島の岸辺で行方不明だった船を見つけたぜ "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+"。いや、実は船のことじゃなくて、その乗組員のうち五十人ほどと船長についてだ。彼らは今は無事だ――乗組員は俺の船に乗り込んでいるし、船長は今この町にいる――もうお前のところに挨拶に来たんじゃないか。";
					Link.l1.go = "Escort_LU1S_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "「素晴らしい。お任せください。」 "+GetFullName(PChar)+".";
					Link.l1 = "ご依頼は果たしました。交易船団を襲った海賊艦隊は壊滅させました。";
					Link.l1.go = "Escort_LU2_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus != "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "「素晴らしい。ご用命とあらば、私がお仕えいたします。」 "+GetFullName(PChar)+".";
					Link.l1 = "俺は護衛船の船長だ。商船を港まで無事に連れてきたことを報告しに来たぜ。";
					Link.l1.go = "Escort_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus == "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "「素晴らしい。お任せください。」 "+GetFullName(PChar)+".";
					Link.l1 = "俺は護衛船の船長だ。二隻の商船とその積み荷を港まで護送するよう命じられたが、 残念ながら敵の護送船団との戦闘で両方の商船が沈んじまった。だが、積み荷だけは何とか届けることができたぜ。";
					Link.l1.go = "Escort_fail";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id && !CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp"))
				{
					dialog.text = "「素晴らしい。お任せください。」 "+GetFullName(PChar)+".";
					Link.l1 = "俺は護衛船の船長だ。交易船を港まで無事に連れてきたことを報告しに来た。";
					Link.l1.go = "Escort_complete";
					break;
				}
// <-- эскорт
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice" && NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "そう言っていただけて嬉しいですな。あなたの立場なら、多くの者がうぬぼれてしまうでしょう。さて、 私と記録がどのようにお役に立てますかな？";
			}
			else dialog.text = "「素晴らしい。お任せください。」 "+GetFullName(PChar)+".";
			if (npchar.city != "Panama") // Captain Beltrop, 24.12.2020, запрет брать задания и ставить корабли в ПУ Панамы
			{
				Link.l2 = "俺が引き受けられる仕事はあるか？それとも契約でもあるのか？";
				Link.l2.go = "Work_check"; //квесты
				Link.l3 = "ここに俺の船の一隻をしばらく係留してもいいか？";
				Link.l3.go = "ShipStock_1";
			}
			if (sti(NPChar.Portman) > 0)
			{
                Link.l4 = "俺の船を取り戻したいんだ。";
    			Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "財政の件で話をしに来た。";
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)	
			}
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("私はある男の依頼でここに来た。その名は総督だ "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" 俺をあんたのところに寄越したんだ。何か受け取ることになっててな……");
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = "あなたの港湾当局に登録している船長たちについて、もっと詳しく知りたいのだが。";
			link.l6.go = "CapitainList";
			link.l61 = "特別仕様の船やその伝説的な船長たちについて、何か知っていることを教えてもらえないか？";
			link.l61.go = "UniqueShips";
			
			link.l8 = "私は別の案件を処理している。";
			// Warship 26.07.09 Генер "Сгоревшее судно"
			if(CheckAttribute(NPChar, "Quest.BurntShip") && !CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate"))
			{
				if(CheckAttribute(NPChar, "Quest.BurntShip.TimeIsOver")) // Просрочено
				{
					link.l8.go = "BurntShip10";
				}
				else
				{
					if(CheckAttribute(NPChar, "Quest.BurntShip.TwoDaysWait"))
					{
						if(GetNpcQuestPastDayParam(NPChar, "Quest.BurntShip.TwoDaysWait") >= 2)
						{
							link.l8.go = "BurntShip17";
						}
						else
						{
							link.l8.go = "quests";
						}
					}
					else
					{
						link.l8.go = "BurntShip12";
					}
				}
			}
			else
			{
				link.l8.go = "quests";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "portman_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "こんにちは、あなたの息子さんの招待で参りました。"; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "これはあなたの娘のことだが…";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if(pchar.questTemp.different == "free")
				{
					link.l10 = "たまたまこの船の書類の包みを見つけたんだ。";
					link.l10.go = "ShipLetters_out1";				
				}
				else
				{
					if(pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = "たまたまこの船の書類の包みを見つけたんだ、誰かが落としたに違いねえ。";
						if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakPortman"))
						{
							link.l10.go = "ShipLetters_Portman1_1";						
						}
						else
						{
							link.l10.go = "ShipLetters_Portman2";
						}
					}
				}		
			}												
			Link.l15 = "ありがとうございます。さようなら。";
			Link.l15.go = "exit";
		break;

		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = "お前の問題は簡単に解決できるぜ。航海局の役人に会いに行けば、友人の船の航路についてすべて教えてくれるはずだ。";
			link.l1 = "残念ながら、そう簡単にはいかないんだ。俺の友人はお前さんの港で船の名前を変えたんだ……宗教的な理由でな。";
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = "なるほど。それは少し話をややこしくするな。船籍簿の記録を調べなきゃならねえし、時間がかかるぜ。しかも、 時間は金だってことは分かってるだろう。";
			if(sti(pchar.money) >= 1000)
			{
				link.l1 = "そのことは十分に理解しております、旦那 "+GetFullName(NPChar)+"……そして、君の時間を評価する準備は十分できている……例えば千ペソという額でどうだろう。";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // Можно будет спросить.
				link.l1 = "それは残念だが、今は手元に金がねえ……また後で来るぜ……";
				link.l1.go = "exit";
			}
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if(CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = "完璧だ！さてと……ちょっと待ってくれ……ここだ……よし。船の改名は登録された、そしてこれからこの船は『"+PChar.GenQuest.ChurchQuest_1.CapShipName+"「」+Captain+"船長の指揮下" "+PChar.GenQuest.ChurchQuest_1.CapFullName+" 本日、出航して向かった "+XI_ConvertString("Colony"+sColony+"Gen")+".";
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = "おお！君は私がとても忙しい男だと本当に理解してくれているんだな、それを分かってくれて嬉しいよ！さてと……ちょっと待ってくれ……ここだ……よし。船の改名は登録された、そしてこの船は今後『"+PChar.GenQuest.ChurchQuest_1.CapShipName+"『』"+GetFullName(sld)+"船長が指揮する "+PChar.GenQuest.ChurchQuest_1.CapFullName+" 本日出航し、～へ向かった "+XI_ConvertString("Colony"+sColony+"Gen")+".";			
				link.l1 = "ありがとうございます、旦那、あなたは私に大きな恩を売ってくれました。";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_4";
				AddMoneyToCharacter(pchar, -1000);
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Gen"));
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);	
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true;
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_1":
			dialog.text = "具体的に何を知りたいんだ？";
			link.l1 = "その船長が所有する船があなたの港に寄港したかどうか、教えてもらえるか？";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;
						
		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = "ふむ……それを聞く理由を伺ってもよろしいですか？";
			link.l1 = "俺はあいつに用があるんだ。だが、もしあんたの港に寄っていないとか、あんたが知らねえなら……";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = "ああ、そうだ。しかし聖人たちに感謝しよう、今朝になってやっと奴はここからいなくなり、どこかへ向かったんだ\n "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapGoToColony+"Acc")+"。そいつと関わらなきゃならねえ奴には心から同情するぜ。";
			link.l1 = "その場合は、俺に幸運を祈ってくれ――そして助けてくれてありがとう。";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_4";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "5");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Voc")); // belamour gen
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony; // Спрашиваем портмана в колонии, куда отправился кэп.
			if(rand(2) == 1) 
			{
				Log_TestInfo("The next colony is the last");
				PChar.GenQuest.ChurchQuest_1.NextColonyIsLast = true; // Флаг - следующая колония будет последней
			}
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_1":
			dialog.text = "何を知りたいんだ、 "+GetSexPhrase("旦那","お嬢さん")+" "+GetFullName(PChar)+"?";
			link.l1 = "この船長があなたの港に寄港したかどうか、教えてもらえますか？";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = "ふむ、確かにそうだな。それに、あの男がようやくこの苦労続きの港を去る、 その祝福された瞬間を心待ちにしているのだよ。";
			link.l1 = "「つまり、奴の船はまだここにあるってことか？」";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = "はい、ありがたく "+GetSexPhrase("旦那","ご婦人")+"。港中の者――一番下っ端の荷役から水先案内人の長まで――みんながあいつの早い出発を祈っているんだ。奴の船はついさっきドックから出たばかりで、すぐに修理されたが、 その間にあの勇ましい船長は大工全員と喧嘩し、船体用に選ばれた板を三度も突き返したんだ。だが明日には、 我らが慈悲深くすべてを見通す主が、あの……あの疫病神、皆の目の上のたんこぶを取り除いてくださるだろう！";
			link.l1 = "さあ、落ち着いてくれ、旦那 "+NPChar.Name+"、そして誰かがもっと苦労することになるだろうな。お前はもうこの試練を乗り越えたが、 俺はまだお前の船長に会っていないんだ。では、失礼する……";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_4";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "6");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
//			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithSailors = true; // Спрашиваем моряков
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithCap = true; // Говорим с капитаном
//			SetFunctionLocationCondition("Church_GenQuest1_ChangeCapitanLocation", "Deck_Near_Ship", true);
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = NPChar.city;
			Group_SetAddress("ChurchGenQuest1_CapGroup", colonies[FindColony(NPChar.City)].Island, "IslandShips1", "Ship_1"); // Ставим кэпа в порту колонии
			Characters[GetCharacterIndex("ChurchGenQuest1_Cap")].Nation = sti(NPChar.Nation); // Сменим нацию, чтоб вражды не было
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan"); // Больше не спрашиваем
//			if(rand(1) == 0) PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
			sld = CharacterFromID("ChurchGenQuest1_Cap");
			sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		break;
						
		case "ShipLetters_out1":
			dialog.text = "見せてくれ！うむ、確かに俺の書類ではこの一式は無効と記されている。わざわざ時間を作って俺に会いに来て、 これらの書類を渡してくれるとは親切だな。\n風下に気をつけろよ、船長！";
			link.l1 = "ありがとう！";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "CaptainBook"); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "10");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
				
		case "ShipLetters_Portman1_1":
			pchar.questTemp.different.GiveShipLetters.speakPortman = true;
			s1 = "Let me take a look! Yes, this vessel and its captain are both registered in my documents. ";
			s1 = s1 + "Your conscientiousness, captain, reflects credit upon yourself! Of course, your efforts must not go unrewarded.  ";
			dialog.text = s1+"「なあ、いくらかの金を考えてみないか "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" ペソだが、それで報酬として十分か？";
			link.l1 = "もちろん違う！";
			link.l1.go = "exit";
			link.l2 = "まあ、控えめな額だが、大したことでもなかったしな。よし、その申し出、受けるぜ。 "+npchar.name+".";
			link.l2.go = "ShipLetters_Portman1_2";
		break;
		
		case "ShipLetters_Portman1_2" :
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "5");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "ShipLetters_Portman2":
			dialog.text = "俺の提案を受けてくれるか？";
			link.l1 = "もちろん違う！";
			link.l1.go = "exit";
			link.l2 = "たぶんね。ただ、この書類はもっと価値があるはずだ。";
			link.l2.go = "ShipLetters_Portman2_1";
		break;
		
		case "ShipLetters_Portman2_1":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "6");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 		
		break;

		case "EncGirl_1":
			dialog.text = "耳を傾けているぞ。";
			link.l1 = "逃亡者を連れてきたぜ。";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "ああ、船長、本当にありがとうございます！彼女はどうですか？怪我はしていませんか？なぜ逃げたんです？ なぜなんです？\n彼女には分からないのでしょうか？花婿は裕福で重要な人物なのですよ！若さとは無知で愚か……時には残酷です。覚えておきなさい！";
			link.l1 = "まあ、あなたは彼女の父親で最終的な決定はあなたのものですが、結婚を急ぐのはおすすめしません…";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "何が分かるってんだ？自分の子供はいるのか？いねえのか？自分の子ができたら、俺のところに来いよ。 その時に話をしようじゃねえか。\n彼女を家族の元に連れ戻した者には報酬を約束したんだ。";
			link.l1 = "ありがとう。あの女には気をつけたほうがいいぜ。俺の勘だが、あれで終わるような奴じゃねえ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "「ああ、お前があの」 "+GetSexPhrase("連れてきた船長","連れてきた若い娘")+" 「放蕩息子が若い花嫁を連れてきたのか？」";
				link.l1 = "ああ、俺が奴らの逃亡を手助けしたんだ。";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "おやおや、ご恩人。報酬を待っているのかい？";
				link.l1 = "「まあ、報酬なんていらねえよ、あんたの感謝だけで十分だぜ。」";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "あなたが私の子供を絶体絶命の状況で見捨てず、あの繊細な問題から抜け出す手助けをしてくださったこと、 心より感謝いたします。どうか私の感謝の気持ちを受け取ってください。そして、ささやかではございますが、 この金額と私からの個人的な贈り物をお納めください。";
			link.l1 = "ありがとうございます。この若い二人を助けることができて光栄でした。";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "感謝だと？何が感謝だ！？あの間抜けが無職でぶらぶらしてからもう半年だぞ――それなのに、恋愛にうつつを抜かす暇はあるらしい！俺があいつの年の頃には、 もう自分の商売を切り盛りしてたってのに！ふん！総督には嫁入り前の娘がいるってのに、 あの馬鹿は身寄りもない女をうちに連れてきて、俺に祝福を頼むとは厚かましいにも程がある！";
			link.l1 = "ふむ……どうやら本当の気持ちってものを信じてないんだな？";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "何の感情だ？どんな感情のことを言っている？感情…お前の年でそんなに軽率になれるとはな！？若い者の気まぐれに付き合い、世話役のように振る舞うとは恥を知れ！ お前は娘を家から連れ出しただけでなく、わしの未熟者の人生まで台無しにしたのじゃ。感謝などせんぞ。さらばだ。";
			link.l1 = "ああ、そっちも同じくだぜ……";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		case "node_4":
			//--> дача миниквестов начальника порта. 
			if (rand(2) < 2 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "quest.meeting") > 7)
			{
				dialog.text = LinkRandPhrase("ああ、くそったれ！お前に頼みたい仕事があるんだ！","ははっ！ちょうどいいところに来たな！俺には解決してほしい用件があるんだ。","もちろんだとも！もちろん君に頼みたい仕事がある！最近は問題だらけで手が回らんのだよ……");
				link.l1 = "「それでは、要件をお聞かせください。」 "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}
			
			// Warship 25.07.09 Генер "Сгоревшее судно"
			if(hrand(4) == 2 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			{
				dialog.text = "「なんてこった！船長」 "+GetFullName(PChar)+"「ちょうどいいところに来てくれた！なんという不運、なんという災難だ……港湾当局の管理下で船が停泊中に焼け落ちてしまったんだ！警備の不注意で船が……船が水面まで焼け落ちてしまった……\n」"+"旦那様、私は何をしたというのだ？こんな罰を受ける覚えはありません……長年、忠実な召使いとして仕えてきたというのに……";
				link.l1 = "それで、何が大ごとなんだ？船が燃えちまったのか？だったら保険契約は何のためにあるんだよ？それとも、 金をケチって保険に入らなかったのか？今さら後悔しても遅いぜ。";
				link.l1.go = "BurntShip4";
				link.l2 = "この件については、造船所の方が私よりもよく助けてくれるでしょう。数か月もすれば、古いものを修復するか、 新しいものを建造してくれるはずです。申し訳ないが、私は船大工ではありません……";
				link.l2.go = "BurntShip2";
				break;
			}
			//<-- дача миниквестов начальника порта.

			dialog.text = "総督は市民の福祉を大切にしているから、いつも何かしらの仕事を用意しているんだ。\n酒場には助けを求めている商人がいるかもしれないし、店でも輸送を任せられる船長を必要としているぞ。";
			Link.l1 = "もう一つ質問がある。";
			Link.l1.go = "node_2";
			Link.l2 = "ありがとうございます。さようなら。";
			Link.l2.go = "exit";
		break;

///Jason-----------------------новые генераторы накопительного типа для портмана----------------------------
		int iTime, idaysQty, iGoods, iGoodsQty, amount;
		case "Work_check"://фейс-контроль - общая проверка профпригодности ГГ и выбор задания
			//--> проверка миниквестов начальника порта. 
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = "お前はその船長を見つけるはずだった "+npchar.quest.PortmansJornal.capName+" そして彼の航海日誌を返してやってくれ。うまくいったか？";
				link.l1 = "いや、まだだ……";
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //взят квест на поиски украденного корабля
			{
				dialog.text = "「盗まれたものを探し出すと自ら誓った」 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName))+" 「」"+npchar.quest.PortmansSeekShip.shipName+"「。その任務を終えるまでは、他の仕事は与えないぞ。」";
				link.l1 = "俺は捜索を続けるぜ、ちょっと待ってろ。";
				link.l1.go = "exit";
				link.l2 = "任務を放棄したい。";
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //украденный корабль взят на абордаж
			{
				dialog.text = "「盗まれたものを探し出すと約束してくれたじゃないか」 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName))+" 「」"+npchar.quest.PortmansSeekShip.shipName+"「。やったのか？」";
				bool bOk = false;
				for (i=0; i<=COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(pchar, i);
					if(cn != -1)
					{
						sld = &characters[cn];
						if (sld.ship.name == npchar.quest.PortmansSeekShip.shipName && 
							RealShips[sti(sld.ship.type)].BaseName == npchar.quest.PortmansSeekShip.shipTapeName &&
							RealShips[sti(sld.Ship.Type)].basetype == npchar.quest.PortmansSeekShip.shipTape)
						{
							if (i == 0)
							{	//если нужный корабль - у ГГ
								sld.Ship.Type = GenerateShip(SHIP_TARTANE, true);
								SetBaseShipData(sld);
								SetCrewQuantityFull(sld);
							}
							else
							{
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
							}
							bOk = true;
						}
					}
				}				
				if (bOk)
				{
					link.l1 = "ああ、見つけたぜ、今は港にある。持っていっていいぞ。";
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = "俺が引き続き捜索するから、待っていろ。";
					link.l1.go = "exit";
				}
				link.l2 = "任務を放棄したい。";
				link.l2.go = "SeekShip_break";
				break;
			}
			//<-- проверка миниквестов начальника порта. 
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2)//проверка повтора
				{
					if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
					{
						dialog.text = RandPhraseSimple("の旗の下で航海する者には仕事はない "+NationNameGenitive(sti(pchar.nation))+"「俺の執務室から今すぐ出ていけ！」","俺は協力しねえ "+NationNameAblative(sti(pchar.nation))+"。失せろ！");
						link.l1 = RandPhraseSimple("まあ、好きにしな…","まあ、好きにしな…");
						link.l1.go = "exit";
						break;
					}
					if (isBadReputation(pchar,40)) // проверка репутации ГГ с вызывающим доверие belamour legendary edition
					{
						dialog.text = "お前の評判じゃ俺は信用できねえ。協力する気はない。さらばだ。";
						link.l1 = "なんだと！全部嘘じゃねえか。";
						link.l1.go = "exit";
						break;
					}
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
					{
						dialog.text = "侮辱するつもりはないんだ、船長。でも……君には私の依頼をこなすのは無理だと思う。経験が足りないんだ。契約は結べない。";
						link.l1 = "なるほど。まあ、あなたの言う通りだ。";
						link.l1.go = "exit";
						break;
					}
					dialog.Text = "ふむ……まあ、それはお前がどんな仕事に興味があるかによるな。";
					link.l1 = "俺の船を貨物輸送のためにチャーターしてもいいぜ。";
					Link.l1.go = "Fraht_begin";		//фрахты
					link.l2 = "商人の護衛で余分に稼ぎたいんだ。";
					Link.l2.go = "escort_begin";	//эскорт
					link.l3 = "郵便を配達して、余分に稼ぎたいんだ。";
					Link.l3.go = "cureer_begin";	//доставка почты
					Link.l4 = "そうだな、何か提案してくれるか？";
					Link.l4.go = "node_4"; 			//судовой журнан, угнанное судно, сгоревшее судно
				}
				else
				{
					dialog.Text = "今日はもう何も残っていない。別の日にまた来い。";
					link.l1 = "「よし。」";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "港にお前の船が見当たらねえな。沖に停めてからもう一度来い――そしたら何か仕事を探してやるぜ。";
				link.l1 = "よし、そうするぜ。";
				link.l1.go = "exit";
			}
		break;
			
		case "escort_begin"://эскорт
		SaveCurrentNpcQuestDateParam(npchar, "work_date"); // mitrokosta безусловно сохраняем
		
		if (hrand(5) > 1)
		{
			if (GetCompanionQuantity(pchar) < 3 && or(sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_WAR, sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_RAIDER)) 
			{
				if (pchar.questTemp.WPU.Escort == "begin" || pchar.questTemp.WPU.Escort == "late" || pchar.questTemp.WPU.Escort == "win" || CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp")) 
				{ // если заняты
					dialog.text = "残念ながら、その手の依頼は今は用意できないんだ。二、三日後にまた来てくれ。";
					link.l1 = "よし、そうするぜ。";
					link.l1.go = "exit";
				} 
				else 
				{ // если не заняты
					if (sti(pchar.questTemp.WPU.Escort.count) > 3 && hrand(1) == 1) 
					{ // 2 уровень
						dialog.text = "あなたはすでに何度も商船の護衛を見事に果たしてくれたな。\n君にふさわしい任務があると思う。";
						link.l1 = "聞く耳は持ってるぜ。";
						link.l1.go = "Escort_LevelUp";
					} 
					else 
					{ // 1 уровень
						if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_GALEON_H && 2500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) < 0 && !CheckAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID")) { // если на ТГ
							dialog.text = "お前にぴったりの仕事があるぜ。港に商船が二隻いるんだが、本来ならもう出航しているはずだったんだ。だが、 護衛船が損傷して修理待ちでな、しばらく出港できそうにないんだよ。\nそこでお前の船がうってつけってわけだ――それに、追加の積み荷もお前の船倉に積みたいんだ。当然、報酬は倍払うぜ――運送分と護衛分、両方な。";
							link.l1 = "なんて面白い提案だ！乗ったぜ！";
							link.l1.go = "escort_bonus";
							link.l2 = "ありがとうございますが、そういう仕事は俺の性に合わねえんだ。";
							link.l2.go = "exit";
						} 
						else 
						{ // просто эскорт
							dialog.text = "ちょうどお前に頼みたい仕事がある。今、二隻の商船が我々の港に停泊している――護衛が必要だ。これらの船を目的地まで護衛する機会をお前にやろう。やってくれるか？";
							link.l1 = "面白い提案だな！乗ったぜ！";
							link.l1.go = "escort";
							link.l2 = "ありがとうございますが、そういう仕事は俺の性に合わねえんだ。";
							link.l2.go = "exit";
						}
					}
				}
			}
			else
			{
				//не тот тип корабля
				dialog.text = "護衛任務にタルターヌで来るようなもんだぜ。こういう仕事には、ちゃんとした火力を持つ軍船か襲撃船が必要なんだ。";
				link.l1 = "わかったよ。";
				link.l1.go = "exit";
			}
		}
		else
		{
			//нет работы
			dialog.text = "残念ながら、そのような依頼は今は用意できない。\n数日後にまた来てくれ。";
			link.l1 = "よし、そうするぜ。";
			link.l1.go = "exit";
		}
		break;
		
		case "cureer_begin"://доставка почты
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
		
		if (hrand(5) > 1)
		{
			if (sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_RAIDER)
			{
				if (pchar.questTemp.WPU.Postcureer == "begin" || pchar.questTemp.WPU.Postcureer == "late" || pchar.questTemp.WPU.Postcureer == "lost" || pchar.questTemp.WPU.Postcureer == "fail" || CheckAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp"))
				{ 
					// если заняты
					dialog.text = "残念だが、その手の依頼は今は用意できねえ。また二、三日したら来てくれ。";
					link.l1 = "よし、そうするぜ。";
					link.l1.go = "exit";
				} 
				else 
				{ 
					// если не заняты
					if (sti(pchar.questTemp.WPU.Postcureer.count) > 3 && hrand(1) == 1) 
					{ //если 2 уровень
						dialog.text = "そうか……お前はすでに何度か運び屋の仕事を引き受けて、俺の知る限りではかなりうまくやってきたようだな。 これから任せる仕事も、お前ならきっとやれるだろう。";
						link.l1 = "「さあ、聞かせてくれ」 "+GetAddress_FormToNPC(NPChar)+".";
						link.l1.go = "Postcureer_LevelUp";
					} 
					else 
					{ // первый уровень
						dialog.text = "速い船を持っているようだな。急ぎの仕事を頼みたい――郵便や商業書類の配達だ。";
						link.l1 = "これは面白いな。俺も同意だ。どこへ行けばいいんだ？";
						link.l1.go = "Postcureer";
						link.l2 = "ありがとうよ、だがそれは俺の性に合わねえ仕事だぜ。";
						link.l2.go = "exit";
					}
				}
			}
			else
			{
				//не тот тип корабля
				dialog.text = "申し訳ないが、君に頼める仕事はないんだ。こういう任務には素早い襲撃船が必要だ。君の船なら、 貨物運搬の方が向いているぞ。";
				link.l1 = "わかったよ。";
				link.l1.go = "exit";
			}
		}
		else
		{
			//нет работы
			dialog.text = "残念だが、その手の依頼は今は用意できねえ。二、三日したらまた来てくれ。";
			link.l1 = "よし、そうするぜ。";
			link.l1.go = "exit";
		}
		break;

///--> ------фрахт со свободным выбором пункта назначения, оплаты и вида груза из предложенного списка---------

		case "Fraht_begin":
			if (hrand(4) < 4)
			{
				if (pchar.questTemp.WPU.Fraht == "begin" || pchar.questTemp.WPU.Fraht == "late" || pchar.questTemp.WPU.Fraht == "lost" || CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))//проверка на занятость
				{
					dialog.Text = "しかし、あなたの船はすでに傭船契約を結んでいると聞いております。これ以上の貨物はお渡しできません。 すでに引き受けた責務を果たしてください。";
					link.l1 = "ああ、たぶんお前の言う通りだな。";
					Link.l1.go = "exit";
					break;
				}
				if (1500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) > 0)//мало места - не даем
				{
					dialog.text = "お前の船倉は狭すぎるな。貨物を運ぶにはもっと大きな船が必要だぜ。\n店で確認してみるといい――地元の商人はよく小口の貨物を運ぶ船をチャーターしてるからな。";
					link.l1 = "なるほど。まあ、あなたの言う通りだ。";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.WPU.Fraht.count > 3 && rand(1) == 0)
				{
					dialog.text = "今のところ君に合う仕事はない。しかし、君はすでに何度も荷物を無事に届けてくれたな。 君にぜひ任せたい特別な仕事があるんだ。";
					link.l1 = "聞こう。どんな仕事だ？";
					link.l1.go = "Fraht_LevelUp";
					break;
				}
				dialog.Text = "さて、いくつかの傭船の機会を提案できるぜ。";
				link.l1 = "さて、どうするかな……";
				Link.l1.go = "Fraht_choise";
			}
			else
			{
				dialog.Text = "本日の運送依頼はもう残っていない。別の日にまた来てくれ。";
				link.l1 = "まあ、仕方ねえな。";
				Link.l1.go = "exit";
			}
		break;
	
		int iFrahtGoods1, iFrahtGoods2, iFrahtGoods3, iFrahtGoods;
		int iFrahtGoodsQty1, iFrahtGoodsQty2, iFrahtGoodsQty3;
		case "Fraht_choise":
			//выбираем города
			pchar.questTemp.WPU.Fraht.City1 = findCurrentCity1(npchar);
			pchar.questTemp.WPU.Fraht.City2 = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Fraht.City3 = findCurrentCity3(npchar);
			//выбираем товары
			iFrahtGoods1 = hrand(GOOD_PAPRIKA);
			iFrahtGoods2 = hrand(GOOD_PAPRIKA-3);
			iFrahtGoods3 = hrand(GOOD_PAPRIKA-7);
			pchar.questTemp.WPU.Fraht.Goods1 = iFrahtGoods1;
			pchar.questTemp.WPU.Fraht.Goods2 = iFrahtGoods2;
			pchar.questTemp.WPU.Fraht.Goods3 = iFrahtGoods3;
			//определим количество
			iFrahtGoodsQty1 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods1))/(1+frand(0.5));
			iFrahtGoodsQty2 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods2))/(1+frand(0.5));
			iFrahtGoodsQty3 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods3))/(1+frand(0.5));
			if (sti(iFrahtGoodsQty1) > 10000) iFrahtGoodsQty1 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty2) > 10000) iFrahtGoodsQty2 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty3) > 10000) iFrahtGoodsQty3 = 10000 + rand(500);
			pchar.questTemp.WPU.Fraht.GoodsQty1 = iFrahtGoodsQty1;
			pchar.questTemp.WPU.Fraht.GoodsQty2 = iFrahtGoodsQty2;
			pchar.questTemp.WPU.Fraht.GoodsQty3 = iFrahtGoodsQty3;
			pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Fraht.Chance = rand(4);//форс-мажор
			//определим сроки с учётом рандома
			int daysQty1 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City1));
			int daysQty2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City2));
			int daysQty3 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City3));
			pchar.questTemp.WPU.Fraht.DaysQty1 = makeint(sti(daysQty1)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty2 = makeint(sti(daysQty2)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty3 = makeint(sti(daysQty3)*(frand(1.3)+0.7));
			//установим цену исходя из объёма груза, дальности и сроков
			pchar.questTemp.WPU.Fraht.Money1 = (makeint((sti(iFrahtGoodsQty1) * sti(Goods[iFrahtGoods1].Weight) / sti(Goods[iFrahtGoods1].Units))))*(sti(daysQty1)*2)*sti(daysQty1)/sti(pchar.questTemp.WPU.Fraht.DaysQty1);
			pchar.questTemp.WPU.Fraht.Money2 = (makeint((sti(iFrahtGoodsQty2) * sti(Goods[iFrahtGoods2].Weight) / sti(Goods[iFrahtGoods2].Units))))*(sti(daysQty2)*2)*sti(daysQty2)/sti(pchar.questTemp.WPU.Fraht.DaysQty2);
			pchar.questTemp.WPU.Fraht.Money3 = (makeint((sti(iFrahtGoodsQty3) * sti(Goods[iFrahtGoods3].Weight) / sti(Goods[iFrahtGoods3].Units))))*(sti(daysQty3)*2)*sti(daysQty3)/sti(pchar.questTemp.WPU.Fraht.DaysQty3);
			if (hrand(5) < 4)//три варианта
			{
				dialog.text = "以下の選択肢があります:\n"+"積み荷 "+GetGoodsNameAlt(iFrahtGoods1)+" の額で "+FindRussianQtyString(iFrahtGoodsQty1)+" の町へ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+"、で "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1)+"。支払い－ "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1))+"\n積荷 "+GetGoodsNameAlt(iFrahtGoods2)+" 「～の額で」 "+FindRussianQtyString(iFrahtGoodsQty2)+" の町へ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+"、の "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2)+"。支払い－ "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2))+"\n積荷 "+GetGoodsNameAlt(iFrahtGoods3)+" の額で "+FindRussianQtyString(iFrahtGoodsQty3)+" の町へ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3)+"、で "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty3)+"。支払い－ "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3))+"\nどうなさいますか？";
				Link.l1 = "俺は二番目の選択肢――その町へのチャーターを選ぶぜ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+" 積み込まれた "+GetGoodsNameAlt(iFrahtGoods1)+".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "俺は三つ目の選択肢――町への通行証を選ぶぜ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+" 「～を積んだ」 "+GetGoodsNameAlt(iFrahtGoods2)+".";
				Link.l2.go = "Fraht_Choise_2";
				Link.l3 = "俺は三番目の選択肢――この町への通行証を選ぶぜ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3)+" 「～を積んだ」 "+GetGoodsNameAlt(iFrahtGoods3)+".";
				Link.l3.go = "Fraht_Choise_3";
			}
			else //два варианта
			{
				dialog.text = "以下の選択肢があります:\n"+"積荷 "+GetGoodsNameAlt(iFrahtGoods1)+" 「～の額で」 "+FindRussianQtyString(iFrahtGoodsQty1)+" の町へ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+"、で "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1)+"。支払い－ "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1))+"\n積荷 "+GetGoodsNameAlt(iFrahtGoods2)+" 「～の額で」 "+FindRussianQtyString(iFrahtGoodsQty2)+" の町へ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+"、で "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2)+"。支払い－ "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2))+"\nお前の選択はどうする？";
				Link.l1 = "俺は最初の選択肢――その町への許可証を選ぶぜ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+" 積み荷がいっぱいの "+GetGoodsNameAlt(iFrahtGoods1)+".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "俺は二つ目の選択肢――その町への許可証を選ぶぜ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+" 積み荷がいっぱいの "+GetGoodsNameAlt(iFrahtGoods2)+".";
				Link.l2.go = "Fraht_Choise_2";
			}
			Link.l4 = "残念ながら、俺に合う仕事はないな。";
			Link.l4.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
		break;
	
		case "Fraht_Choise_1":
			dialog.text = "よし、素晴らしい！俺が必要な書類を処理するから、お前は積み込みの準備をしてくれ。";
			link.l1 = "全力を尽くすぜ！";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods1), sti(pchar.questTemp.WPU.Fraht.GoodsQty1));
			iFrahtGoods1 = pchar.questTemp.WPU.Fraht.Goods1;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods1));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty1)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty1)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty1), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City1+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods1].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods1].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty1);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods1);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty1);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money1);
		break;
	
		case "Fraht_Choise_2":
			dialog.text = "よし、素晴らしい！俺が必要な書類を手続きするから、お前は船の積み込み準備をしてくれ。";
			link.l1 = "全力を尽くすぜ！";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods2), sti(pchar.questTemp.WPU.Fraht.GoodsQty2));
			iFrahtGoods2 = pchar.questTemp.WPU.Fraht.Goods2;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods2));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty2)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty2)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty2), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City2+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods2].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods2].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty2);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods2);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty2);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money2);
		break;
	
		case "Fraht_Choise_3":
			dialog.text = "よし、素晴らしい！俺が必要な書類を手続きするから、お前は積み込みの準備をしてくれ。";
			link.l1 = "全力を尽くします！";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods3), sti(pchar.questTemp.WPU.Fraht.GoodsQty3));
			iFrahtGoods3 = pchar.questTemp.WPU.Fraht.Goods3;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods3));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty3)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty3)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty3), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City3+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods3].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods3].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty3);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods3);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty3);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money3);
		break;
	
		case "Fraht_Forcemajor":
			pchar.questTemp.WPU.Fraht = "begin";
			sld = characterFromId(pchar.questTemp.WPU.Fraht.TargetPortmanID);
			pchar.questTemp.WPU.Fraht.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Fraht.TargetCity = FindTownOnIsland(pchar.questTemp.WPU.Current.TargetIslandID);
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Fraht.Chance > 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Fraht.Chance == 2) FrahtHunterOnSea();//создание ДУ в акватории
			DialogExit();
		break;
	
		case "Fraht_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			iFrahtGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
			amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
			if (amount > 0)
			{
				dialog.text = "さて、見せてもらおうか。お前は本来、荷物を届けるはずだった "+GetGoodsNameAlt(iFrahtGoods)+" 「～の額で」 "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+"。しかし見たところ、全ての積荷を届けてはいないようだな――お前は "+FindRussianQtyString(sti(amount))+" 短い。";
				link.l1 = "「千匹のサメだと！きっとあの忌々しいネズミどもに違いねえ！だが心配すんな、」 "+GetAddress_FormToNPC(NPChar)+"、足りない分は俺が買い取って、全部まとめて納品するぜ。";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "さて、見せてもらおうか。お前は本来、積み荷を届けるはずだった "+GetGoodsNameAlt(iFrahtGoods)+" の額で "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+"。正しいか？";
			link.l1 = "「まったくその通りだ」 "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "Fraht_complete_1";
		}
		else
		{
			dialog.text = "港にお前の船が見当たらねえな。錨を下ろしてからもう一度来い――そしたら話をしよう。";
			link.l1 = "よし、それをやるぜ。";
			link.l1.go = "exit";
		}
		break;
	
		case "Fraht_complete_1":
			if (pchar.questTemp.WPU.Fraht == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Fraht.Late"))+1;
				pchar.questTemp.WPU.Fraht.DayLate = iTime;
				pchar.questTemp.WPU.Fraht.PercentLate = iTime/0.2;
				pchar.questTemp.WPU.Fraht.Money = makeint(sti(pchar.questTemp.WPU.Fraht.Money) - sti(pchar.questTemp.WPU.Fraht.Money)*sti(pchar.questTemp.WPU.Fraht.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "ふむ……だが、お前は "+FindRussianDaysString(iTime)+" 遅れましたね。したがって、貨物運送の報酬を減額せねばなりません。契約によれば、 遅延一日ごとに総額の五パーセントが罰金となります。では、どうぞ、お受け取りください\n "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+"、そして今後は契約を守るようにしてくれ。";
				link.l1 = "まあ、少なくとも何かはあるな。";
				link.l1.go = "Fraht_complete_2";
				break;
			}
			dialog.text = "お勤めご苦労だった。さあ、報酬を受け取ってくれ― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "ありがとう！";
			link.l1.go = "Fraht_complete_2";
		break;
	
		case "Fraht_complete_2":
			if (pchar.questTemp.WPU.Fraht == "begin")
			{
				pchar.quest.FrahtTime_Over.over = "yes";
				AddQuestRecord("Fraht", "2");
			}
			else
			{
				pchar.quest.FrahtTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Fraht", "4");
				AddQuestUserData("Fraht", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Fraht.DayLate));
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
			}
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
			CloseQuestHeader("Fraht");
			DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "Fraht_complete_bad":
			dialog.text = "積荷は届けたか？ふん、いいだろう。実のところ、俺たちが自腹で買い取って受取人に渡す羽目になったんだぜ！しかも、 かなり高くついたんだ、わかってるか。だからな、もしお前が信用を取り戻したいなら、 俺たちの出費分に加えて違約金も払ってもらうぜ。積荷についてはもういらねえから、お前が持ってていい。\n";
			link.l1 = "はい、もちろん。いくらだ？";
			link.l1.go = "Fraht_complete_bad_1";
		break;
	
		case "Fraht_complete_bad_1":
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)*3;
			dialog.text = "商品の三倍の値段だ。つまり "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+".";
			if (sti(Pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
			{
				link.l1 = "なかなかの額だな。しかし、商売は商売だ。よし、金を渡すぜ。";
				link.l1.go = "Fraht_complete_pay";
			}
			link.l2 = "気は確かか？そんな法外な金額を要求するなんて、強欲にもほどがある！俺からはびた一文も出さねえぞ！";
			link.l2.go = "Fraht_complete_fail";
		break;
	
		case "Fraht_complete_pay":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			dialog.text = "賢明な判断だ。これでお前が本当に真面目な奴だと分かったぜ。今後もまだ一緒に仕事ができそうだな。";
			link.l1 = "ありがとうございます、しかし、そろそろ失礼します。";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 12);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 30);
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "8");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "6");
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Fraht");
				pchar.questTemp.WPU.Fraht = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 70);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
		break;
	
		case "Fraht_complete_fail":
			dialog.text = "ああ、そうか……それなら、二度とどこの港の役所にも顔を出すんじゃねえぞ "+NationNameGenitive(sti(pchar.questTemp.WPU.Fraht.Nation))+"「消え失せろ！」";
			link.l1 = "「大して見逃してねえだろう…」";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "9");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "7");
				CloseQuestHeader("Fraht");
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
		break;
	
		case "Fraht_complete_3":
			dialog.text = "急げ、受取人はすでにお前の船が到着したことを知っていて、自分の貨物のことを心配しているぞ。";
			link.l1 = "その場合、これ以上時間を無駄にはしません！";
			link.l1.go = "exit";
		break;
	//фрахт <--
	
/// -------------------------------работа курьером по доставке почты-------------------------------------

		case "Postcureer":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.7)); 
			if (sti(pchar.questTemp.WPU.Postcureer.DaysQty) == 1) pchar.questTemp.WPU.Postcureer.DaysQty = 2;
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*1000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));
			dialog.text = "この荷物は、都市の港湾当局に届けなければならない "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)+"、のために "+FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DaysQty)+"、できるだけ早く頼む。報酬は― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))".";
			link.l1 = "同意するぜ！";
			link.l1.go = "Postcureer_1";
			link.l2 = "ふむ……だが、俺はそっちには行かねえんだ。悪いが、断らせてもらうぜ。";
			link.l2.go = "exit";
		break;
	
		case "Postcureer_1":
			dialog.text = "素晴らしい！頼りにしているぞ。これが荷物だ。";
			link.l1 = "すぐに出航するぜ！";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "PostLetters");
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Postcureer.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)+1;//считаем сделанные доставки
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			if (pchar.questTemp.WPU.Postcureer.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Postcureer.Chance == 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "1");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)); // belamour gen
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_complete":
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.DayLate = iTime;
				pchar.questTemp.WPU.Postcureer.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money) - sti(pchar.questTemp.WPU.Postcureer.Money)*sti(pchar.questTemp.WPU.Postcureer.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "ふむ……だが、お前は "+FindRussianDaysString(iTime)+" 遅れましたね。したがって、今回の仕事の報酬を減額せざるを得ません。契約によれば、 遅延一日ごとに総額の五パーセントがあなたの違約金となります。では、どうぞ、あなたの\n "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+"、そして今後は契約を守るようにしてくれ。";
				link.l1 = "まあ、少なくとも何かはあるな。";
				link.l1.go = "Postcureer_complete_1";
				break;
			}
			dialog.text = "お勤めご苦労だった。さあ、報酬を受け取ってくれ－ "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
			link.l1 = "ありがとう！";
			link.l1.go = "Postcureer_complete_1";
		break;
	
		case "Postcureer_complete_1":
			if (pchar.questTemp.WPU.Postcureer == "begin")
			{
				pchar.quest.PostcureerTime_Over.over = "yes";
				AddQuestRecord("Postcureer", "2");
			}
			else
			{
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "4");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DayLate));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			}
			RemoveItems(PChar, "PostLetters", 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Achievment_Set("ach_CL_118");
			DialogExit();
		break;
	
		case "Postcureer_complete_bad":
			dialog.text = "「で、これを今さらどうしろって言うんだ？人々はいつから待たされていたかわからんくらいだぞ、 お前が持ってきたのは今日が初めてじゃないか。まあいい、渡せ。まだ何か使い道があるかもしれん。だが、 今さら報酬が出ると思うなよ。」";
			link.l1 = "もちろんだ。荷物を持っていけ。さらばだ。";
			link.l1.go = "exit";
			RemoveItems(PChar, "PostLetters", 1);
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			Group_DeleteGroup("Fraht_Attack");
			pchar.questTemp.WPU.Postcureer = "fail";
		break;
	
/// ---------------------------работа в качестве эскорта для торговых кораблей----------------------------

		case "escort":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods1 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.Goods2 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1)); 
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));
			dialog.text = "つまり、船の護衛をしてもらうことになる。"+pchar.questTemp.WPU.Escort.ShipName1+"「」と「」"+pchar.questTemp.WPU.Escort.ShipName2+"「」の街へ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)+"、のために "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+"。支払い－ "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))"。両方の船を無事に目的地まで届けなければならん。現地の港役人に船を引き渡すんだ。 報酬もその役人から受け取ることになるぞ。";
			link.l1 = "すべて問題なさそうだ。進めてもよろしいか？";
			link.l1.go = "escort_1";
			link.l2 = "ふむ……だが、俺はそっちには行かねえんだ。悪いが、断らせてもらうぜ。";
			link.l2.go = "exit";
		break;
	
		case "escort_1":
			dialog.text = "進め。今やその船はお前の指揮下にあるぜ。";
			link.l1 = "じゃあ、出航するぜ！";
			link.l1.go = "escort_add_ships";
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "1");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)); // belamour gen
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "escort_add_ships":
			int iGoods1, iGoods2, iSpace1, iSpace2, ShipType, Rank;
			int iNation = pchar.questTemp.WPU.Escort.ShipNation;
			int iLifeday = sti(pchar.questTemp.WPU.Escort.DaysQty)+10;
			string sTemp;
	        for (i=1; i<=2; i++)
	        {
				ShipType = GetRandomShipType(GetClassFlag(sti(RealShips[sti(pchar.Ship.Type)].Class)), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
				Rank = 5 * (6 - sti(RealShips[sti(pchar.Ship.Type)].Class)) + rand(5);
				if (i == 1) sTemp = pchar.questTemp.WPU.Escort.ShipName1;
				if (i == 2) sTemp = pchar.questTemp.WPU.Escort.ShipName2;
				if (i == 2) ShipType = SHIP_FLEUT;//один всегда флейт
	            sld = GetCharacter(NPC_GenerateCharacter("EscortCaptain_"+i, "trader_"+(rand(15)+1), "man", "man", Rank, iNation, iLifeday, true, "citizen"));
				FantomMakeSmallSailor(sld, ShipType, sTemp, -1, 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10));
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				SetCharacterGoods(sld, GOOD_FOOD, 400+rand(200));
				SetCharacterGoods(sld, GOOD_MEDICAMENT, 60+rand(30));
	            iGoods1 = sti(pchar.questTemp.WPU.Escort.Goods1);
				iSpace1 = GetCharacterFreeSpace(sld, iGoods1);
				iSpace1 = makeint(iSpace1/2 + rand(iSpace1/2));
				iGoods2 = sti(pchar.questTemp.WPU.Escort.Goods2);
				iSpace2 = GetCharacterFreeSpace(sld, iGoods2);
				iSpace2 = makeint(iSpace2/2 + rand(iSpace2/2));
				if (i == 1) SetCharacterGoods(sld, iGoods1, iSpace1);
				if (i == 2) SetCharacterGoods(sld, iGoods2, iSpace2);
				sld.CompanionEnemyEnable = false; //всегда друзья
	            SetCompanionIndex(pchar, -1, sti(sld.index));
				sld.loyality = MAX_LOYALITY;
				SetCharacterRemovable(sld, false);
				sld.Dialog.Filename = "Common_portman.c";
				sld.dialog.currentnode = "Escort_companion";
				pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l1.character = "EscortCaptain_1";
				pchar.quest.Escort_fail.win_condition.l2 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l2.character = "EscortCaptain_2";
				pchar.quest.Escort_fail.function = "Escort_failed";
	        }
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			DialogExit();
		break;
	
		case "Escort_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//проверяем, все ли корабли
			if (GetCharacterIndex("EscortCaptain_1") == -1 || GetCharacterIndex("EscortCaptain_2") == -1)
			{
				dialog.text = "ふむ……護衛には一隻しか船が見えないが、それで間違いないか？";
				link.l1 = "「ああ、」 "+GetAddress_FormToNPC(NPChar)+"。もう一隻は敵の艦隊との戦闘で沈められた。";
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
				{
					link.l1.go = "EscortBonus_complete_fail";
				}
				else
				{
					link.l1.go = "Escort_complete_fail";
				}
				break;
			}
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				//pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney);
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.TotalMoney);
				amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
				if (amount > 0)
				{
					dialog.text = "よし、そういうことだな。お前は船団を護衛して、積荷を届けるはずだった "+GetGoodsNameAlt(iGoods)+" 「～の額で」 "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty))+"。しかし、まだ全ての積荷を届けていないようだな――お前は "+FindRussianQtyString(sti(amount))+" 短い。";
					link.l1 = "「千匹のサメだと！きっとあの忌々しいネズミどもに違いねえ！だが心配すんな、」 "+GetAddress_FormToNPC(NPChar)+"、足りない分は俺が買い取って、全部まとめて納品するぜ。";
					link.l1.go = "Fraht_complete_3";
					break;
				}
			}
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "ふむ……だが、お前は "+FindRussianDaysString(iTime)+" 遅れましたね。したがって、今回の仕事の報酬を減額せざるを得ません。契約によれば、 遅延一日ごとに総額の五パーセントが罰金となります。では、どうぞ、あなたの\n "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+"、そして今後は契約を守るようにしてくれ。";
				link.l1 = "まあ、少なくとも何かはあるな。";
				link.l1.go = "Escort_complete_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				dialog.text = "よし、それじゃあ。お前は船団を護衛して、積み荷を届ける役目だったんだ "+GetGoodsNameAlt(iGoods)+" の額で "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty))+"。ご苦労だった。さあ、報酬を受け取ってくれ― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
			}
			else
			{
				dialog.text = "お勤めご苦労だった。さあ、報酬を受け取ってくれ－ "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
			}
			link.l1 = "ありがとう！";
			link.l1.go = "Escort_complete_1";
		}
		else
		{
			dialog.text = "港にお前の船が見当たらねえな。沖に錨を下ろしてからもう一度俺のところに来い――そしたら話をしよう。";
			link.l1 = "わかった、そうするぜ。";
			link.l1.go = "exit";
		}
		break;
	
		case "Escort_complete_1":
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				AddQuestRecord("Escort", "2");
			}
			else
			{
				pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//опоздавший рейс не засчитываем
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
				{
					pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				}
				AddQuestRecord("Escort", "4");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_1"));//удалим компаньонов
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_2"));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 100);//защита
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "escort_bonus":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods = 	hrand(GOOD_PAPRIKA);//для ГГ
			pchar.questTemp.WPU.Escort.Goods1 = hrand(GOOD_PAPRIKA-3);
			pchar.questTemp.WPU.Escort.Goods2 = hrand(GOOD_PAPRIKA-5);
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			iGoodsQty = makeint(GetCharacterFreeSpace(pchar, iGoods))-(50+rand(100));//количество груза
			pchar.questTemp.WPU.Escort.GoodsQty = iGoodsQty;
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1));//дни
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));//оплата за сопровождение
			pchar.questTemp.WPU.Escort.BonusMoney = (makeint((sti(iGoodsQty) * sti(Goods[iGoods].Weight) / sti(Goods[iGoods].Units))))*(sti(idaysQty)*2)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty);//оплата за фрахт
			pchar.questTemp.WPU.Escort.TotalMoney = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney); // общая сумма
			dialog.text = "つまり、船団の護衛を頼まれることになる "+pchar.questTemp.WPU.Escort.ShipName1+"「と」"+pchar.questTemp.WPU.Escort.ShipName2+"「」の街へ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)+"、のため "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+"。支払い－ "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+"\nそれから、積荷もお前の船に載せておくぜ。 "+GetGoodsNameAlt(iGoods)+" の額で "+FindRussianQtyString(iGoodsQty)+"。配達の報酬だ―― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+".";
			link.l1 = "全て明らかのようだ。進めてもよろしいか？";
			link.l1.go = "escort_bonus_1";
			link.l2 = "ふむ……だが、俺はそっちには行かねえんだ。悪いが、断らせてもらうぜ。";
			link.l2.go = "exit";
		break;
	
		case "escort_bonus_1":
			dialog.text = "素晴らしい！艦隊の指揮を執れ。";
			link.l1 = "じゃあ、出航するぜ！";
			link.l1.go = "escort_add_ships";
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.Bonus = "true";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 3) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "6");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
			AddQuestUserData("Escort", "sGoods", GetGoodsNameAlt(iGoods));
			AddQuestUserData("Escort", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)));
			AddQuestUserData("Escort", "sMoney1", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Escort.GoodsQty);//средняя стоимость товара
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "Escort_complete_fail":
			dialog.text = "信じられん！それでお前が必要だった意味があるのか？どうしてこんな事態を許したんだ！？ これで報酬は無しだということ、わかってるだろうな。";
			link.l1 = "もちろんだ…さて、ごきげんよう。";
			link.l1.go = "exit";
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			pchar.quest.EscortTime_Over.over = "yes";//снять прерывание // patch-2
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));
			AddQuestRecord("Escort", "11");
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "EscortBonus_complete_fail":
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));//удалим компаньона
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			pchar.questTemp.WPU.Escort.GoodsQty = GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				pchar.questTemp.WPU.Escort.MinusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)*sti(amount));
				if (sti(pchar.questTemp.WPU.Escort.MinusMoney) < 0) amount = 101;
				if (amount > 0 && amount <= 100)
				{
					pchar.questTemp.WPU.Escort.BonusMoney = sti(pchar.questTemp.WPU.Escort.MinusMoney);
					dialog.text = "信じられん！一体お前に何を頼んだ意味があったんだ？どうしてこんな事態を許したんだ！？ これで護衛の報酬なんて論外だと分かっているだろうな……それだけじゃない、積荷まで足りてないじゃないか― "+FindRussianQtyString(sti(amount))+"\n基本的に、俺が支払うのは、無事に届けられた貨物分の運賃だけだ。足りない分の価値は差し引くからな。自分の "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+" 好きなところへ行っていいぞ。";
					link.l1 = "まあ、少なくとも何かはあるな。";
					link.l1.go = "EscortBonus_complete_fail_1";
					break;
				}
				if (amount > 100)
				{
					dialog.text = "信じられん！それでお前が必要だった意味は何だ？どうしてこんな事態を許したんだ！？ これで護衛の報酬なんて論外だと分かっているだろうな……それだけじゃない、積荷も大幅に不足しているじゃないか。\n足りない品を揃えるのを待つ時間なんてない。だから全額補償してもらうぞ― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+"。貨物については、お前が持っていていいぜ。";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "わかった、そんなに熱くなるなよ。ほら、金だ。";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "お前ら、気でも狂ったのか？これは完全なゆすりじゃねえか！俺は何も渡さねえぞ！";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "信じられん！それでお前に何の用があったんだ？どうしてこんな事態を許したんだ！？ これで護衛の報酬は一切なしだということ、分かっているだろうな。\nとにかく、お前が運んだ貨物の運賃だけは払う。さあ、 "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+" 好きなところへ行っていいぞ。";
				link.l1 = "まあ、少なくとも何かはあるな。";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
			if (pchar.questTemp.WPU.Escort == "late")
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.BonusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Escort.BonusMoney)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				if (amount > 0)
				{
					dialog.text = "信じられん！それでお前が必要だったのか？どうしてこんな事を許したんだ！？ 護衛の報酬なんて論外だと分かってるだろうな……船を失い、お前は到着した\n "+FindRussianDaysString(iTime)+" 遅れてきた上に、しかも貨物も足りてねえじゃねえか── "+FindRussianQtyString(sti(amount))+"\nお前が足りない品を手に入れるのを待つ暇はない。だから全額を補償してもらうぞ "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+"。貨物については、お前が持っていていいぜ。";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "わかった、そんなに熱くなるなよ。ほら、金だ。";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "お前ら、正気か？これはまるっきりゆすりじゃねえか！俺は何も渡さねえぞ！";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "信じられん！で、何のためにお前を雇ったんだ？どうしてこんな事態を許したんだ！？ これで護衛の報酬なんて論外だということは分かっているだろうな……それに、お前は到着した\n "+FindRussianDaysString(iTime)+" 遅れたな。\nだから貨物運賃の支払いを減額せざるを得なかった。契約によれば、遅延一日ごとに元の金額の10パーセントが罰金となる。さあ、受け取れ "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+"、それでは行ってよい。";
				link.l1 = "まあ、少なくとも何かはあるな。";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
		break;
	
		case "EscortBonus_complete_fail_1"://потеряли корабль, время и груз в норме или частично
			AddQuestRecord("Escort", "12");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.BonusMoney));
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_2"://потеряли корабль и груз, время норма или нет, мир
			AddQuestRecord("Escort", "13");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_3"://потеряли корабль и груз, время норма или нет, война
			dialog.text = "ああ、そうか……なら、その場合は二度とどこの港の役所にも顔を出すんじゃねえぞ "+NationNameGenitive(sti(pchar.questTemp.WPU.Escort.Nation))+"「うせろ！」";
			link.l1 = "「大して見逃してねえだろう……」";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "14");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.WPU.Escort.Nation)) + "hunter", 30);
			pchar.questTemp.WPU.Fraht.Nation = pchar.questTemp.WPU.Escort.Nation;
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "Escort_fail"://потеряли 2 корабля
			dialog.text = "これは本当に、とてもまずいぞ！一体何のためにお前を雇ったと思っているんだ、言ってみろ！船を守るためか？ それともただうろつくためか？";
			link.l1 = "承知した。敵があまりにも強すぎたんだ、それに……だが、今さら言い争っても仕方ねえ――起きたことはもう変わらねえさ。だが、積み荷は――積み荷はまだ無事だ！さあ、整理しようじゃねえか。";
			link.l1.go = "Escort_fail_complete";
		break;
	
		case "Escort_fail_complete":
			iFrahtGoods = makeint(pchar.questTemp.WPU.Escort.Goods);
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (amount > 0)
			{
				dialog.text = "さて、見せてもらおうか。お前は本来、積荷を届けるはずだったよな "+GetGoodsNameAlt(iFrahtGoods)+" 「の額で」 "+FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty)+"。しかし、まだ全ての荷を届けていないようだな――お前は "+FindRussianQtyString(sti(amount))+" 短い。";
				link.l1 = "「千匹のサメだと！きっとあの忌々しいネズミどもに違いねえ！だが心配すんな、」 "+GetAddress_FormToNPC(NPChar)+"、足りない分は俺が買い取って、全部まとめて納めるぜ。";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "さて、見せてもらおうか。お前は本来、荷物を届けるはずだった "+GetGoodsNameAlt(iFrahtGoods)+" 「の額で」 "+FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty)+"。正しいか？";
			link.l1 = "「まったくその通りだ」 "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "Escort_fail_complete_1";
		break;
	
		case "Escort_fail_complete_1":
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney)/2);
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "ふむ……任された船を失っただけでなく、さらに遅れてきたのだな "+FindRussianDaysString(iTime)+"。だから運賃の支払いを減額せざるを得なかった。船を救えなかったので、運賃の支払いは半分にした。 これが私が出せる精一杯だ。\nさらに、契約によれば遅延一日ごとに元の金額の一割が罰金となる。さあ、受け取りなさい "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+"、それじゃあ行ってこい。";
				link.l1 = "まあ、少なくとも何かはあるな。";
				link.l1.go = "Escort_fail_complete_2";
				break;
			}
			dialog.text = "まあ、君に託した船を守れなかったことには非常に腹立たしいが、少なくとも貨物は届けてくれたな。 船を救えなかったので、運賃の支払いは半額にした。これが君にできる最大限の支払いだ。さあ、報酬を受け取れ—— "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+" そして、好きなところへ行っていいぞ。";
			link.l1 = "まあ、少なくとも何かはあるな。";
			link.l1.go = "Escort_fail_complete_2";
		break;
	
		case "Escort_fail_complete_2":
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";
				AddQuestRecord("Escort", "17");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			else
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				AddQuestRecord("Escort", "18");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//фейловый рейс не засчитываем
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
//-------------------------------------задания 2 уровня для курьера---------------------------------------------
		case "Postcureer_LevelUp":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);//целевой город
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.6));//дни
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*3000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));//оплата
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			pchar.questTemp.WPU.Postcureer.StartNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Postcureer.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}

			switch (rand(3))
			{
				case 0:
					dialog.text = "至急の公用書簡をその町の総督に届けてもらう必要がある "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" 遅くとも "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+"。十分に気をつけてくれ――敵もその書状を狙っているかもしれん。配達の報酬は―― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "同意するぜ！";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "いや、今回は遠慮しておくぜ。";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_Mayor";//ИД губера
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == "Villemstad_Mayor") pchar.questTemp.WPU.Postcureer.TargetPortmanID = "hol_guber"; // фикс Матиаса Бека #717
					pchar.questTemp.WPU.Current.Add = "a dispatch for the governor";
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp1";//описание
				break;
			
				case 1:
					dialog.text = "これらの書類を店主に届けてもらう必要がある "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" 遅くとも "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+"。これは諸島中の店の最新価格一覧だ――貴重な商業書類だぜ。気をつけろよ、ライバルが狙ってくるかもしれねえ。配達の報酬は―― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "同意するぜ！";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "いや、今回は遠慮しておくぜ。";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_trader";//ИД торговца
//					pchar.questTemp.WPU.Current.Add = "сводку цен для хозяина магазина";
					pchar.questTemp.WPU.Current.Add = "a price list for the store owner";     // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp2";//описание
				break;
			
				case 2:
					dialog.text = "この書類の束を町の高利貸しに届けてもらう必要がある "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" 遅くとも "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+"。これは通貨の為替レートや株価に関する非常に重要な情報だ。十分に注意しろ――この荷物を狙っている怪しい連中がすでに動き出している。配達の報酬は―― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "同意するぜ！";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "いや、今回は遠慮しておくよ。";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_usurer";//ИД ростовщика
					pchar.questTemp.WPU.Current.Add = "a packet of information for the moneylender";   // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp3";//описание
				break;
			
				case 3:
					dialog.text = "この包みをその町のドックマスターに届けるべきだ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" 遅くとも "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+"。新しいものの設計図が含まれている "+RandPhraseSimple(LinkRandPhrase("ブリッグ","コルベット","フリゲート"),LinkRandPhrase("フルート","ピナス","ガレオン"))+"、独自の技術設計を用いているんだ。他にも…関心を持つ者たちがいることは理解してほしい、だから慎重に行動してくれ。納品の報酬は― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "同意するぜ！";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "いや、俺は遠慮しておくぜ。";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_shipyarder";//ИД верфиста
					pchar.questTemp.WPU.Current.Add = "the draft of a new ship for the owner of the shipyard";
					pchar.questTemp.WPU.Current.Item = "ShipyardsMap";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_ShipyardsMap_PortmanLevelUp4";//описание
				break;
			}
		break;
	
		case "Postcureer_LevelUp_Go":
			dialog.text = "それでは書類を受け取って出航しなさい。幸運を祈る……そして全能の神のご加護がありますように。";
			link.l1 = "ありがとう！";
			link.l1.go = "Forsmajor_choose";
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.LevelUp = "true";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) + 1;
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			ChangeItemDescribe(pchar.questTemp.WPU.Current.Item, pchar.questTemp.WPU.Current.Itemdescr);
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "6");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)); // belamour gen
			AddQuestUserData("Postcureer", "sText", pchar.questTemp.WPU.Current.Add);
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_LevelDown":
			dialog.text = "本当に残念だな……まあ、そういう申し出は普通は簡単に断るもんじゃねえが、最終的にはお前の判断だぜ。";
			link.l1 = "「ああ、それは俺の判断だ」 "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) - 1;//за отказ от спецзадания счетчик скрутим
		break;
	
		case "Forsmajor_choose":
			switch (sti(pchar.questTemp.WPU.Postcureer.Chance))
			{
				case 0://охотники в городе прибытия + ДУ
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.City + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerGopHuntersOnLand";
					TraderHunterOnMap(false);
				break;
		
				case 1://создание скоростного перехватчика на глобалке
					EnemyNationHunterOnMap(true);
				break;
		
				case 2://запуск ДУ на глобалке и в порту прибытия
					TraderHunterOnMap(false);
					FrahtHunterOnSea();
				break;
		
				case 3://наёмники в стартовом городе
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerProfHuntersOnLand";
				break;
		
				case 4://агент
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerAgent";
				break;
			}
			DialogExit();
		break;

		case "Postcureer_complete_fail":
			dialog.text = "くそっ！やっぱり奴らに見つかったのか。残念だが、お前が兵士じゃねえのが惜しいな、船長――そうだったら、結果も違ったかもしれねえ……で、奴らはどんな面してた？";
			link.l1 = "黒い服を着て顔に半面の仮面をつけた、頑丈で屈強な二人の男が、ポールアックスと二連銃で武装している……";
			link.l1.go = "Postcureer_complete_fail_1";
		break;

		case "Postcureer_complete_fail_1":
			dialog.text = "すぐに総督に知らせて捜索を始めさせる。\nよし、それじゃあな。 "+GetAddress_Form(NPChar)+"。また、あなたが兵士でないのは残念だな……";
			link.l1 = "「本当に申し訳ない」 "+GetAddress_FormToNPC(NPChar)+"……今回の出来事については申し訳ない。では、さらばだ。";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.fail");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
	
//----------------------------------------задания 2 уровня фрахт------------------------------------------

	case "Fraht_LevelUp":
		rColony = GetColonyByIndex(FindColony(npchar.city));
		pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Fraht.Nation = npchar.nation;//нация получателя
		switch (rand(4))//для тестов
		{
			case 0:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_CHOCOLATE + hrand(makeint(GOOD_TOBACCO - GOOD_CHOCOLATE));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 3000 + sti(pchar.rank)*30*(hrand(9)+1);
				iGoodsQty = 1000+sti(pchar.rank)*10*(hrand(9)+1); // min 1100 max 5000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "我が植民地で最近、ある商品への需要が急激に高まっている。\n地元の店ではもう在庫がないのだ。\nそこで、君にその品を用意してもらいたい。 "+GetGoodsNameAlt(iGoods)+" 「～の額で」 "+FindRussianQtyString(iGoodsQty)+"、そして倍額を支払うつもりだ― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" 1つあたり。合計で "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+"。ああ、それと納期は一ヶ月以内に頼むぞ――これ以上は品物を待てないからな。";
				link.l1 = "よし、この任務を引き受けるぜ。";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "ご期待に添えず申し訳ありませんが、今はそれができません。";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 1:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_EBONY + hrand(makeint(GOOD_CINNAMON - GOOD_EBONY));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 1500 + sti(pchar.rank)*20*(hrand(9)+1);
				iGoodsQty = 600+sti(pchar.rank)*5*(hrand(6)+1); // min 630 max 2000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "最近、我が植民地である商品への需要が急激に高まっている。\n地元の店ではもう在庫がない。\nそこで、君にその品を調達してもらいたいのだ。 "+GetGoodsNameAlt(iGoods)+" の額で "+FindRussianQtyString(iGoodsQty)+"、そして倍額払うつもりだ―― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" 1つあたり。合計で "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+"。ああ、それと納期は一か月以内に頼むぞ――これ以上品物を待てないんだ。";
				link.l1 = "よし、この任務、引き受けるぜ。";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "申し訳ないが、今はそれをすることができないんだ。";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 2:
				//pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS + hrand(makeint(GOOD_POWDER - GOOD_BOMBS));
				pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 15000 + sti(pchar.rank)*300*(hrand(9)+1);
				iGoodsQty = 5000+sti(pchar.rank)*10*(hrand(9)+1); // min 5100 max 9000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/20);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "我々の植民地の兵器庫は深刻に不足している "+GetGoodsNameAlt(iGoods)+"。地元の店にはもう在庫がありません。それゆえ、あなたに用意してもらいたいのです\n "+GetGoodsNameAlt(iGoods)+" 「…の額で」 "+FindRussianQtyString(iGoodsQty)+"、それに俺は三倍払うつもりだ―― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" 1個あたり。合計で "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+"。ああ、それと納期は一か月以内に頼むぞ――これ以上品物を待てないんだ。";
				link.l1 = "よし、この任務を引き受けるぜ。";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "申し訳ないが、今はそれをすることはできないんだ。";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 3:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_MEDICAMENT;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 7000 + sti(pchar.rank)*300*(hrand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/30);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "最近わが植民地で熱病が流行したため、医療用品が不足しており、倉庫にも何も残っていません。 総督は町民の安全を案じております。そこで、あなたに用意していただきたいのです\n "+GetGoodsNameAlt(iGoods)+" の額で "+FindRussianQtyString(iGoodsQty)+"、そして俺は三倍払うつもりだ― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" 1パックあたり。これで合計 "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+"。ああ、それと納期は一ヶ月以内に頼む――これ以上品物を待つことはできんからな。";
				link.l1 = "よし、この任務を引き受けるぜ。";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "ご期待に添えず申し訳ありませんが、今はそれができません。";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 4:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_FOOD;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 15000 + sti(pchar.rank)*300*(hrand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2)/10);//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "不作のせいで、我々の植民地は常に輸入食料を必要としている。今のところ、備蓄はほとんど空で、 店の棚からもずいぶん前に全てが消えてしまった。そこで、あなたに届けてほしいのだ\n "+GetGoodsNameAlt(iGoods)+" 「～の額で」 "+FindRussianQtyString(iGoodsQty)+"、そして倍額払うつもりだ―― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" 1パックあたり。これで合計は "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+"。ああ、それと納期は一ヶ月以内に頼むぞ――もうこれ以上、品物を待てんからな。";
				link.l1 = "よし、この任務を引き受けるぜ。";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "申し訳ないが、今はそれをすることはできない。";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		}
	break;
		
	case "Fraht_LevelDown":
		DialogExit();
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//скрутим счетчик
	break;
		
	case "Fraht_LevelUp_Go":
		dialog.text = "素晴らしい！引き受けてくれて本当に嬉しい。\nまたすぐにお会いできることを願っている。";
		link.l1 = "「もちろん」 "+GetAddress_FormToNPC(NPChar)+".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Fraht = "begin";
		pchar.questTemp.WPU.Fraht.LevelUp = "true";
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count) + 1;
		pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.StartCity +"_portman";//ИД портмана
		iGoods = pchar.questTemp.WPU.Fraht.Goods;
		ReOpenQuestHeader("Fraht");
		AddQuestRecord("Fraht", "8");
		AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
		AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
		AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iGoods));
		AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty)));
		AddQuestUserData("Fraht", "sText", pchar.questTemp.WPU.Current1.Add);
		SetFunctionTimerCondition("FrahtTimeLevelUp_Over", 0, 0, 30, false);
	break;
	
	case "Fraht_completeLevelUp":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		iGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
		amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
		if (amount > 0)
		{
			dialog.text = "ふざけてるのか？俺が注文した分の品物が揃ってねえじゃねえか！";
			link.l1 = "申し訳ない、俺のミスだ……";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "よし、お前は本来なら積荷を届けるはずだった "+GetGoodsNameAlt(iGoods)+" の額で "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+"。素晴らしい、ありがとうございます。こちらがあなたへの報酬です― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "「取引できて嬉しいぜ」 "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "Fraht_completeLevelUp_1";
		}
	}
	else
	{
		dialog.text = "港にお前の船が見当たらねえな。沖に停泊させてからもう一度来い――そしたら話をしよう。";
		link.l1 = "わかった、その通りにするぜ。";
		link.l1.go = "exit";
	}
	break;
	
	case "Fraht_completeLevelUp_1":
		pchar.quest.FrahtTimeLevelUp_Over.over = "yes";//снять таймер
		AddQuestRecord("Fraht", "2");
		CloseQuestHeader("Fraht");
		RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current1"); // лесник  Current1 вместо Current
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.LevelUp");
		pchar.questTemp.WPU.Fraht = "complete";
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
		DialogExit();
	break;
	
//----------------------------------------задания 2 уровня эскорт ------------------------------------------

	case "Escort_LevelUp":
		pchar.questTemp.WPU.Escort.LevelUp = "true";//установим атрибут
		pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Escort.Nation = npchar.nation;//нация квестодателя
		pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
		i = 0;
		while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
		{
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
			i++;
			if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
		}
		switch (hrand(2))
		{
			case 0://приключения на необитаемых островах
				pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();//выбор необитайки
				while (!isLocationFreeForQuests(pchar.questTemp.WPU.Current.TargetIslandID)) pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();//выбор корабля
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));//имя корабля
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				pchar.questTemp.WPU.Escort.ShipBaseName = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.WPU.Escort.ShipType), "Name") + "Gen"));
				dialog.text = "この災難が起きたのは十日前のことだ……我々の植民地へ向かう商船団が海賊に襲われた。突風が吹き荒れ、海賊どもは退却したが、商船たちは四散し、 お互いを見失ってしまった。結局、すべての船が別々の港にたどり着いたが、一隻だけ行方知れずだ。\n"+pchar.questTemp.WPU.Escort.ShipBaseName+" 「」"+pchar.questTemp.WPU.Escort.ShipName+"「」は消息を絶ち、その運命は未だ不明だ。おそらく無人島の近くで見つかるだろう。 "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+"。そこへ行き、行方不明の船に何が起きたのか調べ、もし無事なら我々の港まで連れてきてほしい。 報酬については任務完了後に決めるが、必ずや満足できるものになると約束しよう。";
				link.l1 = "もちろん、同意するぜ！";
				link.l1.go = "Escort_LevelUp_1";
				link.l2 = "申し訳ないが、この仕事は俺には向いていない。悪いが、遠慮させてもらうぜ。";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 1://защитить конвой вблизи текущего острова от пиратов
				pchar.questTemp.WPU.Current.TargetIslandID = Islands[GetCharacterCurrentIsland(PChar)].id;//текущий остров
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				dialog.text = "我々の植民地には交易隊が到着する予定だったが、港に入る直前に海賊に襲われたのだ。戦闘はまさに今行われている。 砦の大砲の射程外で、しかも今は護衛艦も用意できないから、哀れな商人たちを助けてやることができん。 君は勇敢な船長だ、だからこそ君に頼みたい――介入して商人たちを助け、海賊を撃退してくれ！やってくれるか？";
				link.l1 = "もちろんだ！名誉の問題だぜ！";
				link.l1.go = "Escort_LevelUp_2";
				link.l2 = "申し訳ないが、この仕事は俺には向いてねえ。悪いが、今回は遠慮させてもらうぜ。";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 2://встретить и довести
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();
				pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//город, откуда забрать
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
				sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
				pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
				pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(npchar);//ИД целевого ареала
				pchar.questTemp.WPU.Escort.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));//расстояние в днях
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.DaysQty)*2000+20000;
				pchar.questTemp.WPU.Escort.Chance = rand(1);
				dialog.text = "我が植民地が注文した武器と弾薬を積んだ船が最近植民地に到着した "+XI_ConvertString(pchar.questTemp.WPU.Escort.City)+"。彼女の護衛船は暗礁に乗り上げて大破し、当分の間出港できそうにありません。 このような積荷を載せた交易船を単独で送り出すわけにはいかないのです。\nあなたが彼女を我々の植民地まで護衛してくれませんか？報酬は既に決まっております "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
				link.l1 = "もちろん、同意するぜ！";
				link.l1.go = "Escort_LevelUp_0";
				link.l2 = "申し訳ないが、この仕事は俺には向いてねえ。悪いが、今回は遠慮させてもらうぜ。";
				link.l2.go = "Escort_LevelUp_exit";
			break;
		}
	break;
	
	case "Escort_LevelUp_exit":
		dialog.text = "本当に残念だ。実はお前に期待してたんだがな…";
		link.l1 = "俺も残念だぜ。じゃあ、また会う日までな。 "+GetAddress_FormToNPC(NPChar)+".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//скрутим счетчик
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	break;
	
	case "Escort_LevelUp_0":
		dialog.text = "素晴らしい！君なら頼りになると思っていたよ。できるだけ早く頼む。私が思うに\n "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+" 「まで行くのに十分だ」 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City+"Gen")+"。これを渡そう、身分を証明する書類だ。順風を祈るぜ、船長！";
		link.l1 = "心配するな、俺はお前をがっかりさせねえぜ。";
		link.l1.go = "Escort_LevelUp_0_go";
	break;
	
	case "Escort_LevelUp_0_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "19");
		AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty));
		SetFunctionTimerCondition("EscortArsenalShip_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+1, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.LevelUp_0 = "true";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LUGo_0":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.EscortArsenalShip_Over.over = "yes";
		dialog.text = "やっとか！あの船はずっと目障りだったぜ。さあ、指揮を取れ。その船の名前は "+pchar.questTemp.WPU.Escort.ShipName+"、そして彼女の船長にはあなたの到着がすぐに通知されるでしょう。";
		link.l1 = "奴に船を出航できるよう準備させろ――俺はできるだけ早く出発するつもりだ。";
		link.l1.go = "Escort_LUGo_01";
	}
	else
	{
		dialog.text = "港にお前の船が見当たらねえな。今は沖で待ってろ、また後で来い――そしたら話をしよう。";
		link.l1 = "まさにそうするぜ。";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_01"://добавляем компаньона
		int iShipType = sti(pchar.questTemp.WPU.Escort.ShipType);
		sTemp = pchar.questTemp.WPU.Escort.ShipName;
		sld = GetCharacter(NPC_GenerateCharacter("ArsenalShipCaptain", "citiz_41", "man", "man", 15, sti(pchar.nation), -1, true, "quest"));
		FantomMakeSmallSailor(sld, iShipType, sTemp, CANNON_TYPE_CANNON_LBS16, 65, 22, 24, 35, 33);
		SetFantomParamFromRank(sld, 15, true); 
		SetCaptanModelByEncType(sld, "war");
		SetCharacterGoods(sld, GOOD_FOOD, 500);
		SetCharacterGoods(sld, GOOD_BALLS, 5000);
		SetCharacterGoods(sld, GOOD_GRAPES, 3000);
		SetCharacterGoods(sld, GOOD_KNIPPELS, 3000);
		SetCharacterGoods(sld, GOOD_BOMBS, 5000);
		SetCharacterGoods(sld, GOOD_POWDER, 10000);
		SetCharacterGoods(sld, GOOD_WEAPON, 3000);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		SetCharacterRemovable(sld, false);
		sld.loyality = MAX_LOYALITY;
		sld.Dialog.Filename = "Common_portman.c";
		sld.dialog.currentnode = "Escort_companion";
		DialogExit();
		AddQuestRecord("Escort", "20");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
		pchar.quest.Escort_fail.win_condition.l1.character = "ArsenalShipCaptain";
		pchar.quest.Escort_fail.function = "EscortArsenalShip_failed";
		SetFunctionTimerCondition("EscortArsenalShipGo_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+6, false);
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0");
		pchar.questTemp.WPU.Escort.LevelUpGo_0 = "true";
		if (sti(pchar.questTemp.WPU.Escort.Chance) == 0) EnemyNationHunterOnMap(true);//скоростной перехватчик
		else FrahtHunterOnSea();
	break;
	
	case "Escort_LUGo_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.Escort_fail.over = "yes";
		pchar.quest.EscortArsenalShipGo_Over.over = "yes";
		dialog.text = "素晴らしい！今回も君が頼りになることを証明してくれたな。よくやってくれてありがとう。さあ、 報酬を受け取ってくれ― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+"。 それと、時々は私のところに顔を出すのを忘れないでくれ――あんたみたいな船長には、いつだって仕事があるからな。";
		link.l1 = "「それは良かった」 "+GetAddress_FormToNPC(NPChar)+"！もちろん、我々の協力関係はこれからも続く。よろしく頼む！";
		link.l1.go = "Escort_LUGo_complete_1";
	}
	else
	{
		dialog.text = "港にお前の船が見当たらねえな。今は沖で待ってろ、あとでまた来い――その時に話をしようぜ。";
		link.l1 = "よし、そうするぜ。";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_complete_1":
		RemoveCharacterCompanion(Pchar, characterFromID("ArsenalShipCaptain"));
		sld = characterFromId("ArsenalShipCaptain");
		sld.lifeday = 0;//на всякий случай
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
		AddQuestRecord("Escort", "24");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		CloseQuestHeader("Escort");
		DialogExit();
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 100, 100, 0, 100, 0, 0);
		AddComplexSelfExpToScill(30, 30, 30, 30);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_1":
		dialog.text = "それでは、ご無事の航海をお祈りします。\nそして、どうか捜索を遅らせないでください！その船の乗組員は今すぐ助けを必要としているかもしれません。";
		link.l1 = "了解だ。今日は出航するぜ！";
		link.l1.go = "Escort_LevelUp_1_select";
	break;
	
	case "Escort_LevelUp_1_select"://выберем приключение
		switch (rand(2))
		{
			case 0://весь побитый и остался без мачты
				pchar.quest.DisasterShip_WM.win_condition.l1 = "location";
				pchar.quest.DisasterShip_WM.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_WM.function = "CreateDisasterShip_WithoutMasts";
				pchar.questTemp.WPU.Escort.LevelUp_1WM = "true";
			break;
			case 1://ведет бой с пиратусами в шторме
				pchar.quest.DisasterShip_VSP.win_condition.l1 = "location";
				pchar.quest.DisasterShip_VSP.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_VSP.function = "CreateDisasterShip_VSPirate";
				for (i=0; i<MAX_ISLANDS; i++)//устроим шторм
				{				
					if (Islands[i].id == pchar.questTemp.WPU.Current.TargetIslandID)
					{
					Islands[i].alwaysStorm = true; 
					Islands[i].storm = true;
					Islands[i].tornado = true; 
					}
				}
				pchar.questTemp.WPU.Escort.LevelUp_1VSP = "true";
			break;
			case 2://потонул
				pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
				pchar.quest.DisasterShip_S.win_condition.l1 = "location";
				pchar.quest.DisasterShip_S.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
				pchar.quest.DisasterShip_S.function = "CreateDisasterShip_Crew";
				pchar.questTemp.WPU.Escort.LevelUp_1S = "true";
			break;
		}
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "25");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		SetFunctionTimerCondition("DesIsland_Over", 0, 0, 15, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LU1WM_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "はい、すでに連絡を受けている。素晴らしい働きだ。 "+GetAddress_Form(NPChar)+"！またしてもお前が頼りになる奴だと証明してくれたな。報酬として三万ペソ受け取れ。\n時々は俺のところに顔を出してくれよ――お前のような人間は貴重だし、いつでもお前にふさわしい仕事を用意しておくぜ。";
		link.l1 = "「それは嬉しいな」 "+GetAddress_FormToNPC(NPChar)+"！もちろん、これからも協力し続けます。ご健闘を祈ります！";
		link.l1.go = "Escort_LU1WM_complete_1";
	}
	else
	{
		dialog.text = "港にお前の船が見当たらねえな。今は沖で待っていろ、あとでまた来い――その時に話をしようじゃねえか。";
		link.l1 = "よし、そうするぜ。";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1WM_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 30000);
		ChangeCharacterComplexReputation(pchar,"nobility", 5);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 5);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 30000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Repair", 300);//починка
		AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "「はい、彼からすでに海賊との戦いと、あなたが彼の船を守るためにどれほど勇敢だったか聞いています。 素晴らしい働きでした。」 "+GetAddress_Form(NPChar)+"！またしても、お前が頼りになる奴だと証明してくれたな。報酬だ、五万ペソ受け取れ。\n時々は俺のところに顔を出してくれよ――お前みたいな奴は貴重だからな、いつでもお前にふさわしい仕事を用意しておくぜ。";
		link.l1 = "「それは良かった」 "+GetAddress_FormToNPC(NPChar)+"！もちろん、我々の協力関係はこれからも続く。よろしく頼む！";
		link.l1.go = "Escort_LU1VSP_complete_1";
	}
	else
	{
		dialog.text = "港にお前の船が見当たらねえな。今は沖で待機して、後でもう一度来い――その時に話をしようじゃねえか。";
		link.l1 = "わかった、その通りにするぜ。";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1VSP_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 50000);
		ChangeCharacterComplexReputation(pchar,"nobility", 10);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 6);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 50000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_completeSink":
		dialog.text = "なんて悲劇的な最期だ……神よ、彼らの魂に安らぎを。";
		link.l1 = "俺はできることは全部やったぜ。 "+GetAddress_FormToNPC(NPChar)+"。嵐が状況をさらに悪化させた。";
		link.l1.go = "Escort_LU1VSP_completeSink_1";
	break;
	
	case "Escort_LU1VSP_completeSink_1":
		dialog.text = "「私はそう信じている」 "+GetAddress_Form(NPChar)+"、君が船とあの不運な船乗りたちを救うためにできる限りのことをしたのは分かっている。しかし、残念ながら……。では、報酬として一万ペソを受け取ってくれ。そして、君の働きに感謝する。";
		link.l1 = "「礼には及ばねえ」 "+GetAddress_FormToNPC(NPChar)+"。誠に申し訳ありません。本当に、さようなら。";
		link.l1.go = "Escort_LU1VSP_completeSink_2";
	break;
	
	case "Escort_LU1VSP_completeSink_2":
		DialogExit();
		AddMoneyToCharacter(pchar, 10000);
		ChangeCharacterComplexReputation(pchar,"nobility", 1);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 10000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(50, 50, 50, 50, 0, 0, 0);
		AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1S_complete":
		dialog.text = "「ああ、あんたが赤い肌の異教徒と戦って、その後で海賊船ともやり合ったって、もう聞いてるぜ――まるで本物の英雄じゃねえか。見事な働きだ。」 "+GetAddress_Form(NPChar)+"！またしてもお前には頼りになると証明されたな。\n報酬の四万ペソを受け取れ。時々は私のところに顔を出すのを忘れるなよ――お前のような人材は貴重だし、いつでも相応しい仕事を用意しておくからな。";
		link.l1 = "「それは嬉しいな、」 "+GetAddress_FormToNPC(NPChar)+"！もちろん、我々の協力関係はこれからも続く。よろしく頼む！";
		link.l1.go = "Escort_LU1S_complete_1";
	break;
	
	case "Escort_LU1S_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 40000);
		ChangeCharacterComplexReputation(pchar,"nobility", 8);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 3);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 40000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(100, 100, 100, 100);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_2":
		dialog.text = "君なら頼りになると思っていたよ。幸運を祈るぜ、船長！植民地のみんながお前の勝利を願ってるぞ！";
		link.l1 = "ご期待に添えるよう努力いたします。これより出航いたします、神のご加護がありますように！";
		link.l1.go = "Escort_LevelUp_2_go";
	break;
	
	case "Escort_LevelUp_2_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "41");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		SetFunctionTimerCondition("CaravanNearIsland_Over", 0, 0, 2, false);
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
		pchar.quest.CaravanNearIsland_Start.win_condition.l1 = "location";
		pchar.quest.CaravanNearIsland_Start.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
		pchar.quest.CaravanNearIsland_Start.function = "CreateCaravanNearIsland";
		pchar.questTemp.WPU.Escort.LevelUp_2 = "true";
		pchar.questTemp.WPU.Escort = "begin";
		DialogExit();
	break;
	
	case "Escort_LU2_complete":
		switch (sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty))
		{
			case 1:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 10000;
				dialog.text = "ああ、町中があんたの戦いを見てたぜ。商人たちは気の毒だが、まあ仕方ねえ。だが、少なくとも一隻は救えたんだ、 だから一万ペソの報酬は当然のものだ。どうぞ、受け取ってくれ――そして助けてくれて感謝するぜ。";
				link.l1 = "礼を言われる筋合いはねえよ……あの戦いで決定的な勝利を収められなかったのは残念だが、俺にできることは全部やったさ。じゃあな、 "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 2:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 25000;
				dialog.text = "ああ、町中があなたの戦いを見守っていましたよ――そして、実に見事な戦いぶりでした。あの哀れな商人には同情しますが……しかし、あなたがいなければ誰一人として生きて逃げられなかったでしょう。ですから、2万5千ペソの報酬は十分に値するものです。どうぞお受け取りください――そして、ご協力に感謝いたします。";
				link.l1 = "まあ、俺の行動を褒めてくれてありがとな。でも、あれが俺の最高の戦いだったとは思わねえ。 結局一隻失っちまったしな。まあ、運命は運命だ、どうしようもねえさ。じゃあな、 "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 3:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 50000;
				dialog.text = "ああ、町中があんたの戦いを見てたぜ――まさに見事だった！あの汚ねえ海賊どもの艦隊を丸ごとぶっ潰しちまったじゃねえか！これで奴らも思い知っただろうが……もう遅いな。報酬として五万ペソを渡そう――どうか受け取ってくれ。";
				link.l1 = "私の行動を親切に評価してくださり、ありがとうございます！お手伝いできて光栄です。そして今、 "+GetAddress_FormToNPC(NPChar)+"、失礼いたします。";
				link.l1.go = "Escort_LU2_complete_1";
			break;
		}
	break;
	
	case "Escort_LU2_complete_1":
		iTemp = sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty);
		DialogExit();
		Group_DeleteGroup("CaravanShip");
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", iTemp*2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), iTemp);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		CloseQuestHeader("Escort");
		AddCharacterExpToSkill(pchar, "Sailing", iTemp*35);//навигация
		AddCharacterExpToSkill(pchar, "Accuracy", iTemp*50);//меткость
		AddCharacterExpToSkill(pchar, "Cannons", iTemp*50);//орудия
		AddCharacterExpToSkill(pchar, "Grappling", iTemp*35);//абордаж
		AddCharacterExpToSkill(pchar, "Leadership", iTemp*40);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", iTemp*35);//везение
		AddCharacterExpToSkill(pchar, "FencingL", iTemp*35);//лёгкое оружие
		AddCharacterExpToSkill(pchar, "FencingS", iTemp*35);//среднее оружие
		AddCharacterExpToSkill(pchar, "FencingH", iTemp*35);//тяжелое оружие
		AddCharacterExpToSkill(pchar, "Pistol", iTemp*35); //пистоли
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
		case "PortmanQuest_NF":
			dialog.text = "ふむ、それはまずいな。その場合、これ以上俺に任せる仕事はないってことだな。";
			link.l1 = "承知した。さて、私が言いたかったのは……";
			link.l1.go = "node_2";
		break;
		
		//сгоревшее судно
		case "BurntShip2":
			dialog.text = "残念だな、船長……手を貸してくれないとは、惜しいことだ。";
			link.l1 = "それは俺の意思じゃないんだ、旦那。わかってくれよ。じゃあな。";
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;
		
		case "BurntShip4":
			dialog.text = "どうしたんだ、船長！？恥ずかしくないのか！？どうしてそんなことができるんだ！？ 私は自分の仕事をよくわかっている、何年もこの職に就いているんだ。\n保険契約もあるし、保険会社も支払いに応じるつもりだ。それに、保証された金額もなかなか悪くないと断言できるぞ。";
			link.l1 = "どうしたんだ、旦那？火薬庫が爆発して死人まで出たってのに、今度はお前の怠慢で裁判にかけられるってわけか？";
			link.l1.go = "BurntShip5";
		break;
		
		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");
			
			dialog.text = "いや！もちろんそんなことはない！主よ、私の魂をお救いください、さもなくば首が飛ぶところでした。 貨物倉はまったく空っぽでした、主よ感謝します、聖母マリア様、ありがとうございます！\n"+"問題は、その船が……いや、正確には、旦那のものだったということだ。 "+sCapitainId+"、カリブ中でよく知られているんだ。しかも特別注文でヨーロッパで建造され、並外れた特徴を持っているんだぜ。 "+"この船主はやけに威張って、あっちこっちで自慢ばかりしやがったんだ、まったく大馬鹿野郎だよ、神様お許しを……今さらあいつに何て言やいいんだ？いっそ俺が死んじまった方がマシだ、誓ってな……";
			link.l1 = "ああ、なるほど、問題が分かったぜ、確かにな。で、その船の何がそんなに特別だったんだ？ 持ち主がそこまで誇りに思うような、どんな変わった特徴があったんだ？";
			link.l1.go = "BurntShip6";
			
			NPChar.Quest.BurntShip.ShipOwnerName = sCapitainId;
		break;
		
		case "BurntShip6":
			BurntShipQuest_FillStartParams(NPChar);
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "'s wind speed was more than " + NPChar.Quest.BurntShip.ShipNeededValue + " knots. That was the privateer's pride... And now he'd just tell his boys to hang me in the yard. What devil has brought him to our harbor together with that pirate tub...";
				break;
				
				case "turnrate":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "'s maneuverability was more than " + NPChar.Quest.BurntShip.ShipNeededValue + " units. That was the soldier's pride... And now he'd just have me flogged to death. What devil advised him to leave his tub there...";
				break;
				
				case "capacity":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "' had a deadweight of over " + NPChar.Quest.BurntShip.ShipNeededValue + " units. Greed is bad, I'll tell ya. And now he'd just have me quartered in court. What devil advised him to leave his tub there...";
				break;
			}
			
			dialog.text = attrL;
			link.l1 = "「で、波止場の連中は何と言ってる？ここで新しくもう一隻造るのは本当に無理なのか？」";
			link.l1.go = "BurntShip7";
		break;
		
		case "BurntShip7":
			dialog.text = "誰にもできねえよ。俺は近くの島まで行って地元の連中にも聞いてみたんだが、 船大工なら何でもできるって評判の名人がイスラ・テソロにいるらしい。だが、 そのイスラ・テソロがとんでもなく遠いんだ。もう頼れるのはお前みてえな自由船長だけだぜ。 もしかしたらお前がそんな船を見つけてくれるかもしれねえ。他のことは俺が何とかするさ\n"+"私はあなたに十分なお礼をしますし、保険会社も同様に感謝するでしょう。\nこの件は珍しいのですよ。\nあんなに権力のある男を怒らせたい者がいると思いますか？";
			link.l1 = "ああ、それは簡単じゃねえな。で、俺にどれくらい時間があるんだ？";
			link.l1.go = "BurntShip8";
			link.l2 = "いや、相棒、そんなことには関われねえよ。そもそも、そんな条件の船が本当に存在する保証もねえしな。悪いが……";
			link.l2.go = "BurntShip2";
		break;
		
		case "BurntShip8":
			dialog.text = "神に感謝だ、まだ時間はある。船主はヨーロッパへ航海に出て、戻ってくるのは早くても半年後だ。";
			link.l1 = "まあ、なんとかしてやるさ。同じような船を持ってきてやるぜ。だが覚えておけ――ケチな真似をしたら、その場でお前の目の前で燃やしてやるからな！";
			link.l1.go = "BurntShip9";
		break;
		
		case "BurntShip9":
			dialog.text = "何を言いたいんだ、船長？もちろん、時間が必要なのは分かっている――近くの水たまりに浮かぶ適当なボロ船を探してくる話じゃないからな……とにかく船を持ってきてくれれば、全力を尽くすぜ、それは約束する……";
			link.l1 = "そう願いたいな……じゃあ、俺といい知らせを待っててくれ。じゃあな。";
			link.l1.go = "BurntShip9_exit";
		break;
		
		case "BurntShip9_exit":
			attrL = "BurntShipQuest_TimeIsOver_" + NPChar.Id;
			PChar.Quest.(attrL).win_condition.l1 = "Timer";
			PChar.Quest.(attrL).win_condition.l1.date.day = GetAddingDataDay(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.month = GetAddingDataMonth(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.year = GetAddingDataYear(0, 6, 0);
			PChar.Quest.(attrL).function = "BurntShipQuest_TimeIsOver";
			PChar.Quest.(attrL).PortmanId = NPChar.id;
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "speed. The wind speed of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " must be at least " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "turnrate":
					attrL = "manoeuvrability. Manoeuvrability of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " must be no less than " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "capacity":
					attrL = "hold. Hold of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " has to be no less than " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
			}
			
			sTitle = "BurntShipQuest" + NPChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "BurntShipQuest", "1");
			AddQuestUserDataForTitle(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Dat"));
			AddQuestUserData(sTitle, "portmanName", GetFullName(NPChar));
			AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Gen"));
			AddQuestUserData(sTitle, "text", attrL);
			
			NPChar.Quest.BurntShip.LastPortmanName = GetFullName(NPChar); // Запомнм имя
			
			DialogExit();
		break;
		
		// Вариант, когда не уложились в сроки
		case "BurntShip10":
			dialog.text = "何の話をしたかったんだ？";
			link.l1 = "「それで、前の港長はどこにいるんだ、旦那」 "+NPChar.Quest.BurntShip.LastPortmanName+"？俺はあいつに用があるんだ。";
			link.l1.go = "BurntShip11";
		break;
		
		case "BurntShip11":
			dialog.text = "もうここにはいないんだ。想像してみろ――有名人の船を燃やして保険金をせしめたんだよ。その騒ぎを役人たちが片付けている間に、 やつは辞職してヨーロッパへとトンズラした。まったく、とんだ詐欺師じゃねえか？";
			link.l1 = "ああ、その話は聞いたことがある。悪いが、俺は行かなくちゃならねえ。";
			link.l1.go = "BurntShip11_exit";
		break;
		
		case "BurntShip11_exit":
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "2");
			AddQuestUserData(sTitle, "portmanName", NPChar.Quest.BurntShip.LastPortmanName);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		// Не просрочено - проверяем корабль
		case "BurntShip12":
			dialog.text = "何の話をしたかったんだ？";
			link.l1 = "頼まれた通り、珍しい船を持ってきたぜ。さあ、報酬を期待してるからな。";
			link.l1.go = "BurntShip14";
			link.l2 = "「知ってるか、 "+GetFullName(NPChar)+"、まだご要望に合う船は一隻も見つかっていないんだ。この仕事は諦めるしかなさそうだな。 期待に応えられなくて悪かったな……";
			link.l2.go = "BurntShip13";
		break;
		
		case "BurntShip13":
			dialog.text = "残念だな、船長……お前が俺を手伝う気がないとは、惜しいぜ。";
			link.l1 = "それは私の意思でどうこうできることではありません、旦那。ご理解ください。では、失礼します。";
			link.l1.go = "BurntShip13_exit";
		break;
		
		case "BurntShip13_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip14":
			dialog.text = "「おお、本当か！それで、新しい船の名前は何だ？」";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip15";
						}
					}
				}
			}
			
			link.l99 = "失礼する、また後で来るぜ。";
			link.l99.go = "exit";
		break;
		
		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "ああ、船長、俺をがっかりさせなくて本当に嬉しいぜ！なんてこった\n "+GetSexPhrase("立派な若者","「立派なお嬢さん」")+" お前は……本当に俺の命の恩人だ……。頼む、数日後に金を受け取りに来てくれないか？保険の手続きが必要なんだ……。その間に、船の小さな修理でもしておいてくれ――帆を新しくしたり、穴を塞いだり、ケアニングも悪くねえぞ……";
			link.l99 = "俺は、お前が俺を騙そうとしたら船にひどいことをしてやるって約束しただろう。忘れたのか？";
			link.l99.go = "BurntShip16";
		break;
		
		case "BurntShip16":
			dialog.text = "いやいや、とんでもない！俺は約束を守るさ、心配するな。実はな、 新しい船をいわば偽装するために追加の出費がかかると分かっていたから、 前の船の保険金を利子付きで貸し出しておいたんだ。分かってくれるといいんだが…";
			link.l1 = "金が俺の金庫に入ったときに、もっとよく理解できるだろう。\nまた会おうぜ。";
			link.l1.go = "BurntShip16_exit";
		break;
		
		case "BurntShip16_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "3");
			
			NPChar.Quest.BurntShip.TwoDaysWait = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Quest.BurntShip.TwoDaysWait"); // Запомним дату
			
			sTitle = "BurntShipQuest" + NPChar.Id;
			PChar.Quest.(sTitle).over = "yes"; // Завершаем прерывание на время
			
			DialogExit();
		break;
		
		case "BurntShip17":
			dialog.text = "何の話をしたかったんだ？";
			link.l1 = "報酬を受け取りに来たぜ。あんたが必要としている船はまだ俺が持ってる。";
			link.l1.go = "BurntShip18";
		break;
		
		case "BurntShip18":
			dialog.text = "その名前をもう一度教えてくれませんか？昔ほど記憶力がよくなくてね……ご存知の通り、いろいろと面倒が多くて……";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip19_" + i;
						}
					}
				}
			}
			
			link.l99 = "失礼、また後で来る。";
			link.l99.go = "exit";
		break;
		
		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 3;
			rRealShip = GetRealShip(GetCharacterShipType(sld));
			if (sti(rRealShip.Stolen)) cn *= 3;
			
			dialog.text = "「ああ、完璧だ。報酬を渡す準備ができているぞ。」 "+FindRussianMoneyString(cn)+"。それが焼失した船の価値として保険会社が査定した額だ。\n保険金は貸金箱で支払われる――現金じゃない、悪いな。";
			link.l1 = "おいおい、この額じゃ納得できねえな。この船はもっと価値があるはずだぜ。";
			link.l1.go = "BurntShip21";
			link.l2 = "そうだな。力になれて良かったぜ。またな。";
			link.l2.go = "BurntShip20_exit";
			NPChar.Quest.BurntShip.Money = cn;
		break;
		
		case "BurntShip20_exit":
			TakeNItems(pchar, "chest", makeint(sti(NPChar.Quest.BurntShip.Money)/12000));
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip21":
			dialog.text = "何を言ってるんだ、船長！？俺を信じろよ、ちゃんと分かってるんだ。その金があれば、あんな船が二隻は買えるぜ！";
			link.l1 = "俺が預かっておくとするか。なんだか気に入っちまったんだよ……じゃあな。";
			link.l1.go = "BurntShip21_exit";
		break;
		
		case "BurntShip21_exit":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "5");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		//--> миниквесты портмана
		case "PortmanQuest":
			if (hRand(5) == 2)
			{	//квест догнать и передать судовой журнал
				dialog.text = "ある船長が俺の執務室に航海日誌を忘れていったんだ。まったく、うっかり者だぜ！お前にその船長を追いかけて、 日誌を返してきてほしいんだ。";
				link.l1 = "おお、それは楽勝だな……もらっていくぜ！";
				link.l1.go = "PortmanQuest_1";
				link.l2 = "いや、それは俺が引き受けねえ。実際、あいつ自身の問題だぜ。";
				link.l2.go = "node_2";
			}
			else
			{	//квест разыскать украденный корабль
				dialog.text = "そこに停泊していた船が盗まれたんだ。盗まれた船を追跡して取り戻してほしい。";
				link.l1 = "ふむ、さて、俺は調査を始める準備ができてるぜ。";
				link.l1.go = "SeekShip_1";
				link.l2 = "申し訳ないが、盗まれた船を探す仕事には関わらないんだ。";
				link.l2.go = "node_2";
			}
		break;
//-------------------------------- квест доставки судового журнала до рассеяного кэпа ---------------------
		case "PortmanQuest_1":
			dialog.text = "素晴らしい、これが彼の航海日誌だ……本当に助かったよ！船の航海日誌を失うのはとても厄介なことなんだ。 そういう目に遭った船長たちにはいつも同情していたよ……";
			link.l1 = "そりゃあ、本当に心配なことだぜ！さて、そのうっかり者の船長についてもっと詳しく話してくれよ。";
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = "はい、もちろん！名前は "+npchar.quest.PortmansJornal.capName+"、あいつはの船長だ "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName+"Gen"))+" 『』と名付けられた"+npchar.quest.PortmansJornal.shipName+"「。少し前に出航して、向かったのは "+XI_ConvertString("Colony"+npchar.quest.PortmansJornal.city+"Acc")+".";
			link.l1 = "なるほど。よし、そいつを探してくるぜ。さて、報酬の話はどうなってるんだ？";
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName+" 彼自身が支払いをするさ、それが一番都合がいいからな。お前はとにかくできるだけ早く彼に会うことだけ考えろ、 そうすりゃ全てうまくいくぜ。";
			link.l1 = "なるほど。じゃあ、俺は行くぜ……";
			link.l1.go = "exit";
			sTitle = npchar.id + "PortmansBook_Delivery";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "1");
			AddQuestUserDataForTitle(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansJornal.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sCapName2", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			if (GetIslandByCityName(npchar.quest.PortmansJornal.city) != npchar.quest.PortmansJornal.city)
			{
				AddQuestUserData(sTitle, "sAreal", ", which is on " + XI_ConvertString(GetIslandByCityName(npchar.quest.PortmansJornal.city) + "Dat"));
			}			
		break;
		// -------------------------------- квест розыска украденного корабля ----------------------------------
		case "SeekShip_1":
			dialog.text = "素晴らしい！実はな、盗まれた船は有力者の持ち物なんだ。だから俺にとっても非常に重要な案件だぜ。この仕事、 たっぷり報酬を払わせてもらうぞ…";
			link.l1 = "なるほど。その船と盗まれた状況について、もっと詳しく話してくれ。";
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)+" 『という名の"+npchar.quest.PortmansSeekShip.shipName+"「は夜の間に盗まれた」 "+FindRussianDaysString(rand(5)+10)+" 前だ。見張りが殺された。";
			link.l1 = "ふむ……もうかなり遠くへ行ってしまったに違いねえな。足取りも新しくねえ、それが厄介なんだ。";
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = "確かにそうだが、すぐに警報を鳴らす意味は感じなかったんだ。軍艦が奴らに追いつけたかもしれねえが、 ただ船を木っ端みじんにするだけだろう――それじゃ俺の望む結果じゃねえからな。";
			link.l1 = "なるほど。さて、捜索を始めるとするか。運が良けりゃいいんだが。";
			link.l1.go = "exit";
			sTitle = npchar.id + "Portmans_SeekShip";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName+"Acc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansSeekShip.shipName);
		break;

		case "SeekShip_break":
			dialog.text = "残念だが――成功を期待できる状況じゃなかったな。";
			link.l1 = "ああ、船が盗まれてから随分と時が経ったな。";
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = "まあ、とにかく手伝ってくれて感謝するよ、君の努力は我々が期待したほど実を結ばなかったがな。";
			link.l1 = "俺はできることは全部やったんだ……";
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//если кэп-вор ещё жив - убираем его
			if (cn > 0)
			{
				characters[cn].LifeDay = 0; 
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "7");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
			ChangeCharacterComplexReputation(pchar,"nobility", -7);
		break;	

		case "SeekShip_good":
			if (npchar.quest == "SeekShip_sink")
			{
				dialog.text = "素晴らしい！まあ、これが本当に盗まれた船じゃない気もするが……そんなことどうでもいい！俺がもらうぜ。";
				link.l1 = "ああ、確かに……";
				//npchar.quest.money = makeint(sti(npchar.quest.money) / 4); //снижаем оплату
				ChangeCharacterComplexReputation(pchar,"nobility", 5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 50);
                AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 20);
			}
			else
			{
				dialog.text = "素晴らしい！君のおかげで大いに助かったよ。どれほど大変だったか想像もつかない。";
				link.l1 = "ああ、確かに……";
				ChangeCharacterComplexReputation(pchar,"nobility", 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
                AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = "報酬を支払う準備ができている。内容は\n " + makeint(sti(npchar.quest.money)) + " ドゥブロン金貨で支払う。残念だが、それ以上は払えない。";
			link.l1 = "さて、もう十分だ。ありがとう、よろしく頼む。";
			link.l1.go = "exit";
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.money));
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "6");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		break;

		//------------------------------> инфа по базе квествых кэпов
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery  #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		//ПРИМЕР: в конце метода  void SetCapitainFromCityToSea(string qName)
		case "CapitainList":
			if (sti(npchar.quest.qty) > 0)
			{
				dialog.text = "登録されている船長が何人かいる。誰か特に気になる者がいるのか？";
				makearef(arCapBase, npchar.quest.capitainsList); 
				for (i=0; i<sti(npchar.quest.qty); i++)
				{
    				arCapLocal = GetAttributeN(arCapBase, i);
					sCapitainId = GetAttributeName(arCapLocal);
					sld = characterFromId(sCapitainId);
					attrL = "l" + i;
					link.(attrL) = GetFullName(sld) + ", captain of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Gen")) + " '" + sld.Ship.name + "'.";
					link.(attrL).go = "CapList_"+attrL;
				}
			}
			else
			{
				dialog.text = "あなたに関心を持たせるような船長は私の名簿にはいません。";
				link.l1 = "なるほど。情報をありがとう。";
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("さてと……よし！そこだ！ ","あっは……あっは！そこだ！ ","「わかった、じゃあな。」 ")+"Captain "+GetFullName(sld)+" "+arCapLocal.date+" 年に我々の港を出港し、へ向かった "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "ありがとうございます。もう一度リストを確認したいのですが……";
			link.l1.go = "CapitainList";
			link.l2 = "よし、それだけだ。他の船長には興味ねえ。";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Voc")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l1":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  1);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("さてと……うん、あった！そこだ！ ","あっは……あっは！そこだ！ ","「よし、そうしよう。」 ")+"Captain "+GetFullName(sld)+" "+arCapLocal.date+" 年に我々の港を出港し、へ向かった "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "ありがとうございます。もう一度リストを確認したいのですが……";
			link.l1.go = "CapitainList";
			link.l2 = "よし、それだけだ。他の船長には興味ねえ。";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l2":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  2);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("さてと、どれどれ……あっ！そこだ！ ","あっは……あっは！そこだ！ ","「よし、そうしよう。」 ")+"Captain "+GetFullName(sld)+" "+arCapLocal.date+" 年に我々の港を出港し、～へ向かった "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "ありがとうございます。もう一度リストを確認したいのですが……";
			link.l1.go = "CapitainList";
			link.l2 = "よし、それで全部だ。他の船長には興味ねえよ。";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l3":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  3);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("さて、どれどれ……あっ！そこだ！ ","あっは……あっは！そこだ！ ","「わかった、それじゃあ。」 ")+"Captain "+GetFullName(sld)+" "+arCapLocal.date+" 年に我々の港を出港し、へ向かった "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "ありがとうございます。もう一度一覧を確認したいのですが……";
			link.l1.go = "CapitainList";
			link.l2 = "よし、それだけだ。他の船長には興味ねえ。";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l4":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  4);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("さてと……よし！そこだ！ ","あっは……あは！そこだ！ ","「よし、そうしよう。」 ")+"Captain "+GetFullName(sld)+" "+arCapLocal.date+" 年に我々の港を出港し、へ向かった "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "ありがとうございます。もう一度リストを確認したいのですが……";
			link.l1.go = "CapitainList";
			link.l2 = "よし、それだけだ。他の船長には興味ねえ。";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		//<--------------------------- инфа по базе квествых кэпов

		case "ShipStock_1":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobTakeShip" && !CheckAttribute(npchar, "quest.HWICHoll"))
			{
			dialog.text = "聞こう――どの船で、どれくらいの期間だ？";
    		Link.l1 = "ルーカス・ローデンブルフに頼まれて来たんだ。ここに俺の船を無料で停泊できるって言われたぜ。";
    		Link.l1.go = "ShipStock_HWICHoll";
			DelLandQuestMark(npchar);
			break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoPortoffice" && !CheckAttribute(npchar, "quest.HWICEng"))
			{
			dialog.text = "聞こう――どの船で、どれくらいの期間だ？";
    		Link.l1 = "リチャード・フリートウッドに頼まれて来た。ここに俺の旗艦を1万ペソで停泊させていいと言われたんだ。";
    		Link.l1.go = "ShipStock_HWICEng";
			break;
			}
            if (sti(NPChar.Portman) >= 3 || CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip"))
			{
                dialog.text = "そう、その通りだ。しかし残念ながら、今はお前の船を受け入れることはできねえ。空いてるドックがねえんだ。";
    			Link.l1 = "それは残念だ。";
    			Link.l1.go = "exit";
			}
            else
            {
    			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "「で、どの船をここに置いていくつもりなんだ？」";
	    			for(i=1; i<COMPANION_MAX; i++)
					{
						cn = GetCompanionIndex(PChar, i);
						if(cn > 0)
						{ // hasert со сторожем.
							chref = GetCharacter(cn);
							if (!GetRemovable(chref)) continue;							
							attrL = "l"+i+COMPANION_MAX;
							Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockMan22_" + i;

						}
					}
	    			Link.l17 = "気にするな、ありがとう。";
	    			Link.l17.go = "exit";
    			}
    			else
    			{
					dialog.text = "ふむ……お前の船は一隻も見当たらねえな。";
	    			Link.l1 = "ちょっと寄港の可能性について伺いたかったんだ。";
	    			Link.l1.go = "exit";
				}
			}
		break;

		case "ShipStock_2":
			// --> andre270925 оставаил тут комментом старый код чтобы забрать куски перевода, если нужно
      //       chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			// if (CheckAttribute(pchar, "questTemp.GS_BelizSkidka") && npchar.id == "Beliz_portman" && !CheckAttribute(npchar, "DontNullShipBeliz") && sti(RealShips[sti(chref.Ship.Type)].Class) > 1)	// В Белизе скидка 50%
			// {
			// 	NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref)/2;
			// }
			// else
			// {
			// 	if (MOD_SKILL_ENEMY_RATE >= 6) NPChar.MoneyForShip = MOD_SKILL_ENEMY_RATE/2*GetPortManPriceExt(NPChar, chref); // для высокой сложности - 5x цена
			// 	else NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref);
			// }
			// dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName)+" 「」"+chref.Ship.Name+"「」、クラス "+RealShips[sti(chref.Ship.Type)].Class+"、係留費用は "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+" 月ごと、支払いは一ヶ月前払い。";
			// Link.l1 = "「ああ、それで構わねえぜ。」";
			// if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			// {
			//     Link.l1.go = "ShipStock_3";
			// }
			// else
			// {
      //           Link.l1.go = "ShipStock_NoMoney";
			// }
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			PortmanCalculatePrices(NPChar, chref);
			dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " 「」" + chref.Ship.Name + "「」、クラス " + RealShips[sti(chref.Ship.Type)].Class +
                     "、停泊費 " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + " 月ごとに、前払いです。";
			dialog.Text = dialog.Text + " 士官と乗組員に任せれば、彼らと一緒に " + FindRussianMoneyString(sti(NPChar.MoneyForShip) + sti(NPChar.MoneyForCrew));

			Link.l1 = "ああ。それで構わねえよ。";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip)) Link.l1.go = "ShipStock_3";
			else  Link.l2.go = "ShipStock_NoMoney";

			Link.l2 = "ああ、それでいいぜ。船長と乗組員に任せておけ\n";
			if (sti(Pchar.Money) >= (sti(NPChar.MoneyForShip) + sti(NPChar.MoneyForCrew))) Link.l2.go = "ShipStock_4";
			else Link.l2.go = "ShipStock_NoMoney";

			Link.l3 = "いや、気が変わった。";  
			Link.l3.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "「そして、お前が必要な額を集め次第、俺にも都合がいいぜ。」";
			Link.l1 = "おっと……また後で来るぜ。";
			Link.l1.go = "exit";
		break;

		case "ShipStock_3":
		 	LeaveShipInPort(NPChar, GetCharacter(sti(NPChar.ShipToStoreIdx)));
			dialog.text = "わかった。必要なときはいつでも自分の船を引き取っていいぞ。";
			Link.l1 = "ありがとう。";
			Link.l1.go = "exit";
		break;

		case "ShipStock_4":
		 	LeaveShipInPortWithCrew(NPChar, GetCharacter(sti(NPChar.ShipToStoreIdx)));
			dialog.text = "わかった。必要なときはいつでも自分の船を引き取っていいぞ。";
			Link.l1 = "ありがとう。";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
            ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
	            {
	                dialog.text = "どの船を奪うつもりだ？";
	                cn = 1;
	                for(i=1; i<MAX_CHARACTERS; i++)
					{
						makeref(chref, Characters[i]);
						if (CheckAttribute(chref, "ShipInStockMan"))
						{    
							if (chref.ShipInStockMan == NPChar.id)
							{
								attrL = "l"+cn;
								if(HasSubStr(chref.id, "ShipInStockMan_"))											  
								{ 
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
								Link.(attrL).go = "ShipStockManBack22_" + i; 
								}
								else
								{  
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "' and my officer " + GetFullName(chref) + ".";
								Link.(attrL).go = "ShipStockManBack11_" + i;
								}
								cn++;
							}
						}
					}
	
	    			Link.l99 = "いや、気が変わった。";
	    			Link.l99.go = "exit";
				}
				else
				{
	                dialog.text = "もう一隻の船を受け入れる余裕はあるか？";
	    			Link.l1 = "ああ、そうだったな。ありがとう。";
	    			Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "ふむ。お前の旗艦が港に見当たらねえな。ここでしか船を引き取ることはできねえぜ。";
    			Link.l1 = "わかった、後で迎えに来るぜ。";
    			Link.l1.go = "exit";
			}
		break;

		case "ShipStockManBack":
			// Лимит офицеров не позволяет забрать  
			if (AttributeIsTrue(NPChar, "StoreWithOff") && FindFreeRandomOfficer() < 1 ) {
				dialog.text = "船長、あなたの乗組員にはもう一人士官を迎える余地がないようです。";  
				link.l1 = "ふむ……それなら、また後で来るとしよう。";  
				link.l1.go = "exit";  
				break;  
			}
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			
			// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
			if (CheckAttribute(chref, "quest.Mutiny.date")) {
				dialog.text = "さて……この船は港を出たのは "+chref.quest.Mutiny.date+".";
				link.l1 = "「“出て行った”とはどういう意味だ？彼女はここ、波止場にいるはずだろう！」";
				link.l1.go = "ShipStockManMutiny";
				break;
			}
			// <--
            NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);
			if (sti(NPChar.MoneyForShip) > 0)
			{
			    dialog.Text = "船を受け取りたいのか？係留料がまだ残っているぞ "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+".";
			}
			else
			{
				dialog.Text = "「受け取りか？」";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "「ああ。」";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "いや、やっぱり考え直した。";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockManBack2": // hasert новый кейс для сторожа.
			if (sti(NPChar.StoreWithOff))
			{   
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			if(CheckAttribute(chref, "DontNullShip"))
			{
				DeleteAttribute(chref, "DontNullShip");
				DeleteAttribute(NPChar, "DontNullShipBeliz");
			}
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));

			NPChar.Portman	= sti(NPChar.Portman) - 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			}
			else
			{   
			dialog.Text = "「お前の士官のうち、誰に渡せばいいんだ？」";
			int _curCharIdx;
			int q = 0;
			int nListSize = GetPassengersQuantity(pchar);
			for(i=0; i<nListSize; i++)
				{
				_curCharIdx = GetPassenger(pchar,i);
				sld = GetCharacter(_curCharIdx);
					if (_curCharIdx!=-1)
					{
						ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;

						if (!CheckAttribute(sld, "CompanionDisable"))
					    {
							if (!ok && GetRemovable(&characters[_curCharIdx]))
							{
								attrL = "l"+i;
								sProf = "";
								if (IsOfficer(sld)) sProf += " (vanguard)";
								if (sti(pchar.Fellows.Passengers.navigator) == sti(sld.index)) sProf += " (navigator)";
								if (sti(pchar.Fellows.Passengers.boatswain) == sti(sld.index)) sProf += " (boatswain)";
								if (sti(pchar.Fellows.Passengers.cannoner) == sti(sld.index)) sProf += " (cannoneer)";
								if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index)) sProf += " (surgeon)";
								if (sti(pchar.Fellows.Passengers.carpenter) == sti(sld.index)) sProf += " (carpenter)";
							    if (sti(pchar.Fellows.Passengers.treasurer) == sti(sld.index)) sProf += " (purser)";
								Link.(attrL)	= GetFullName(&characters[_curCharIdx]) + sProf;
								Link.(attrL).go = "ShipStockManBack2_" + i;
								q++;
							}
						}
					}
				}
			attrL = "l"+nListSize;
			if (q == 0)
				{
				Link.(attrL) = RandSwear() + "I forgot to bring an officer with me for this ship.";
				Link.(attrL).go = "exit";
				}
			else
				{
				Link.(attrL) = "No, I've changed my mind..";
				Link.(attrL).go = "exit";
				}
			}
		break;
		
		//--> Jason Голландский гамбит
		case "ShipStock_HWICHoll":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "ああ、わかっている。しかし、無料で係留できるのは一隻だけなんだ。だから、まず自分の艦隊の整理をしてから、 また来てくれ。";
				link.l1 = "よし、旗艦だけ連れて行くぜ。";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "はいはい、わかっています。ローデンブルク旦那の命令により、あなたの船を保管として受け入れ、 滞在中ずっと当直士官をつけます。ここに署名を……そしてここにも……";
				link.l1 = "よし……これで全ての手続きは済んだな？";
				link.l1.go = "ShipStock_HWICHoll_1";	
			}
		break;
		
		case "ShipStock_HWICHoll_1":
			dialog.text = "ああ。もうお前の船のことは心配いらねえ――こっちでしっかり面倒を見るぜ。ローデンブルク旦那のところに戻っていいぞ。";
			link.l1 = "ありがとうございます。さようなら。";
			link.l1.go = "exit";	
			npchar.quest.HWICHoll = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "ShipStock_HWICEng":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "はいはい、わかっています。しかし、無料で係留できるのは一隻だけです。ですから、艦隊の整理を済ませてから、 もう一度来てください。";
				link.l1 = "よし、旗艦だけを連れていくぜ。";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "はい、もちろんです。お金は持っていますか？";
				if(makeint(Pchar.money) >= 10000)
				{
					link.l1 = "もちろん。はい、どうぞ。";
					link.l1.go = "ShipStock_HWICEng_1";	
				}
				else
				{
					link.l1 = "いいや。すぐ戻る。";
					link.l1.go = "exit";	
				}
			}
		break;
		
		case "ShipStock_HWICEng_1":
			dialog.text = "承知した。あなたの船はこちらで管理し、滞在中はずっと当直士官を付けておく。";
			link.l1 = "ありがとう！";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -10000);
			npchar.quest.HWICEng = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Fleetwood"), "questmarkmain");
		break;
		//<-- Голландский гамбит
		case "Escort_companion":
			dialog.text = "何かご用ですか、船長？";
			link.l1 = "いや、何もない。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Escort_companion";
		break;
		
		// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
		case "ShipStockManMutiny":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			dialog.text = "あなたの士官 "+GetFullName(chref)+" 通知済"+NPCharSexPhrase(chref,"","")+" 俺にそれを "+NPCharSexPhrase(chref,"彼","彼女")+" お前の命令で俺は海に出なきゃならなかった。反対はしなかったぜ "+NPCharSexPhrase(chref,"彼","彼女")+".";
			link.l1 = "くそっ！そんな命令はなかったはずだ！あんな野郎に俺の船を任せるんじゃなかったぜ！まあ、どうでもいいさ、 どうせ損はもうどうにもならねえしな。";
			link.l1.go = "ShipStockManMutiny1";
			// вот тут можно микроквестик сделать
			//link.l2 = "なんてこった……やったのか "+NPCharSexPhrase(chref,"彼","彼女")+" どこへ行ったか、もしかして教えてくれないか？";
			//link.l2.go = "ShipStockManMutiny2";
		break;
		
		case "ShipStockManMutiny1":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.lifeday = 0;

			dialog.text = "「申し訳ない」 "+GetAddress_Form(NPChar)+"。部下にはもっと注意を払うべきだ。";
			link.l1 = "分かってるさ、俺はバカだ。じゃあな、 "+GetAddress_Form(NPChar)+".";
			link.l1.go = "exit";
		break;
		// <--
		
		// уникальные корабли и легендарные капитаны -->
		case "UniqueShips":
			dialog.text = "この群島で特別な船やそれを託された者たちが目立たずにいることはできん。しかし、この情報は相当な価値があるゆえ、 そう簡単には渡せんのだ。";
			if (sti(pchar.Money) >= 25000)
			{
				link.l1 = "承知しました。誠意を示すために2万5千ペソで十分でしょうか？";
				link.l1.go = "UniqueShips_2";
			}
			else
			{
				link.l1 = "わかった、また今度だな。";
				link.l1.go = "node_2";
			}
		break;
		
		case "UniqueShips_2":
			dialog.text = "確かに、それで問題ありません。どの船にご興味がありますか？";
			if (GetDLCenabled(DLC_APPID_4) && !CheckAttribute(pchar, "questTemp.SantaMisericordia_InfoPU") && CharacterIsAlive("SantaMisericordia_cap"))
			{
				link.l1 = "ガレオン『"+GetShipName("「聖なる慈悲」")+"「。」";
				link.l1.go = "UniqueShips_SantaMisericordia";
			}
			if (GetDLCenabled(DLC_APPID_5) && !CheckAttribute(pchar, "questTemp.LadyBeth_InfoPU") && CharacterIsAlive("LadyBeth_cap"))
			{
				link.l2 = "哨戒用スノー『"+GetShipName("ベス嬢")+"「。」";
				link.l2.go = "UniqueShips_LadyBeth";
			}
			if (GetDLCenabled(DLC_APPID_6) && !CheckAttribute(pchar, "questTemp.Memento_InfoPU") && CharacterIsAlive("Memento_cap"))
			{
				link.l3 = "ブリッグ『"+GetShipName("Memento")+"「。」";
				link.l3.go = "UniqueShips_Memento";
			}
			if (GetDLCenabled(DLC_APPID_6) && !CheckAttribute(pchar, "questTemp.Amsterdam_InfoPU"))
			{
				link.l4 = "「カンパニー旗艦『」"+GetShipName("Amsterdam")+"「。」";
				link.l4.go = "UniqueShips_Amsterdam";
			}
			link.l99 = "十分に分かったと思う。";
			link.l99.go = "node_2";
		break;
		
		case "UniqueShips_SantaMisericordia":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "1");
			pchar.questTemp.SantaMisericordia_InfoPU = true;
			dialog.text = "ホーリー・マーシー号は、エスコリアルからヨーロッパ経由で派遣され、スペイン植民地を監督している。 その船長アラミダ閣下は、スペイン王室に仕える名高き忠臣であり、腐敗や犯罪に容赦なく立ち向かう闘士、 そしてカトリック信仰の狂信者として知られている。ホーリー・マーシー号は植民地間を巡航し、 ハバナを起点にしてまたハバナへ戻る航路を取り、任務だけに集中している。\n各港では、アラミダは数日、時にはそれ以上滞在するという。その間、彼が街中で姿を見せることもあるらしいが、 地元民はそうした遭遇をあまり望んでいない――スペイン人たちの間で、旦那はただ恐れと畏敬の念を抱かせる存在なのだ。\nホーリー・マーシー号の乗組員は、アラミダ自らが選び抜いた経験豊富で忠実な者たちばかりだ。 誰もが祖国と船長のために命を賭ける覚悟を持っている。フェルナンド閣下は、 ホーリー・マーシー号が決して敵に奪われてはならぬと命じたとも言われており、万が一乗り込まれて絶体絶命となれば、 船を敵の手に渡すよりも海の底に沈める覚悟だという噂がささやかれている。";
			link.l1 = "ありがとうございます。";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_LadyBeth":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "2");
			pchar.questTemp.LadyBeth_InfoPU = true;
			dialog.text = "レディ・ベスはまさに絶世の美女だ。イングランドの海事技術の粋を集めた傑作で、 元王立海軍士官アルバート・ブラックウッドが指揮している。実際、あれほど見事に脱走できる者はそうはいない！ 彼は軍務を捨て、輝かしい経歴を台無しにし、軍艦を盗み出した――すべては財宝探しのためだ！\nしかも、その甲斐はあった。すでにバルバドスの半分を買えるほどの財宝を手に入れているが、まだ満足していない。 もし海で彼に出くわしても――追いかけようなんて思うな。あの船は上等すぎるし、船長は経験豊富で用心深い。 最近ブラックウッドはカイマンに入り浸っていて、昼夜問わず穴を掘り、人足を死ぬまで働かせている。 もし様子を見に行くなら――六十人以上の手勢と良い火器を揃えていけ……いや、それでも足りないかもしれん\nお前が銃の扱いに自信があることを願うぞ。なぜならフォックス大佐率いる元海兵隊の一団も一緒に脱走したからだ。 奴らはプロだ、ただのゴロツキとは訳が違う。そして絶対にフランスの港で彼を襲うな――あそこでは後ろ盾と庇護者がいて、発見物の分け前も渡しているのだからな。";
			link.l1 = "誠にありがとうございます。";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_Memento":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "3");
			pchar.questTemp.Memento_InfoPU = true;
			dialog.text = "『メメント』――本物の海賊伝説だ。モーティマー・グリムが船長を務める黒いブリッグだぜ。\n"+"グリムは奴隷商人だけを狙うんだ。奴隷たちを解放し、死刑囚も金貨で買い取るって話さ。立派な大義――裏の事情を知らなければな。\n"+"人間の積み荷を運んでいなけりゃ、グリムは手を出さねえ。変わり者だが、筋は通してる。だが、 船倉に奴隷を積んでるなら……水平線に黒い帆を見かけねえよう祈るんだな。\n"+"『メメント』号は海賊の隠れ家の間を航行しているが、滅多に港に寄港しない。乗組員は何ヶ月も船上で暮らし、 まるで陸に足を踏み入れるのを恐れているかのようだ。かつてこの船が恐ろしい疫病を生き延びたという噂があり――だからこそ、この乗組員たちはなかなか死なないのだという。\n"+"奴らに挑むつもりなら、大砲をもっと積んでいけ。「メメント号」に乗り込むのはほとんど不可能だ――乗組員どもはまるで憑りつかれたように戦い、死を恐れていない。奴らを倒す唯一の方法は、 船を木っ端みじんに砲撃して隠れ家を奪うことだ。破片は怖がらねえが、ぶどう弾の直撃となりゃ話は別だぜ。\n"+"幸運を祈る。死を忘れるな。";
			link.l1 = "ありがとうございます。";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_Amsterdam":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "4");
			pchar.questTemp.Amsterdam_InfoPU = true;
			dialog.text = "名高いオランダ西インド会社の旗艦。この船についてはすべてが秘密のベールに包まれている。 指揮を執るのはヘンドリック・ファン・ドーン、キュラソーの海軍登記部門の責任者であり、極めて有能な男だ。 彼は最も裕福で影響力のある船長たちにとってかけがえのない働きをしている。彼らの仲間入りを果たせば、 さらに多くのことを知ることができるだろう。";
			link.l1 = "誠にありがとうございます。";
			link.l1.go = "node_2";
		break;
		
		// уникальные корабли и легендарные капитаны <--
	}
}

void SetJornalCapParam(ref npchar)
{
	//созадем рассеянного кэпа
	ref sld = GetCharacter(NPC_GenerateCharacter("PortmansCap_" + npchar.index, "", "man", "man", 20, sti(npchar.nation), -1, true, "citizen"));
	SetShipToFantom(sld, "trade", true);
	sld.Ship.Mode = "trade";
	SetCaptanModelByEncType(sld, "trade");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "PortmansCap";
	sld.DeckDialogNode = "PortmansCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	//в морскую группу кэпа
	string sGroup = "PorpmansShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansJornal"; //личный флаг квеста для портмана
	npchar.quest.PortmansJornal.capName = GetFullName(sld); //имя кэпа
	npchar.quest.PortmansJornal.shipName = sld.Ship.name; //имя корабля
	npchar.quest.PortmansJornal.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название корабля
	npchar.quest.PortmansJornal.city = SelectNotEnemyColony(npchar); //определим колонию, куда ушел кэп
	sld.quest = "InMap"; //личный флаг рассеянного кэпа
	sld.quest.targetCity = npchar.quest.PortmansJornal.city; //продублируем колонию-цель в структуру кэпа
	sld.quest.firstCity = npchar.city; //капитану знать откуда вышел в самом начале
	sld.quest.stepsQty = 1; //количество выходов в море
	sld.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 150) + (sti(pchar.rank)*150); //вознаграждение
	Log_TestInfo("The absent-minded cap " + sld.id + " went to: " + sld.quest.targetCity);
	//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
	string sTemp = GetArealByCityName(npchar.city);
	sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName) + " '" + npchar.quest.PortmansJornal.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "jornal"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "PortmansBook_Delivery"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "PortmansBook_Delivery"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
//проверить список отметившихся квестовых кэпов
int CheckCapitainsList(ref npchar)
{
	int bResult = 0;
	if (!CheckAttribute(npchar, "quest.capitainsList")) return bResult;
	aref arCapBase, arCapLocal;
    makearef(arCapBase, npchar.quest.capitainsList);
    int	Qty = GetAttributesNum(arCapBase);
	if (Qty < 1) return bResult;
	string sCapitainId; 
	for (int i=0; i<Qty; i++)
    {
    	arCapLocal = GetAttributeN(arCapBase, i);
        sCapitainId = GetAttributeName(arCapLocal);
    	if (GetCharacterIndex(sCapitainId) > 0) //если ещё жив
    	{
			bResult++;			
    	}
		else
		{
			DeleteAttribute(arCapBase, sCapitainId);
			i--;
			Qty--;
		}
    }
	if (bResult > 5) bResult = 5;
	return bResult;
}

void SetSeekShipCapParam(ref npchar)
{
	//создаем кэпа-вора
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCap_" + npchar.index, "", "man", "man", Rank, PIRATE, -1, true, "soldier"));
	SetSeekCapShip(sld);
	sld.Ship.Mode = "pirate";
	SetCaptanModelByEncType(sld, "pirate");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SeekCap";
	sld.DeckDialogNode = "SeekCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansSeekShip"; //личный флаг квеста для портмана
	npchar.quest.PortmansSeekShip.capName = GetFullName(sld); //имя кэпа-вора
	npchar.quest.PortmansSeekShip.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.PortmansSeekShip.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.PortmansSeekShip.shipTape = RealShips[sti(sld.Ship.Type)].basetype; //тип украденного корабля
	npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 10) + (sti(pchar.rank)*5); //вознаграждение
	// npchar.quest.chest = 12-sti(RealShips[sti(sld.Ship.Type)].Class); //в сундуках
	sld.quest = "InMap"; //личный флаг кэпа-вора
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Thieving cap " + sld.id + " sailed out of: " + sld.city + " and went to: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, откуда кэп-вор спер корабль
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " '" + npchar.quest.PortmansSeekShip.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+3; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на абордаж
	string sTemp = "SeekShip_checkAbordage" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkAbordage";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на потопление без абордажа
	sTemp = "SeekShip_checkSink" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_sink";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkSink";
	pchar.quest.(sTemp).CapId = sld.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "robber"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "Portmans_SeekShip"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "Portmans_SeekShip"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestPortman_GenerateGem() // камни
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";	
		break;
		case 1:
			itemID = "jewelry2"; 
		break;
		case 2:
			itemID = "jewelry3"; 
		break;
		case 3:
			itemID = "jewelry3"; 
		break;
		case 4:
			itemID = "jewelry5"; 
		break;
		case 5:
			itemID = "jewelry6"; 
		break;
	}
	return itemID;
}

// --> Jason, новые мини-квесты
string findCurrentCity1(ref NPChar)//выбираем целевой город 1
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}

string findCurrentCity2(ref NPChar)//выбираем целевой город 2
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(hrand(howStore-1)-3)];
	return colonies[nation].id;
}

string findCurrentCity3(ref NPChar)//выбираем целевой город 3
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(hrand(howStore-1)-7)];
	return colonies[nation].id;
}

int Escort_ShipType()
{
	int iShipType;
	switch (rand(2))
	{
		case 0: iShipType = SHIP_FLEUT; 	break;
		case 1: iShipType = SHIP_GALEON_L; 	break;
		case 2: iShipType = SHIP_PINNACE;	break;
	}
	return iShipType;
}
//<-- новые мини-квесты



void SetSeekCapShip(ref _chr)
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) < 27) iRank = 3;
	if (sti(pchar.rank) >= 27) iRank = 4;
	
	int iShip = SHIP_WAR_TARTANE;
	switch (iRank)
	{
		case 0:
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 1:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break; 
		case 2:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 3:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 4:  
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY))));
		break;
	}
	
	_chr.Ship.Type = GenerateShipExt(iShip, true, _chr);
	SetRandomNameToShip(_chr);
    SetBaseShipData(_chr);
    SetCrewQuantityFull(_chr);
    Fantom_SetCannons(_chr, "pirate");
    Fantom_SetBalls(_chr, "pirate");
	Fantom_SetUpgrade(_chr, "pirate");
	Fantom_SetGoods(_chr, "pirate");
}
