int iDiplomatPseudoGlobal;

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iSumm = 0;
	string s1;
	
	if (!CheckAttribute(npchar, "PatentPrice"))
    {
        npchar.PatentPrice = (8000 + rand(6) * 1000);
    }
    int i;
    string attrLoc;
	ref    sld;
	
    attrLoc   = Dialog.CurrentNode;
    
    if (findsubstr(attrLoc, "SetNationPatent_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.nation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "patent_2";
 	}
 	
 	if (findsubstr(attrLoc, "SetNationLicence_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceNation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "NationLicenceType";
 	}

 	if (findsubstr(attrLoc, "NationLicenceType_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceType = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "NationLicenceType2";
 	}
 	
 	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
        npchar.quest.relation      = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
		    Dialog.CurrentNode = "RelationYet";
		}
		else Dialog.CurrentNode = "RelationAny_Done";
 	}
 	
 	if (findsubstr(attrLoc, "CityPay_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "CityInfo";
 	}
 	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "また会えて嬉しいぞ。";
			link.l1 = "またお前の助けが必要だ。";
			link.l1.go = "relation";
			link.l2 = "俺は行くぜ。";
			link.l2.go = "exit";

			// генератор  "Найденные документы"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))			
			{
				link.l4 = "取引を持ちかけたいんだ。"link.l4.go ="D_ShipLetters_1"; 
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}			

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "自己紹介させてもらおう。俺はここのどの総督にも口利きできる男だ。もちろんタダじゃねえが、 俺の腕は値段以上の価値があるぜ。払ったことを後悔はさせねえよ。";
				link.l1 = "面白いな。続けてくれ。";
				link.l1.go = "relation";
				link.l2 = "次の機会にしよう。";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}
			
			NextDiag.TempNode = "First time";
		break;

		//*************************** Генератор - "You've found shipping papers." **************		
		case "D_ShipLetters_1":
			dialog.text = "条件は何だ？";
			s1 = "By a lucky chance, I've found a legit package of the ship documents. Is anyone looking for them?";
			s1 = s1 + "The vessel is still sailing and in the register so don't worry. That stupid owner has just lost it";
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = "Let me see it! Yes, the markers here are actual. You are a lucky "+ GetSexPhrase("man","woman") +"! ";
			s1 = s1 + "I just need a package like this and I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What would you say?";
			dialog.text = s1;
			link.l1 = "なんて王家のご寛大さだ！もちろん賛成するぜ！";
			link.l1.go = "D_ShipLetters_3";
			link.l2 = "いやだ、取引はしねえ。";
			link.l2.go = "exit";
		break;
		case "D_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "relation":
			dialog.text = "どうやってお前を助けられるか見てみよう。";
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l3 = "俺はイングランドと和解したいんだ。";
				link.l3.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l1 = "フランスと和解したい。";
				link.l1.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l2 = "スペインと和解したい。";
				link.l2.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "俺はオランダと和解したいんだ。";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "俺は密輸業者たちと和解したいんだ。";
				Link.l5.go = "Contraband";
            }
            Link.l8 = "私掠許可証が必要だ。";
			Link.l8.go = "patent_0";
			
			Link.l9 = "取引許可証は持ってるか？";
			Link.l9.go = "Licence";
			
			if (isHeroOwnCity(true))
			{
				Link.l10 = "植民地の所有権について質問がある。";
				Link.l10.go = "City_Buy";
			}
			
			link.l99 = "そうだな、俺が自分でやったほうがいいだろう。";
			link.l99.go = "exit";
		break;
		
		case "Licence":
			dialog.text = "俺はいつもいろんな時代の免許を持ってるぜ。どこの国の免許が欲しいんだ？";
		    link.l1 = "イングランドの";
			link.l1.go = "SetNationLicence_0";
		    link.l2 = "フランスの";
			link.l2.go = "SetNationLicence_1";
		    link.l3 = "スペインの";
			link.l3.go = "SetNationLicence_2";
		    link.l4 = "オランダの";
			link.l4.go = "SetNationLicence_3";
			link.l9 = "そうだな、俺が自分で片付けたほうがいいだろう。";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType":
        	dialog.text = "「時代？」";
		    link.l1 = "30日";
			link.l1.go = "NationLicenceType_30";
		    link.l2 = "６０日";
			link.l2.go = "NationLicenceType_60";
		    link.l3 = "90日";
			link.l3.go = "NationLicenceType_90";
			link.l9 = "考えが変わった。";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType2":
			iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
        	dialog.text = "つまり、取引許可証は"+XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name+"Gen")+" のため "+sti(npchar.LicenceType)+" 日数、価格は "+FindRussianMoneyString(iSumm)+".";
		    link.l1 = "同意する。";
		    if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = "気が変わった。";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType3":
            iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
			dialog.text = "ほら、これだ。港に入るときは友好的な旗を揚げるのを忘れるな。\nそれから、巡回隊が許可証の日付を確認することもあるから気をつけろよ。";
			link.l9 = "感謝する。";
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;
		
        case "No_money":
			dialog.text = "素晴らしい！金が十分に集まったらまた来い。";
			link.l1 = "「いいだろう。」";
			link.l1.go = "exit";
		break;
		
        case "patent_0":
			dialog.text = "素晴らしい。まずは国への忠誠を証明しなければならん"+" その優れた働きによってだ。どの総督のところへ行っても"+//NationNameGenitive(sti(NPChar.nation))+" 彼の任務をいくつか達成すれば、免許を与えてくれるだろう。";
			link.l1 = "「教えてくれ、 "+GetAddress_FormToNPC(NPChar)+"「この面倒な形式を回避する方法はないのか？」";
			link.l1.go = "patent_1";
			link.l2 = "「さらばだ」 "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_1":
			dialog.text = "賄賂ってことか！？俺に自分で免許を作らせたいのか？";
			link.l1 = "「その通りだ！」";
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
            {
			    link.l1.go = "patent_2_give";
			}
			else
			{
                link.l1.go = "patent_2_none";
			}
			link.l2 = "いいや。さらばだ、 "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_2_none":
			dialog.text = "俺にはそんなコネはねえんだ。しかも、全部の印と署名が入った空白の許可証なんて用意できねえよ。";
            link.l1 = "残念だな。じゃあな。"+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;
		
		case "patent_2_give":
			dialog.text = "わかった、それを手配してやろう。どんな許可証が必要なんだ？";
			if (GetPatentNation() != ENGLAND)
			{
			    link.l1 = "イングランドの";
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
			    link.l2 = "フランスの";
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
			    link.l3 = "スペインの";
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
			    link.l4 = "オランダの";
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = "俺が自分でやったほうがいいだろう。";
			link.l9.go = "exit";
		break;
		
		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			pchar.PatentPrice = 350000 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) * 100 + (5000 + rand(1000)) * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
            switch (sti(NPChar.nation))
            {
			    case PIRATE :
                    dialog.text = "これはバグです。もし見かけたら、ALexusBにご連絡ください";
                    link.l1 = "俺は問題ないぜ。お前の条件に同意する！";
                    break;
                case HOLLAND :
                    dialog.text = "オランダはほとんど平和な国だ。多くの友人ができて、敵はほんのわずかだろう。そして、 免許そのものも安く手に入るぜ。 "+pchar.PatentPrice+" ペソ。";
                    link.l1 = "俺は問題ないぜ。お前の条件に同意する！";
                    break;
                case FRANCE :
                    dialog.text = "フランスの友も敵も、あなたのものとなる。彼らの敵に属する船を沈めることが許される。そして、 その許可証自体には費用がかかる。 "+pchar.PatentPrice+" ペソ。";
                    link.l1 = "いいじゃねえか！俺は誰に仕えるかなんて気にしねえよ！フランスでも構わねえさ。";
                    break;
                case SPAIN :
                    dialog.text = "スペインには多くの敵がいる、それはお前の敵にもなるんだぜ！スペインは海の戦士たちの国だ。そして、 その許可証自体にも金がかかるぞ。 "+pchar.PatentPrice+" ペソ。";
                    link.l1 = "それが俺の望んでたことだ！偉い連中のために戦ったり任務をこなしたご褒美に、このわずかな金貨を受け取れ！";
                    break;
                case ENGLAND :
                    dialog.text = "正直に言うと、これがイギリス総督が私腹を肥やすやり方さ。そして、その許可証自体にも金がかかるぜ "+pchar.PatentPrice+" ペソ。";
                    link.l1 = "よし。奴に俺の血の金を渡せ、密輸や拿捕で稼いだやつだ！";
                    break;
			}

            if(makeint(Pchar.money) < makeint(pchar.PatentPrice))
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "patent_3";
			}

			link.l2 = "いや、俺のためじゃねえ。";
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = "取引が成立して嬉しいぜ。";
			link.l1 = "「さらばだ」 "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			iDiplomatPseudoGlobal = CalculateRelationContraSum(false);
			dialog.Text = "いいだろう。金がかかるぜ " + iDiplomatPseudoGlobal + " ペソ。";
			Link.l1 = "同意する。";
			if(makeint(Pchar.money) < iDiplomatPseudoGlobal)
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "気が変わった。";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "素晴らしい、私がすべて手配します。彼らはあなたと一緒に働くでしょう。";
			Link.l99 = "ありがとう。";
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -iDiplomatPseudoGlobal);
		break;
        // boal <--
		case "RelationAny_Done":
			i = sti(npchar.quest.relation);
			iDiplomatPseudoGlobal = CalculateRelationSum(i, false);
			dialog.text = "ふむ……何と言えばいいのか分からねえな。もちろん、和睦の申し出には応じられるぜ "+XI_ConvertString(Nations[i].Name+"Abl")+"、それには費用がかかる "+FindRussianMoneyString(iDiplomatPseudoGlobal)+".";
			if(sti(pchar.money) >= iDiplomatPseudoGlobal)
			{
				link.l1 = "選択肢はなさそうだ。俺の金を持っていけ。";
				link.l1.go = "relation3";
			}
			link.l2 = "いや、それは多すぎる。さらば。";
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = "素晴らしい！君とは驚くほど話が早いな。心配するな、15日以内に君の問題を解決してやる。";
			link.l1 = "「いいだろう。」";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -iDiplomatPseudoGlobal);
			ChangeNationRelationFromRelationAgent(i);
			attrLoc = "RelationAgent" + GetNationNameByType(i);
            Pchar.GenQuest.(attrLoc) = true;
		break;
		
		case "RelationYet":
			dialog.Text = "お前の問題は今すぐ解決されるところだ。\nただ座って待ってろ、これ以上早くはならねえぞ。";
			Link.l99 = "ありがとう。";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy":
			dialog.Text = "どの植民地の所有権について話したいんだ？";
			for (i=0; i<MAX_COLONIES; i++)
			{
				if (sti(colonies[i].HeroOwn) == true && sti(colonies[i].isBought) == false)
				{
					sld = GetFortCommander(colonies[i].id);
					attrLoc = "l" + i;
					Link.(attrLoc) = GetCityName(colonies[i].id) + " - " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)));
					Link.(attrLoc).go = "CityPay_" + i;
				}
			}
			Link.l99 = "いや、何もない。";
			Link.l99.go = "exit";
		break;
		
		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = "Colony "+GetCityName(colonies[i].id)+"、は所有されていた "+XI_ConvertString(GetNationNameByType(sti(sld.Default.nation))+"Gen")+"、再拿捕を阻止するための身代金は "+FindRussianMoneyString(iSumm)+".";
   			if(sti(pchar.money) >= iSumm)
			{
			    Link.l1 = "ああ、まさに俺が必要としていたものだ。";
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = "結構だ。興味はねえよ。";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = "よし、取引は進行中だ。拿捕しようとする動きはないぜ "+GetCityName(colonies[i].id)+" まただ。";
			Link.l2 = "ありがとうございます。良い一日を。";
			Link.l2.go = "exit";
			Link.l3 = "もう一つ質問がある。";
			Link.l3.go = "relation";
		break;
	}
}
