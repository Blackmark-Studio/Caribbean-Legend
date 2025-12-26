// boal 25/04/04 общий диалог мэры
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // фортовый командер
	ref arItem;
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

    ref offref;
    int i, cn, iRank, iDay;
    int qty;
    string attrLoc, QuestName, sTemp;
	bool bOk, bOk1, bOk2;
	
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10)+1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// генератор ИДХ по кейсу -->
	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
 	// генератор ИДХ по кейсу <--
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("私の屋敷に顔を出すとは、よくもまあそんな度胸があるものだな！？それとも、ただの愚か者か……","どうして私の愚かな護衛たちは敵に宮殿へ侵入させたのですか？この責任、誰かの首で償わせますわ。","どうやら私の護衛は一文の価値もないようですわね、ならず者が私の邸宅をうろついて私の物をあさっているなんて……"),LinkRandPhrase("「何かご用ですか、 "+GetSexPhrase("ろくでなし","悪魔")+"！？私の兵士たちはすでにお前の後を追っている"+GetSexPhrase("、汚らわしい海賊め","")+"!",+"殺人者め、今すぐ私の邸宅から出て行け！衛兵！","「俺はお前なんか怖くねえ」 "+GetSexPhrase("悪党","「ネズミ」")+"「もうすぐお前は我々の砦で絞首刑にされるぞ！」"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("お前の兵士たちは役立たずだ。","俺を捕まえてみろよ。"),RandPhraseSimple("「黙れ、」 "+GetWorkTypeOfMan(npchar,"")+"「さもないと、俺が黙らせてやるぜ！」","黙ってろ、相棒。そうすりゃ生きていられるぜ。"));
				link.l1.go = "fight";
				break;
			} 
			if (sti(NPChar.nation) == PIRATE)
            {
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
				{
					dialog.text = "ご用件は何でしょうか？";
					link.l1 = "あなたに重要な用件についてお話ししたかったのです。";
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
				{
					dialog.text = "何のご用ですか？";
					link.l1 = "あなたに重要な仕事についてお話ししたかったのです。";
					link.l1.go = "quests";
					break;
				}
					dialog.text = "話すことは何もない、旦那。私は忙しいのだ。";
					link.l1 = "申し訳ございません。";
					link.l1.go = "Exit";
            }
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
            {
				iTotalTemp = ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0);
                dialog.text = "おや、誰がいるか見てみろ！それは"+GetSexPhrase("","")+" "+GetFullName(pchar)+"。実はな、つい最近お前をここに連れ戻すために海賊狩りを送り出したばかりなんだ。 もしお前が自分からのこのこと現れると知っていれば、金を無駄にせずに済んだのにな。";
                if (sti(pchar.Money) >= iTotalTemp*6000)
                {
                    link.l1 = "ちょうどこれから精算しようと思っていたところだ。";
				    link.l1.go = "arestFree_1";
                }
				link.l2 = "そろそろ俺は早くずらかる時間だな。";
				link.l2.go = "arest_1";
				break;
            }
			if (false)
			{
    			dialog.text = "侵入だ！衛兵！警報だ！殺人だ！";
				link.l1 = "「くそっ！」";
				link.l1.go = "fight"; 
				break;
			}
			//--> Jason, Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && npchar.city == "FortFrance")
			{
    			dialog.text = "何をご所望ですか、旦那？";
				link.l1 = "ごきげんよう、閣下。私はシャルル・ド・モール、つい先日パリから参りました。 ミシェル・ド・モンペールを探しております。";
                link.l1.go = "Sharlie";
				npchar.quest.meeting = "1"; // patch-6
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && npchar.city == "FortFrance")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
				{
					dialog.text = "ああ、あなたでしたか、旦那……無礼をお許しください。申し訳ありません、ここ植民地ではパリのような礼儀作法からは遠いものでして。";
					link.l1 = "「もちろんでございます、公爵閣下。」";
					link.l1.go = "Sharlie_2";
				}
				else
				{
					dialog.text = "何かご用ですか、チャールズ？";
					link.l1 = "質問があるのですが……";
					link.l1.go = "quests";
					link.l2 = "いいえ、何もありません。";
					link.l2.go = "exit";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
				{
					link.l3 = "旦那、ジャングルで盗賊の死体を見つけました。インディオに殺されたようです。死体にはイヤリングがあり、 どうやらヨーロッパから持ち込まれたもののようです。もしかすると、 あなたの町の貴族の誰かの持ち物だったのではありませんか？";
					link.l3.go = "Sharlie_junglejew";
				}
				npchar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_TravlyaKrys") && npchar.city == "FortFrance")
			{
    			dialog.text = "カリブへようこそ、de Maure船長。今回は本当に歓迎いたします。";
				link.l1 = "ありがとうございます、閣下。";
                link.l1.go = "TK_TravlyaKrys";
				DelLandQuestMark(npchar);
				break;
			}
			// Jason НСО
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && npchar.city == "Marigo" && IsUniformEquip())
			{
    			dialog.text = "お会いできて嬉しいです、総督！ご機嫌いかがですか？シント・マールテンではすべて順調です。";
				link.l1 = "私は滞在する時間がありません。引き続き頑張ってください。";
				link.l1.go = "exit";
				link.l2 = "仕事の話をしたかったのです。";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "運試しの勝負はいかがですか？";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE && IsUniformEquip())
			{
    			dialog.text = "おお、総督閣下、お会いできて本当に嬉しゅうございます！このささやかな植民地も、すべて順調でございます！どうぞ、 おかけくださいませ、すぐに召使いに食卓の用意をさせますわ…";
				link.l1 = "その必要はない。長居するつもりはないからな。引き続きしっかり頼むぞ。";
				link.l1.go = "exit"; 
				link.l2 = "仕事の話をしたかったのです。";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "運試しの勝負でもどうだ？";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") &&  IsUniformEquip())
			{
    			dialog.text = "ここにいるのは誰だ！フランス植民地総督閣下じゃないか！何のご用でいらしたのですか、閣下？どうぞお掛けください、 召使いにワインと新鮮な果物を持って来させます。";
				link.l1 = "ご心配なく、私はただこの島を訪れていたので立ち寄っただけですし、 ご挨拶せずに通り過ぎるわけにはいきませんでした。";
				link.l1.go = "exit"; 
				link.l2 = "お仕事の話をしたかったのです。";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "運試しの勝負はいかがですか？";
				link.l8.go = "Play_Game";
				break;
			}		
			//--> Jason, Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernor" && npchar.city == "FortFrance")
			{
    			dialog.text = "おや、やっと来たな、船長！ずいぶん待たせてくれたじゃないか。";
				link.l1 = "できるだけ早く参上いたしました、閣下。お急ぎのご用件があると伺いましたが？";
				link.l1.go = "Portugal"; 
				break;
			}			
			//<-- Португалец
            
            if (npchar.quest.meeting == "0")
			{
				dialog.text = "私の部下が、あなたが非常に粘り強く謁見を求めていたと報告してくれました。私の名は "+GetFullName(npchar)+"。私はこの町の総督でございます "+GetCityName(NPChar.city)+"、の臣下 "+NationKingsName(npchar)+"。さて、どうなさいましたか、何をご所望ですか "+GetAddress_Form(NPChar)+"?";
				link.l1 = "私の名前は "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_townhall")
				{
					dialog.text = TimeGreeting()+"「、MacArthur嬢。」";
					link.l1 = TimeGreeting()+"、閣下。";
					link.l1.go = "Helen_node_1"
				}
			}
			else
			{
               	//ОСАДЫ homo
				if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
                {

                    makearef(aData, NullCharacter.Siege);
                    
                    if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        dialog.text = "「それだけですか？」";
                        link.l1 = "はい、旦那。これ以上お時間は取らせません。";
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = "ご気分を害してしまい申し訳ありませんが、今はお話しする時間がございません。ご存知の通り、我々 の植民地は攻撃を受けましたので "+NationNamePeople(sti(aData.nation))+"。私はまだ防衛の手配をしております。";
                        link.l1 = "砦の防衛に私の助力を申し出たいのでございます。";
                        link.l1.go = "siege_task";
                        link.l2 = "それでは、これ以上お引き止めいたしません。";
            			link.l2.go = "exit";
                    }
                }
                else
                {//->
                    makearef(aData, NullCharacter.Siege);
                    if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                    && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                        ChangeCharacterComplexReputation(pchar,"nobility", 10);
                        AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                        AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                        //--> слухи
                        SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and to defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
			            //<-- слухи
                        DeleteAttribute(aData, "PlayerHelpMayor");
                        DeleteAttribute(aData, "HelpColony");
                        dialog.text = "「ああ、あなたか、」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"、お会いできて嬉しいです。我が植民地に良い知らせがあります――我々は攻撃を撃退することに成功しました "+NationNameSK(sti(aData.nation))+" 侵略者たちだ。お前にも関わりがあるから、これが報酬だ― "+(sti(aData.iSquadronPower)*1500)+" エイトレアル銀貨だ。ほら、持っていけ。";
                        link.l1 = "ありがとうございます。 "+GetAddress_FormToNPC(NPChar)+"、お取引できて光栄です！";
                        link.l1.go = "exit";
                    }
                    else
                    {
   						//--> дача квеста найти кольцо в борделе
						if (rand(4) == 4 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 365 && sti(pchar.questTemp.HorseQty) > 10)
						{// Addon-2016 Jason
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
        						dialog.text = "あなたに頼みたい仕事があるのですが、少々変わった内容です。";
								link.l1 = "それが私の最も得意とする任務でございます。";
        						link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<-- дача квеста найти кольцо в борделе    				
						dialog.text = RandPhraseSimple("おや、またお前か？今度は俺に何の用だ？","私の都市の業務を妨げているのですよ。ご用件は何ですか、 "+GetAddress_Form(NPChar)+"?");
						if (npchar.city != "Panama") // Addon-2016 Jason
						{
							link.l1 = "あなたに仕事の件で話がしたいのです "+NationNameGenitive(sti(NPChar.nation))+".";
							link.l1.go = "work";
						}
						// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
						if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
						{
							link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen")+" 海賊を見つけた。全員だ "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" 現在船に乗せております。彼らを当局に引き渡したいのです。";
							link.l11.go = "PiratesOnUninhabited_1";
						}
						
        				link.l2 = "あなたに大事な話があって参りました。";
						if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
						{
							link.l2.go = "ReasonToFast_Mayor1";
						}
						else
						{
							link.l2.go = "quests";   //(перессылка в файл города)
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
						{
							if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
							{
								link.l12 = "巡回隊を指揮している船長がいる "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" 「名付けられた」 "+pchar.GenQuest.CaptainComission.Name+"「どうやって彼に会えばいいんだ？」";
								link.l12.go = "CapComission_Mayor1";
							}	
							if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
							{
								link.l12 = "巡回隊を指揮していた元船長 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 当局に隠し財宝の場所を明かすことに同意した。";
								link.l12.go = "CapComission_Mayor9";
							}
							if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
							{
								link.l12 = "哨戒隊を指揮していた元船長 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 私に隠し場所を明かした。";
								link.l12.go = "CapComission_Mayor13";
							}
						}
						if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25  && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
						{
							if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
							{
								iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
								if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" 私は船長に会った "+pchar.GenQuest.ShipWreck.Name+" 海賊に上陸させられた彼とその船員たち "+pchar.GenQuest.ShipWreck.BadName+". ""残念ながら、私の船にはすでに乗組員が多すぎて、彼らを乗せることができませんでした。しかし、 食料と武器は残してきました。もし救助船が\n "+(30 - iDay)+" 日数が経てば、生きているかどうかも分からないんだ。";
									link.l13.go = "ShipWreck1";
								}
								else
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Gen"))+" 難破船の船員たちに会ったんだ『"+pchar.GenQuest.ShipWreck.ShipTypeName+"「船長と一緒に。」 "+"残念ながら、私の船にはすでに乗組員が多すぎて、彼らを乗せることができませんでした。しかし、 食料と武器は残してきました。救助船が彼らを迎えに来なければ\n "+(30 - iDay)+" 日数が経てば、生きて見つけられるかどうか分からないんだ。";
									link.l13.go = "ShipWreck1";							
								}
							}	
						}
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = "囚人を引き渡したいのです。";
        				    link.l3.go = "sell_prisoner";
        				}
        				if (npchar.Default  == npchar.location) // если не в тюрьме
        				{
        					if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        					{
        						link.l4 = "あなたといくつか財政上の問題を整理する必要があります。";
        						link.l4.go = "LoanForAll";//(перессылка в кредитный генератор)
        					}
        				}
						//-->> сдача найденного в борделе кольца
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
        						link.l5 = "指輪を見つけることができました。どうぞ。";
        						link.l5.go = "TakeRing_S1";
							}
							else
							{
        						link.l5 = "あなたの結婚指輪を持ってきた。娼館の…働いている娘の一人が持っていたんだ。";
        						link.l5.go = "TakeRing_S3";
							}
						}
						//<<-- сдача найденного в борделе кольца 
						
						//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "私は町からの伝言を持ってきました "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
						//<-- генер почтового курьера 2 уровня
						
						// Warship, 16.05.11. Квест "Правосудие на продажу" -->
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+"、最近衛兵に捕まった首領を持つ密輸団を見つけたんだ。今、奴らは首領の脱走を企んでいる。その船『"+PChar.GenQuest.JusticeOnSale.ShipName+"「』は停泊している」 "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+".";
							link.l15.go = "JusticeOnSale_1";
						}
						
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+"、密輸団はもういない！";
							link.l15.go = "JusticeOnSale_7";
						}
						// <--Правосудие на продажу
						//Jason --> Регата
						if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
						{
							link.l16 = "私はレガッタのために来ました。これが私の招待状です。";
							link.l16.go = "Regata";
						}
        				//link.l7 = "「の総督がどこにいるのか知りたいのですが」 "+NationNameGenitive(sti(NPChar.nation))+"です。";
        				link.l8 = "「運試しの賭け事でひと休みなさいますか？」";
        			    link.l8.go = "Play_Game";
        				link.l10 = "申し訳ありませんが、職務がございますので失礼いたします。";
        				link.l10.go = "exit";
                    }
                }//<-
			}
		break;
		
		// Warship Генер "Пираты на необитайке"
		case "PiratesOnUninhabited_1":
			offref = CharacterFromID("PirateOnUninhabited_0");
			qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);
			
			PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;
			
			dialog.text = "よろしい。私たちはこの共通の災厄に力を合わせて立ち向かわねばなりません。 すぐに船を派遣して奴らを引き取りに行かせましょう。安心なさい、1週間も経たぬうちに奴らは絞首台に吊るされているはずです。ああ、それから当然ながら報酬もございます―― "+FindRussianMoneyString(qty)+".";
			link.l1 = "ありがとうございます、閣下。いつも光栄でございます。 ";
			link.l1.go = "PiratesOnUninhabited_2";
			link.l2 = "いいや。やはり、それではいけません。";
			link.l2.go = "exit";
		break;
		
		case "PiratesOnUninhabited_2":
			offref = CharacterFromID("PirateOnUninhabited_0");
			
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));
			
			RemovePassenger(PChar, offref);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTemp = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTemp, "PiratesOnUninhabited", "12");
			AddQuestUserData(sTemp, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTemp, "mayorName", GetFullName(NPChar));
			CloseQuestHeader(sTemp);
			
			PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
			PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";
			
			if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
			{
				PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
				
				PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
				Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
			}
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Mayor1":
			dialog.text = "私は耳を傾けております、船長。";
			link.l1 = "あなたの駐屯地の士官と海賊たちの間に犯罪的な共謀があることをお伝えしたかったのです……（事情を説明する）。";
			if(sti(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_BMayor";			
			}
			else
			{
				link.l1.go = "ReasonToFast_GMayor";	
			}
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_GMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "ありがとうございます。 "+GetSexPhrase("旦那","お嬢さん")+"！すぐにあの裏切り者の逮捕を命じます。\nあなたも多額の金を使ったことでしょう、しかし、残念ながら我々の財庫は空でございます……";
				link.l1 = "お金のためにやったわけではありません、閣下。";
				link.l1.go = "ReasonToFast_GMayor_11";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "感謝いたします！あの悪党は必ず逮捕させます。\n考えてもみてください！私はちょうど彼の十年勤続を称えて金の柄のサーベルを授与しようとしていたのです！ あなたのおかげで大恥をかかずに済みました！";
				link.l2 = "「正義はそれ自体が報いである。」";
				link.l2.go = "ReasonToFast_GMayor_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mis"+GetSexPhrase("テール","ｓ")+" ド・モール、証人もいないのに容疑者を殺してはいけません！これでは彼の罪を証明することすらできなくなりました！ あなたを過失致死で逮捕させないようにするだけで精一杯です。";
				link.l3 = "自己防衛でございました、閣下。";
				link.l3.go = "ReasonToFast_GMayor_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}			
		break;
		
		case "ReasonToFast_BMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 				
				dialog.text = "「船長、てめえが何をしでかしたかわかってんのか？！！俺はこの罠を一ヶ月以上も仕掛けてたんだぜ！それを、 てめえの気まぐれで、俺たちの哨戒隊の会合を台無しにしやがって」 "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" それで今ここに来て自慢しに来たのか？！この作戦にかかった全ての費用や出費を、 私は一体どう説明すればいいのか教えてくれないか！？";
				link.l1 = "閣下、問題は私が解決いたしました。よくお考えになれば、最初から私に報酬をお支払いいただくべきでしたでしょう！";
				link.l1.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "この地図を見せてくれ\n本気か？このボロボロの紙切れが証拠だっていうのか？";
				link.l2 = "さあ、閣下、どうかご賢明に。";
				link.l2.go = "ReasonToFast_BMayor_1";
				TakeItemFromCharacter(pchar, "mapQuest");				
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "ほうほう、これで私の巡回隊に何が起きたか分かりましたわ。少なくとも、あなたがここに来てくれたおかげで、 殺人犯を探す手間が省けましたの。";
				link.l3 = "閣下！あなたはどうしても要点をお認めになりませんね……";
				link.l3.go = "ReasonToFast_BMayor_1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_GMayor_11":
			dialog.text = "お前は馬鹿かもしれんが、少なくとも役に立つ馬鹿だ。ほら、この地図を持っていけ； 先週絞首刑にした海賊から見つけたものだ。神のご加護があれば、その海賊の財宝を見つけられるかもしれんが、 私にはまず無理だと思うな……";
			link.l1 = "ありがとうございます、とてもご寛大ですわ！";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		
		case "ReasonToFast_GMayor_21":
			dialog.text = "あなたの熱意は称賛に値します。この剣を報酬としてお受け取りください――せめてもの礼ですわ。ああ、それと地図もご自身でお持ちになって。 カリブにはこの手の偽物がたくさんあると確信していますの。";
			link.l1 = "ありがとうございます、とてもご親切ですわ！";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_GMayor_31":
			dialog.text = "「まあ、そうかもしれません……。さて、この取引は神の正義と主のお導きによって決まったと申しておきましょう。」";
			link.l1 = "ありがとうございます、とてもご親切ですわ！";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");
		break;
		
		case "ReasonToFast_BMayor_1":
			dialog.text = "黙れ、小僧！貴様は正気じゃないか、あるいは我々の敵と通じているのか！\n衛兵ども、この馬鹿を捕えよ！";
			link.l1 = "俺に手を出したら、その手を失うぜ！";
			link.l1.go = "fight";
		
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";						
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		
		// --------------------------Операция 'Галеон'-----------------------------
		case "CapComission_Mayor1":
			dialog.text = "今はそれは不可能です。彼は逮捕されており、裁判を待っています。";
			link.l1 = "彼か？それで、彼は何の容疑をかけられているんだ？";			
			link.l1.go = "CapComission_Mayor2";
		break;
		
		case "CapComission_Mayor2":
			dialog.text = "残念ながら、それは疑いではなく、確かな事実でございます。我々には、 彼が巡回を装いながら船を襲撃していたという情報がございます。商人から貨物を没収し、 それを密輸業者や海賊に売りさばいていたのです。嘆かわしいことです……かつては王冠が誇る最良の船長の一人と見なされていたというのに……";
			link.l1 = "「そして誰がその証拠を渡したのですか？」";
			link.l1.go = "CapComission_Mayor3";				
		break;
		
		case "CapComission_Mayor3":
			dialog.text = "彼の被害者の一人が報告書を書き、その中で事件の詳細、日付、襲撃された船の名前、 押収された品物の数量まで記述している。 "+"私を信じてください、数字はかなり立派です。その日の哨戒で\n "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))+" 船長 "+pchar.GenQuest.CaptainComission.Name+" 確かに当直しておりました。船長はこの出来事を報告書で海賊船との遭遇と記述しましたが、 貨物については一切言及しておりませんでした。";
			link.l1 = "「だが、そもそも積み荷はあったのか？」";
			link.l1.go = "CapComission_Mayor4";
			pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;
		
		case "CapComission_Mayor4":
			dialog.text = "間違いありません。被害者は非常に有名な人物で、誹謗中傷などで自らの品位を落とすようなことはしないでしょう。 現在、我々の巡回隊がその船長の隠し財宝を捜索中です。 "+"発見され次第、船長は法廷に出廷できます\nこの件でご協力いただければ、私どもは大変感謝いたします。";
			link.l1 = "おそらく違います。この土地にはあまり詳しくないので、隠し場所を探すのは無理です。\n失礼します、行かなくてはなりません。";
			link.l1.go = "CapComission_Mayor5";
			link.l2 = "もしかして……どれくらい猶予があるんだ？";
			link.l2.go = "CapComission_Mayor6";	
		break;
		
		case "CapComission_Mayor5":
			AddQuestRecord("CaptainComission2", "49");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.GenQuest.CaptainComission = "MayorTalkBad";
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor6":
			dialog.text = "私の考えでは、あと二日もすれば哨戒隊があなたの助けなしでも隠し場所を見つけられるでしょうから、 急いだほうがよろしいです。"; 
			link.l1 = "ああ、任せとけ。だが船長のところに寄らなきゃならねえ "+pchar.GenQuest.CaptainComission.Name+"。これは手配できますか？";
			link.l1.go = "CapComission_Mayor7";
		break;
		
		case "CapComission_Mayor7":
			dialog.text = "それは問題ありません。砦の司令官にあなたの訪問を知らせておきます。";
			link.l1 = "ありがとうございます。では、これで失礼いたします。";
			link.l1.go = "CapComission_Mayor8";
		break;
		
		case "CapComission_Mayor8":
			AddQuestRecord("CaptainComission2", "50");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);			
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			OfficersReaction("good");
			pchar.GenQuest.CaptainComission.MayorTalkGood = true;
			pchar.GenQuest.CaptainComission = "MayorTalkGood";
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			SetFunctionTimerConditionParam("CaptainComission_GetSecretTimeIsOut", 0, 0, 2, MakeInt(24 - GetHour()), false);
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor9":
			dialog.text = "素晴らしい！宝はどこだ？";
			link.l1 = "まだ分かりません。彼は正確な場所を教えてくれませんでした。";
			link.l1.go = "CapComission_Mayor10";
		break;
		
		case "CapComission_Mayor10":
			dialog.text = "ふむ、なんという偶然だ！実はな、あいつも俺に正確な場所は“教えてくれなかった”んだよ……";
			link.l1 = "ただいま取り組んでおります。";
			link.l1.go = "CapComission_Mayor11";
		break;
		
		case "CapComission_Mayor11":
			dialog.text = "もう違う\n衛兵たち！囚人を部屋へ連れて行け\nお前はもう行ってよい "+GetFullName(pchar)+".";
			link.l1 = "「ですが、総督…」";
			link.l1.go = "CapComission_Mayor12";
		break;
		
		case "CapComission_Mayor12":
			sld = CharacterFromID("CapComission_1");
			sld.lifeDay = 0;
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);			
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";									
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);			
			AddQuestRecord("CaptainComission2", "23");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CapComission_Mayor13":
			pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";
			dialog.text = "素晴らしい！それで、どこへ彼の財宝を探しに行くんだ？";
			link.l1 = "「～の中で」 "+RandPhraseSimple(RandPhraseSimple("北の","西洋"),RandPhraseSimple("東の","南部"))+" の終わり "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+" 崖のふもとに大きな窪みがあり、その入口は石で塞がれている。そこが隠し場所だ。";
			link.l1.go = "CapComission_Mayor14";
		break;
		
		case "CapComission_Mayor14":
			dialog.text = "素晴らしい働きだ！それで、どこにいるんだ "+pchar.GenQuest.CaptainComission.Name+" 本人か？お前が砦の地下牢から彼を連れ出したと聞いたが。";
			link.l1 = "残念ながら、彼は密輸業者との小競り合いで命を落としました。";
			link.l1.go = "CapComission_Mayor15";
		break;
		
		case "CapComission_Mayor15":
			dialog.text = "これはまずい……本当にまずいぞ。 "+GetSexPhrase("旦那","お嬢さん")+" "+GetFullName(pchar)+"。私は彼を公開処刑しようと思っていた、「他の者たちへの見せしめのために」\n"+"いずれにせよ、彼は絞首台を免れることはなかったでしょう\nさて、あなたは技術的には囚人を違法に釈放したことで法を犯し、そのうえ彼を救うことにも失敗しましたので、 私の報告書でこの件を揉み消すことはできません。したがって、報酬は差し上げられません……しかし、個人的にはあなたに感謝したいのです。私からの贈り物を受け取ってください――戦う船長には非常に役立つ品です。 ";
			link.l1 = "ありがとうございます。いつでもお仕えできて光栄です。";	
			link.l1.go = "CapComission_Mayor16";
		break;
		
		case "CapComission_Mayor16":
			AddQuestRecord("CaptainComission2", "30");
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			CloseQuestHeader("CaptainComission2");
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			OfficersReaction("good");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// --------------------------Операция 'Галеон'-----------------------------
		
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		case "ShipWreck1":
			if(iDay > 15)
			{
				dialog.text = RandPhraseSimple("どうやってやったんだ？あそこまで行くには、追い風でも最低十五日はかかるはずだぜ！","Captain "+GetFullName(pchar)+"、あなたの無責任さには驚かされます！なぜもっと早く私に知らせなかったのですか？");
				link.l1 = "さて、何と言えばいいのかわからないな……";
				link.l1.go = "ShipWreck2";
			}
			else
			{
				dialog.text = "これは素晴らしい知らせです！もう会える望みは失っていました "+pchar.GenQuest.ShipWreck.Name+"  また生きて戻ったのですね。すぐに救助隊を派遣いたします。それと、救出にご尽力いただいたお礼として、 この報酬をお受け取りください。";
				link.l1 = "ありがとうございます、閣下。お力になれて光栄でございます。遠征隊もきっと間に合うことでしょう。";
				link.l1.go = "ShipWreck3";	
			}
			pchar.GenQuest.ShipWreck.SpeakMayor = true;
			pchar.quest.ShipWreck_MeetInShore.over = "yes";
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen таймер на 30 дней тоже нужно снять
		break;
		
		case "ShipWreck2":
			dialog.text = "おおっと、なんてこった…何を言えばいいんだ？海の法を学んでこい、坊主！まあいい、俺は全力でこの連中を助けてやるぜ。";
			link.l1 = "閣下、しかし私は彼らに十分な食糧を残してきました。ご安心ください、まだ時間はございます……";
			link.l1.go = "ShipWreck4";
		break;
		
		case "ShipWreck3":
			addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			AddQuestRecord("ShipWrecked", "14");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;		
		
		case "ShipWreck4":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("ShipWrecked", "13");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		
		// ---------------------- найти кольцо в борделе ----------------------------
		case "TakeRing_1":
			dialog.text = "「あなたが、そうですね……」 "+GetSexPhrase("売春宿の常連でございます","時々娼館に行くのが好き")+"。そこであなたに助けを求めることにしたのです\n"+"実はな、恥ずかしい話だが、俺も最近そこにいたんだ……";
			link.l1 = "それの何が悪いんだ？性なんてごく自然なものだぜ……";
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = "ああ、いや、説教しているわけじゃないんだ、違うよ。実はな、あるとき酒を飲みすぎて、 結婚指輪をなくしちまったんだ……";
			link.l1 = "それは困ったな。申し訳ない。";
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = "俺に同情なんかいらねえ。必要なのは指輪を取り戻すことだ。もし真夜中までに取り返してくれたら、 たっぷり礼をするぜ。失敗したら、女房に殺されちまう。";
			link.l1 = "なるほど……それで、どこでそれを失くしたのか、正確な場所は覚えていますか？何か特別なことを覚えていますか？";
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = "残念ながら、いいえ。何もありません。";
			link.l1 = "なるほど。では、探してみましょう。";
			link.l1.go = "TakeRing_5";
			link.l2 = "「知っているだろう、」 "+GetAddress_FormToNPC(NPChar)+"……今回は遠慮させていただきます。どうかお許しください……";
			link.l2.go = "TakeRing_6";
		break;	
		case "TakeRing_5":
			dialog.text = "素晴らしい！しかし、忘れないでください――真夜中までに見つけなければなりません。";
			link.l1 = "覚えている。すぐに戻ってくる。";
			link.l1.go = "exit";
			pchar.questTemp.different = "TakeMayorsRing";
			pchar.questTemp.different.TakeMayorsRing = "toBrothel";
			pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
			pchar.questTemp.different.TakeMayorsRing.city = npchar.city;	
			pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank)*100+1000;
			sld = ItemsFromID("MayorsRing");
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			//ложим кольцо в итем
			if (rand(3) != 2)
			{				
				switch (rand(2))
				{
					case 0: sTemp = "_Brothel_room";  break;
					case 1: sTemp = "_Brothel";  break;
					case 2: sTemp = "_SecBrRoom";  break;
				}
				sld.shown = true;
				sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
				sld.startLocator = "item" + (rand(4)+1);
				pchar.questTemp.different.TakeMayorsRing.item = true; //флаг кольцо валяется в итемах
				Log_QuestInfo("The ring is at " + sld.startLocation + ", in locator " + sld.startLocator);
			}
			SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("SeekMayorsRing");
			AddQuestRecord("SeekMayorsRing", "1");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;	
		case "TakeRing_6":
			dialog.text = "おや？それはまったく予想外でしたな……それでは、ご武運をお祈りします、船長。";
			link.l1 = "ごきげんよう。";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
		break;

		case "TakeRing_S1":
			dialog.text = "それは俺の指輪だ！命を救ってくれたんだな！";
			link.l1 = "たいしたことではありません、旦那。";
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
			dialog.text = "よくやってくれたな、これが報酬だ！本当に感謝しているぞ！";
			link.l1 = "お力になれて光栄です、旦那。次はもっとお気をつけくださいませ。";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		case "TakeRing_S3":
			dialog.text = "おお、神よお許しを！本当にこんなに酒を飲むのはやめるべきだな……";
			link.l1 = "間違いないぜ！ほら、お前の指輪だ。";
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
			dialog.text = "はいはい、本当にありがとうございます。あなたには借りができました！よくやってくれたので、これが報酬です！";
			link.l1 = "Thanks "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "MayorsRing");
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 3);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// ---------------------- найти кольцо в борделе ----------------------------

		case "node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "私たちはすでにすべて話し合いましたね？";
                    link.l1 = "その通りです。これ以上お引き留めしません。";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "ご気分を害してしまい申し訳ありませんが、今はあなたと話す時間がありません。ご存知の通り、我々 の植民地が襲撃されたのです\n "+NationNamePeople(sti(aData.nation))+"。防衛の手配をしなければなりません。";
                    link.l1 = "ええと、ただ砦の防衛に協力したいと思って申し出たまでです。";
                    link.l1.go = "siege_task";
                    link.l2 = "それでは、これ以上お引き止めいたしません。";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "「ああ、お前か。」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"、お会いできて嬉しいです。良い知らせがあります――我々は撃退することに成功しました "+NationNameSK(sti(aData.nation))+" 侵略者たちだ。お前もこの件で役割を果たしたな、これが報酬だ― "+(sti(aData.iSquadronPower)*1500)+" エイトピース銀貨だ。ほら、持っていけ。";
                    link.l1 = "「ありがとうございます」 "+GetAddress_FormToNPC(NPChar)+"、お取引できて光栄です！";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "「それで、何の用で私の国政の重要な仕事を妨げに来たのですか？」";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "「私は働きたかった」 "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Dat")+" 海賊たちに会った。全員 "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" 今、船に乗っております。彼らを当局に引き渡したいのです。";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "重要な件についてお話ししたく参りました。";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "巡回隊を指揮している船長がいる "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" 「名付けられた」 "+pchar.GenQuest.CaptainComission.Name+"「どうすれば彼に会えるんだ？」";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "哨戒任務を指揮していた元船長 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 当局に隠し財宝の場所を明かすことに同意した。";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "哨戒隊を指揮していた元船長  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 私に隠し場所を明かした。";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" 俺は船長に会った "+pchar.GenQuest.ShipWreck.Name+" 海賊に上陸させられた彼とその船員たち "+pchar.GenQuest.ShipWreck.BadName+". "+"残念ながら、私の船にはすでに乗組員が多すぎて、彼らを乗せることができませんでした。しかし、 食料と武器は残してきました。救助船が彼らを迎えに来なければ\n "+(30 - iDay)+" 日数が経てば、まだ生きているかどうかは分からないんだ。";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" 難破した船の船員たちに会ったんだ『"+pchar.GenQuest.ShipWreck.ShipTypeName+"「船長と一緒に。」 "+"残念ながら、私の船にはすでに乗組員が多すぎて、彼らを乗せることができませんでした。しかし、 食料と武器は残してきました。救助船が彼らを迎えに来なければ\n "+(30 - iDay)+" 日数が経てば、彼らがまだ生きているかどうか、私には分かりません。";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "「町からの伝言があります」 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "旦那様、最近衛兵に捕まった首領を持つ密輸団を発見いたしました。現在、彼らはその首領の脱走を企てております。 彼らの船『"+PChar.GenQuest.JusticeOnSale.ShipName+"「』は停泊している」 "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Gen")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "捕虜の船長を当局に引き渡さなければならない。";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "私はレガッタのために来ました。これが私の招待状です。";
						link.l4.go = "Regata";
					}
        			link.l5 = "少し休憩なさいますか？";
        			link.l5.go = "Play_Game";
        			link.l10 = "ただの表敬訪問でした。 "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Helen_node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "すでにすべて話し合いましたね？";
                    link.l1 = "その通りです。これ以上お引き留めしません。";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "ご気分を害してしまい申し訳ありませんが、今はあなたと話している時間がございません。ご存知の通り、我々 の植民地は攻撃を受けたのです "+NationNamePeople(sti(aData.nation))+"。防衛の確認をしなければなりません。";
                    link.l1 = "ええと、ただ砦の防衛に協力したいと思って申し出たまでです。";
                    link.l1.go = "siege_task";
                    link.l2 = "それでは、これ以上お引き止めしません。";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "「ああ、お前か。」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"、お会いできて嬉しいです。良い知らせです――我々は撃退することに成功しました "+NationNameSK(sti(aData.nation))+" 侵略者たちだ。お前もこれに一役買ったな、これが報酬だ― "+(sti(aData.iSquadronPower)*1500)+" エイトレアル銀貨だ。ほらよ。";
                    link.l1 = "ありがとうございます。 "+GetAddress_FormToNPC(NPChar)+"、お取引できて光栄です！";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "何の用で私のところに？あなたの…後ろ盾とすべての用事を済ませていると思っていましたが。\nまあ、話してください。私はいつでもあなたの話を聞くのを嬉しく思いますよ。";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "「私は働きたかった」 "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Dat")+" 海賊たちに会った。全員 "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" 今、船に乗っております。私は彼らを当局に引き渡したいのです。";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "大事な件についてお話ししたく参りました。";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "巡回隊を指揮している船長がいる "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" 「名付けられた」 "+pchar.GenQuest.CaptainComission.Name+"「どうやって彼に会えばいいんだ？」";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "哨戒隊を指揮していた元船長 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 当局に隠し財宝の場所を明かすことに同意した。";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "哨戒隊を指揮していた元船長  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 私に隠し財宝の場所を明かした。";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" 私は船長に会った "+pchar.GenQuest.ShipWreck.Name+" 海賊に上陸させられた彼とその船員たち "+pchar.GenQuest.ShipWreck.BadName+". "+"残念ながら、私の船にはすでに乗組員が多すぎて、彼らを乗せることができませんでした。しかし、 食料と武器は残してきました。もし救助船がこの期間内に彼らを迎えに来なければ\n "+(30 - iDay)+" 日数が経てば、まだ生きているかどうかは分からないんだ。";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" 難破した船の船員たちに会ったんだ『"+pchar.GenQuest.ShipWreck.ShipTypeName+"「船長と一緒に。」 "+"残念ながら、私の船にはすでに男手が多すぎて、彼らを乗せることができませんでした。しかし、 食料と武器は残してきました。救助船が彼らを迎えに来ない場合は\n "+(30 - iDay)+" 日数が経てば、まだ生きているかどうか、私には分かりません。";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "私は町からの伝言を預かっております "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "旦那様、最近衛兵に捕まった首領を持つ密輸団を見つけました。今、奴らは彼の脱走を企んでおります。奴らの船『"+PChar.GenQuest.JusticeOnSale.ShipName+"「'は停泊している」 "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Gen")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "私は捕虜の船長を当局に引き渡さなければなりません。";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "私はレガッタのために来ました。これが私の招待状です。";
						link.l4.go = "Regata";
					}
        			link.l5 = "少し休憩なさいますか？";
        			link.l5.go = "Play_Game";
        			link.l10 = "「ただの表敬訪問でした」 "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "今はだめだ！検査があるんだ、アラミーダ旦那が町に来ている。ああ、毎年同じことだ、俺が何をしたっていうんだ……";
				link.l1 = "おっしゃる通りです。お引き止めはいたしません。";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			dialog.text = "ふむ、どんな遊びがお好みですか？";
			link.l1 = "「本気の金を賭けてカードゲームをやらないか？」";
			link.l1.go = "Card_Game";
   			link.l2 = "ポーカージョーカーでサイコロを振ってみないか？";
			link.l2.go = "Dice_Game";
			link.l10 = "申し訳ありませんが、職務がございますので。";
			link.l10.go = "exit";
		break;
		
		//  карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "申し訳ありません、モンシニョール、しかし今はその時間がございません。\nまた次の機会にいたしましょう。"; // Jason НСО
                else dialog.text = "私は海賊どもと賭け事などいたしません！";
    			link.l1 = "かしこまりました。";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = "もちろんだぜ！くつろぐのは心にはいいが、財布にはよくねえな……";
	    			link.l1 = "素晴らしいです。";
	    			link.l1.go = "Cards_begin";
	    			link.l2 = "我々のゲームのルールは何ですか？";
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = "いや、今日はもう終わりだ。やることがあるんでな。";
	    			link.l1 = "かしこまりました。";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "さあ、それでは始めよう！";
			link.l1.go = "Cards_begin";
			link.l3 = "いいえ、私のためではありません……";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = "まずは賭けの内容を決めよう。";
			link.l1 = "千枚のエイトで勝負しようぜ。";
			link.l1.go = "Cards_Node_100";
			link.l2 = "5,000枚のエイトを賭けて勝負しようぜ。";
			link.l2.go = "Cards_Node_500";
			link.l3 = "行かなくてはならないようですね。";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "お前は悪名高いイカサマ師だ。俺はお前とは賭けをしねえ。";
                link.l1 = "全部嘘だ！";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "冗談を言っているのか、 "+GetAddress_Form(NPChar)+"？金がないのか！";
                link.l1 = "そういうこともある。";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "これで終わりだ！もうカードはやらねえ――浪費家呼ばわりされて、この席を追い出される前にな。";
                link.l1 = "「残念です。」";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "よし、千枚のエイト金貨で勝負しよう。";
			link.l1 = "始めよう！";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "お前は悪名高いイカサマ師だ。俺はお前とは賭けをしねえ。";
                link.l1 = "全部嘘だ！まあ、どうでもいいさ。";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = "あなたはとても腕の立つ勝負師だと聞いています。私はあなたと高額の賭けはしませんよ。";
                link.l1 = "賭け金を下げましょうか？";
			    link.l1.go = "Cards_Node_100";
				link.l2 = "申し訳ありませんが、私（わたくし）は行かなくてはなりません。";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "冗談を言っているのか、 "+GetAddress_Form(npchar)+"！？15000枚のエイト金貨がないじゃねえか！";
                link.l1 = "俺が上げるぜ！";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "いいえ、こんな賭けを続ければ市の財政が底をついてしまいます。";
                link.l1 = "かしこまりました。";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "よし、じゃあ五千エイトで勝負しようぜ。";
			link.l1 = "始めよう！";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 5000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            SetNPCQuestDate(npchar, "Card_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--

	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "申し訳ありません、モンシニョール、今はそのような時間がございません。次の機会にいたしましょう。"; // Jason НСО
                else dialog.text = "私は海賊と賭け事などいたしません！";
    			link.l1 = "かしこまりました。";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "もちろんだ！息抜きは心にはいいが……財布にはよくねえな……";
	    			link.l1 = "素晴らしい。";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "我々のゲームのルールは何ですか？";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "いいや、今日はもう終わりだ。やることがあるんでな。";
	    			link.l1 = "かしこまりました。";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "さあ、始めようぜ！";
			link.l1.go = "Dice_begin";
			link.l3 = "いいえ、私のためではありません……";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			dialog.text = "まずは賭けの内容を決めよう。";
			link.l1 = "1ダイスにつき500エイトで勝負しようぜ。";
			link.l1.go = "Dice_Node_100";
			link.l2 = "1個のサイコロにつき2,000エイトピースで勝負しよう。";
			link.l2.go = "Dice_Node_500";
			link.l3 = "行かねばならないようですね。";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "お前は悪名高いイカサマ師だ。俺はお前とは賭けをしねえ。";
                link.l1 = "全部嘘だ！まあ、どうでもいいさ。";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "冗談を言っているのか、 "+GetAddress_Form(NPChar)+"？金がないのか！";
                link.l1 = "そういうこともあるさ。";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "これで終わりだ！もう賭博はやめるぜ――浪費家だなんて呼ばれて、職を追われる前にな…";
                link.l1 = "残念だ。";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "よし、じゃあ500エイトで勝負だ。";
			link.l1 = "始めよう！";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 500;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "お前は悪名高いイカサマ師だ。俺はお前とは賭けをしねえ。";
                link.l1 = "全部嘘だ！まあ、どうでもいいさ。";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "あなたがとても腕のいい勝負師だと聞いています。あなたとは高額の賭けはしませんよ。";
                link.l1 = "「賭け金を下げましょうか？」";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "申し訳ありませんが、私は行かねばなりません。";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "冗談を言っているのか、 "+GetAddress_Form(NPChar)+"？１５,０００枚のエイト金貨を持っていないじゃないか！";
                link.l1 = "俺が上げるぜ！";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "いいえ、こんな賭けを続ければきっと市の財庫が空になってしまいます。";
                link.l1 = "かしこまりました。";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "よし、1つのサイコロにつき2,000エイトで勝負しよう。";
			link.l1 = "始めよう！";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 2000;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
		case "node_2":
			dialog.text = "その場合は、私の書斎からお引き取りいただき、これ以上仕事の邪魔をなさらないでください。";
			link.l1 = "はい、はい、もちろんです。お邪魔して申し訳ありません。";
			link.l1.go = "exit";
		break;

		//---------------------------- генератор квестов мэра -------------------------------
		case "work": 
            dialog.text = "これはバグです。開発者に報告してください。";
        	link.l1 = "ありがとう、これは素晴らしいゲームだぜ！";
        	link.l1.go = "exit";
			
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "今はだめだ！検査があるんだ、アラミーダ旦那が町に来ているんだよ。ああ、毎年同じことだ、 俺が何をしたっていうんだ……";
				link.l1 = "おっしゃる通りです。お引き止めはいたしません。";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			//==> взят ли какой-либо квест
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{		 				
				//--> Федот, да не тот
				QuestName = pchar.GenQuest.questName;
				if (pchar.GenQuest.(QuestName).MayorId != npchar.id) 
				{					
					dialog.text = RandPhraseSimple("私の知る限り、あなたはすでにその総督から任務を与えられているようです "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Gen")+"。すでに受けている仕事を終わらせてから、話をしましょう。","ふむ、あれはお前じゃなかったか "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Voc")+" 地元の総督から指令を受けた場所か？はい、その通りです。まずはその任務を完了してください。");
					link.l1 = RandPhraseSimple("なるほど……","承知いたしました……"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".");
					link.l1.go = "exit";					
					break;
				}
				//<--Федот, да не тот
				//-------- взят квест уничтожения банды ---------->>
				if (QuestName == "DestroyGang")
				{
					switch (pchar.GenQuest.DestroyGang)
					{
						makearef(arName, pchar.GenQuest.DestroyGang);
						case "":
							dialog.text = LinkRandPhrase("盗賊を捜索する任務 "+GetFullName(arName)+" すでにあなたに発行されている。今すぐ遂行しなさい！","あなたはすでに「という名の盗賊を捜索する任務を受けております "+GetFullName(arName)+"。結果をお待ちしております！","「あなたが私の邸宅で時間を無駄にしている間に、」 "+GetFullName(arName)+" 我々の植民者を襲っておる！さっさと働け！");
							link.l1 = RandPhraseSimple("「よし、」 "+GetAddress_FormToNPC(NPChar)+".","「それに取り込んでおります」 "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("その盗賊を見つけ出して排除するために与えられた時間はすでに過ぎております。\nそして、私のもとに届いている報告はどのようなものだと思いますか？お教えしましょう―― "+GetFullName(arName)+" まだ元気に生きてるぜ！さあ、自分のことを説明しろ、 "+GetAddress_Form(NPChar)+".","あの悪党を始末するためにあなたに与えられた時間は "+GetFullName(arName)+"、もう尽きてしまいました。それでも、全く進展がないと聞いております。どうなっているのですか？");
							link.l1 = "ご指定の期間内にご依頼の仕事を完了できませんでした。 "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("それで、どうだ？私が話した盗賊を退治できたのか？ "+GetFullName(arName)+" ついに死んだのか？","一つだけ教えてくれ――それは "+GetFullName(arName)+" 生死問わずか？");
							link.l1 = "「残念ながら、まだ生きている」 "+GetAddress_FormToNPC(NPChar)+"。奴の行方は突き止めたが、相手が強すぎて退却するしかなかった。あの盗賊は手強い野郎だ。すまねえ。";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("それで、どうだ？私が話した盗賊を始末することができたのか？ "+GetFullName(arName)+" ついに死んだのか？","「一つだけ教えてくれ――」 "+GetFullName(arName)+" 生死を問わずか？");
							link.l1 = "「彼は死んだ」、 "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 180);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контркурьер ---------->>
				if (QuestName == "TakePostcureer")
				{
					switch (pchar.GenQuest.TakePostcureer)
					{
						case "":
							dialog.text = LinkRandPhrase("すでに急使船拿捕の任務を与えてあります。さあ、実行しなさい！","すでに急使船を拿捕する任務を与えてあります！結果を待っていますぞ！","あなたが私の邸宅で無駄に時間を過ごしている間に、私が必要とする書類が敵の手に渡ろうとしております！ 早く仕事に取りかかりなさい！");
							link.l1 = RandPhraseSimple("「よし、」 "+GetAddress_FormToNPC(NPChar)+".","「それに取り込んでおります」 "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("貴殿に与えた使者船を捜索し拿捕する猶予は終わった。\nそして、私が受け取っている報告がどのようなものか、分かるか？教えてやろう――私が期待していた書類は、まんまと敵の手に渡ってしまったのだ！\nさあ、弁明してもらおうか。 "+GetAddress_Form(NPChar)+".","使者船から書類を奪取するために与えられた時間はすべて尽きてしまいました。\nそれなのに、まったく進展がありません。これは一体どういうことですか？");
							link.l1 = "「私は時間内に仕事を完了できませんでした。」 "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("それで、どうだ？書類を手に入れることができたのか？","一つだけ教えてくれ——書簡の確保には成功したのか？");
							link.l1 = "「残念ながら、いいえ」 "+GetAddress_FormToNPC(NPChar)+"。船は見つけましたが、書類は手に入りませんでした。";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("それで、どうだ？書類は手に入れたのか？","一つだけ教えてくれ――書簡の確保には成功したのか？");
							link.l1 = "「はい」 "+GetAddress_FormToNPC(NPChar)+"。持っております。どうぞ。";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							RemoveItems(pchar, "ContraPostLetters", 1);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контрфрахт - арсенал ---------->>
				if (QuestName == "TakeArsenalship")
				{
					switch (pchar.GenQuest.TakeArsenalship)
					{
						case "":
							dialog.text = LinkRandPhrase("軍用輸送船を撃滅する任務はすでにあなたに与えられております。さあ、実行なさい！","すでに軍用輸送船を撃沈する任務を与えております！結果を待っておりますぞ！","貴殿が私の邸宅で無駄に時を過ごしている間にも、火薬や弾薬が敵の大砲へと直接運ばれているのです！さあ、 仕事に取りかかりなさい！");
							link.l1 = RandPhraseSimple("「よし、」 "+GetAddress_FormToNPC(NPChar)+".","「その件で忙しいのです」 "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("貴殿に与えられた軍用輸送船の捜索および撃破の期限はすでに切れております。\nそして、私の元に届いている報告は何だと思いますか？お教えしましょう――敵の護送船団は無事に目的地へ到達したのです！\nさて、弁明していただけますか。 "+GetAddress_Form(NPChar)+".","敵の軍用輸送船を撃破するために与えられた時間がすべて過ぎてしまいました。\nそれなのに、まったく進展がありません。\n一体どうなっているのですか？");
							link.l1 = "ご指定の時間内にご依頼の任務を遂行できませんでした。 "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("それで、どうだ？敵の輸送船を撃沈できたのか？","一つだけ教えてくれ――その敵の積み荷は海底に沈んでいるのか？");
							link.l1 = "「残念ながら、違います」 "+GetAddress_FormToNPC(NPChar)+"。護送船団を発見したが、指定された船を沈めることはできなかった。";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("それで、どうだ？あの敵の輸送船を沈めることができたのか？","一つだけ教えてくれ――敵の兵器庫は海の底に沈んでいるのか？");
							link.l1 = "「はい」 "+GetAddress_FormToNPC(NPChar)+"。敵にはその火薬と弾薬は渡さぬ。";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 220);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- ОЗГ - пират ---------->>
				if (QuestName == "TakePirateship")
				{
					switch (pchar.GenQuest.TakePirateship)
					{
						case "":
							dialog.text = LinkRandPhrase("すでに海賊討伐の任務を与えてある。さあ、遂行しなさい！","すでに海賊船を討伐する任務があるではないか！私はその結果を待っているぞ！","お前が私の邸宅で無駄に時間を過ごしている間に、あの汚らわしい海賊がまた別の犠牲者を食い物にしているのだ！ さっさと仕事に取りかかれ！");
							link.l1 = RandPhraseSimple("「よし、」 "+GetAddress_FormToNPC(NPChar)+".","「それに取り組んでいるところだ」 "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("海賊を見つけて討伐するために与えられた時間はもう過ぎたのです。\nさて、私がどんな報告を受け取っていると思いますか？教えて差し上げましょう――あの卑劣な海賊はいまだに我々の船を襲っているのです！\nさあ、弁明なさい。 "+GetAddress_Form(NPChar)+".","海賊船を撃破するために与えられた時間はすべて過ぎてしまいました。それなのに、まったく進展がありません。 どういうことですか？");
							link.l1 = "ご依頼の仕事を期限内に完了できませんでした。 "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("それで、どうだ？海賊船を撃沈することができたのか？","一つだけ教えてくれ――あの汚らわしい海賊は、ついに海の底で眠っているのか？");
							link.l1 = "「残念ながら、いいえ。」 "+GetAddress_FormToNPC(NPChar)+"。あの悪党の行方は突き止めたが、奴の船を沈めることはできなかった。";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("それで、どうだ？海賊船を撃沈することができたのか？","一つだけ教えてくれ――あの汚らわしい海賊はついに海の底で眠っているのか？");
							link.l1 = "「はい。」 "+GetAddress_FormToNPC(NPChar)+"。あの悪党はもう我々の商船を悩ませることはないでしょう。";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
					//-------- ОЗГ - пассажир ---------->>
				if (QuestName == "TakePassenger")
				{
					switch (pchar.GenQuest.TakePassenger)
					{
						case "":
							dialog.text = LinkRandPhrase("犯罪者を追う任務はすでに与えられている。さあ、遂行しなさい！","すでに犯罪者を捜索する任務を与えてあります！私はその結果を待っていますぞ！","あなたが私の邸宅で無駄に時を過ごしている間に、あの汚らわしい悪党はまだ航海を続けているのです！\nすぐにあなたに託された任務を遂行しなさい！");
							link.l1 = RandPhraseSimple("「よし、」 "+GetAddress_FormToNPC(NPChar)+".","「それに取り掛かっているところだ」 "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("貴殿に与えられたあの悪党を探す時間はもう終わった。\nそして、私が受け取っている報告はどのようなものだと思うか？教えてやろう――奴は無事に目的地へ到着し、その後跡形もなく姿を消したのだ！\nさあ、説明してもらおうか。 "+GetAddress_Form(NPChar)+".","犯人を見つけるために与えられた時間はすべて終わりました。\nそれなのに、まったく進展がありません。\n一体どうなっているのですか？");
							link.l1 = "「申し上げた期間内にご依頼を遂行することができませんでした。」 "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("それで、どうだ？悪党を捕まえたのか？","一つだけ教えてくれ――その汚い悪党はお前の船倉に、猿ぐつわをされて手錠をかけられているのか？");
							link.l1 = "残念ながら、違います。 "+GetAddress_FormToNPC(NPChar)+"。悪党の捕縛に失敗しました。奴は乗っていた船と共に沈みました。";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("それで、どうだ？悪党を捕まえたのか？","一つだけ教えてくれ――その汚らわしい悪党は、お前の船倉で猿ぐつわをされ、手錠をかけられているのか？");
							link.l1 = "「はい」 "+GetAddress_FormToNPC(NPChar)+"。どうか兵士たちを桟橋に送ってください、私が彼をお引き渡しいたします。";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.TakePassenger.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							sld.lifeday = 0;
						break;
					}
				}
				//-------- таможенный патруль ---------->>
				if (QuestName == "CustomPatrol")
				{
					switch (pchar.GenQuest.CustomPatrol)
					{
						case "":
							dialog.text = LinkRandPhrase("密輸業者を探し出す任務はすでにあなたに与えられている。さあ、遂行しなさい！","すでに密輸業者を探す任務を与えている！私はその結果を待っているぞ！","貴殿が私の邸宅で無駄に時を過ごしている間にも、あの密輸業者どもは次の取引の準備を進めております！\n速やかにお任せした任務に取りかかりなさい！");
							link.l1 = RandPhraseSimple("「よし、」 "+GetAddress_FormToNPC(NPChar)+".","「それに取り組んでおります」 "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("密輸業者を見つけるために与えた時間はもう終わった。\nさて、私が受け取っている報告はどんなものだと思うか？教えてやろう――やつらは喜んで全ての商品を売りさばいたそうだ！\nさあ、弁明してもらおうか。 "+GetAddress_Form(NPChar)+".","密輸業者を探すために与えられた時間はすべて過ぎてしまいました。\nそれなのに、まったく進展がありません。どういうことですか？");
							link.l1 = "ご依頼の任務を期限内に完了できませんでした。 "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("それで、どうだ？密輸業者どもは片付けたか？","一つだけ教えてくれ――密輸業者との取引を台無しにしたのか？");
							link.l1 = "「残念ですが、違います」 "+GetAddress_FormToNPC(NPChar)+"。あの悪党どもの企みを阻止できなかった。";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("それで、どうだ？密輸業者どもは片付けたか？","一つだけ教えてくれ――あの密輸業者たちの取引を台無しにしたのか？");
							link.l1 = "「はい」 "+GetAddress_FormToNPC(NPChar)+"。奴らに追いついて、買い手も売り手も両方の船を沈めてやった。";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 300);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- Дезертир ---------->>
				if (QuestName == "FindFugitive")
				{
					switch (pchar.GenQuest.FindFugitive)
					{
						case "":
							dialog.text = LinkRandPhrase("脱走兵を探す任務はすでにあなたに与えられております。さあ、遂行なさい！","すでに脱走兵を探す任務があるではないか！結果を待っておるぞ！","貴殿が私の邸宅で無駄に時を過ごしている間に、あの脱走兵が我が国の機密を裏切っているかもしれません！ 託された任務を直ちに遂行しなさい！");
							link.l1 = RandPhraseSimple("「よし、」 "+GetAddress_FormToNPC(NPChar)+".","「それに取り組んでいるところだ」 "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("脱走兵を見つけるために与えられた時間はもう終わりました。\nそして、私のもとにどんな報告が届いていると思いますか？教えて差し上げましょう――何も、まったく何もありません！\nさあ、説明していただきましょう。 "+GetAddress_Form(NPChar)+".","脱走兵を見つけるために与えられた時間がすべて過ぎてしまいました。\nそれなのに、まったく進展がありません。\n一体どうなっているのですか？");
							link.l1 = "ご依頼の仕事を期限内に完了できませんでした。 "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("それで、どうだ？脱走兵を捕まえたのか？","一つだけ教えてくれ――その脱走兵はお前の船倉に、猿ぐつわをされて手錠をかけられているのか？");
							link.l1 = "「残念ながら、違います」 "+GetAddress_FormToNPC(NPChar)+"。あの悪党を捕まえるのに失敗した。その足取りを の居住地で見つけた "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.City)+"、しかし私が到着する前日に彼は海賊船で南へ向かったんです。今ごろは運命の紳士たちと一緒にいるのでしょうね。";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("まあいいか……こちらが我々の "+pchar.GenQuest.FindFugitive.Name+"…素晴らしい働きだ、船長！捜索は大変だったか？","おや、なんと素晴らしいお客様だ！こんにちは、 "+pchar.GenQuest.FindFugitive.Name+"！素晴らしい働きだ、船長！捜索にはかなり力を入れたのか？");
							link.l1 = "「どう言うか、 "+GetAddress_FormToNPC(NPChar)+"。何であれ、あなたの任務は果たされました。";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 300);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar, "authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							LAi_SetActorType(sld);
							sld.lifeday = 0;
							pchar.quest.FindFugitive_Over.over = "yes"; //снимаем таймер
							chrDisableReloadToLocation = false;//открыть локацию
						break;
					}
				}
				//------ проникновение во враждебный город ------------>>
				if (QuestName == "Intelligence")
				{
					switch (pchar.GenQuest.Intelligence)
					{
						case "":
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								dialog.text = RandPhraseSimple("手紙を届けるために与えられた時間はもう過ぎました。つまり、あなたは失敗したということですね。","時間切れだ。それなのに、まったく進展がないじゃないか。どうしたんだ？");
								link.l1 = "ご依頼を完了できませんでした。 "+GetAddress_FormToNPC(NPChar)+".";
								link.l1.go = "All_Late";	
							}
							else
							{
								dialog.text = LinkRandPhrase("私に手紙を届ける任務はすでにあなたに与えられている。さあ、果たしなさい！","あなたにはすでに私宛ての手紙を直接届ける任務があります！私はその結果を待っていますので、 できるだけ早くその手紙が必要です！","あなたが私の邸宅で時間を無駄にしている間にも、私が切実に必要としている情報は、 私に送るはずの者の手元にあるままです！\n速やかにあなたに託した任務を遂行しなさい！");
								link.l1 = RandPhraseSimple("「よし、」 "+GetAddress_FormToNPC(NPChar)+".","すぐに取りかかります。 "+GetAddress_FormToNPC(NPChar)+".");
								link.l1.go = "exit";	
							}
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("私が待っていた手紙は届けてくれましたか？","さあ言え――持っているのか！？");
							link.l1 = "はい、持っています。我々の約束通り、あなたご本人にお届けしました。";
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								link.l1.go = "Intelligence_ExecuteLate";
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							else
							{
								link.l1.go = "All_Execute";		
								AddCharacterExpToSkill(PChar, "Leadership", 100);
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							TakeItemFromCharacter(pchar, "sicretLetter");
							DeleteAttribute(ItemsFromID("sicretLetter"), "City");
							DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
						break;
					}
				}
				break;
			}
			else
			{
				if(sti(pchar.reputation.nobility) > 41) {dialog.text = "私に託された土地で無法を取り締まるため、できる限りのことをしております。そして、 あなたのような高潔な船長には常に任務を用意しております。\nどのような任務をお望みですか？";}
				else {dialog.text = "私の権限の及ぶ土地の秩序を全力で維持しようと努めております、そしてあなたのような評判の方にも、船長、 任せたい仕事がございます。\nどのような任務であなたの才覚を発揮なさりたいですか？";}
				link.l1 = "植民地内および周辺地域の内部問題に専念したいのです。";
				link.l1.go = "GovQuestGroup1";
				link.l2 = "私は貴殿の支配領域外で行われる作戦に参加する方が好みです。";
				link.l2.go = "GovQuestGroup2";
				link.l3 = "私は国際関係に影響を及ぼし、立場を強化できるような高リスクの任務に興味があります "+ NationNameGenitive(sti(NPChar.nation))+".";
				link.l3.go = "GovQuestGroup3";
				link.l4 = "申し訳ありませんが、今は何もお引き受けしたくございません。";
				link.l4.go = "exit";
			}
			break;
			
			case "GovQuestGroup1":
			// Группа 1 - Местные
			if (CheckAttribute(npchar, "work_date") && GetNpcQuestPastDayParam(npchar, "work_date") <= 1)
			{
				dialog.text = RandPhraseSimple("本日はこの手の仕事はございません。明日また来てみてはいかがでしょうか…", 
						"あいにく、今はこの手の依頼はございません。\n一日か二日後にまた来てみてください。", 
						"今日はそのようなご負担をおかけするわけにはまいりません。また別の機会にお会いできれば嬉しいです。");
				link.l1 = "承知いたしました。 "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "exit";
				break;
			}
			pchar.GenQuest.Governor.Group1.index = hrand(2);
			i = pchar.GenQuest.Governor.Group1.index;
			switch (i)
			{
				case 0: // Отказ
					dialog.text = RandPhraseSimple("本日はこの手の仕事はございません。明日また来ていただけますか…", 
							"申し訳ありませんが、今のところこの種の依頼はございません。\n一日か二日後にまたお越しください。", 
							"今日はそのようなご負担をおかけするわけにはまいりません。また別の機会にお会いできれば嬉しいです。");
					link.l1 = RandPhraseSimple("「哀れだな……」","「ああ、なんと残念なことだ」 "+GetAddress_FormToNPC(NPChar)+". ");
					link.l1.go = "exit";
				break;
						
				case 1: // Таможенный патруль
					if (CheckAttribute(pchar, "GenQuest.Governor.Group1.day") && sti(pchar.GenQuest.Governor.Group1.day) == GetDataDay())
					{
						dialog.text = "気が変わったのか、船長？密輸業者どもはまだ野放しだし、どうせ計画を諦めちゃいねえだろうぜ。";
						link.l1 = "この任務の詳細をもう一度ご説明いただけますか、閣下。";
						link.l1.go = "CustomPatrol";
						link.l2 = RandPhraseSimple("申し訳ありませんが、今はこの任務を引き受ける準備ができておりません。", 
						"申し訳ありませんが、今はこの任務を遂行できません。", 
						"申し訳ありません——まだこの任務を引き受ける準備ができておりません。");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "ちょうどいい時に来てくれたな、船長。わが植民地への密輸品に関する緊急の問題を処理しなければならんのだ。 君の船は航海に耐え、戦闘の準備もできているのだろうな？";
					link.l1 = "私の船はいつでも航海可能で、戦闘の準備も万端でございます。どうか、 これからの任務について詳しくお聞かせくださいませ、閣下。";
					link.l1.go = "CustomPatrol";
				break;
						
				case 2: // Уничтожение банды
					if (CheckAttribute(pchar, "GenQuest.Governor.Group1.day") && sti(pchar.GenQuest.Governor.Group1.day) == GetDataDay())
					{
						dialog.text = "結局、盗賊討伐の任務を引き受ける決心をされたのですね、船長。\n残念ながら、彼らはいまだに我が植民地の安寧を脅かしております。";
						link.l1 = "「この任務の詳細をもう一度ご説明いただけますか、閣下。」";
						link.l1.go = "DestroyGang";
						link.l2 = RandPhraseSimple("申し訳ありませんが、今はこの任務を引き受ける準備ができておりません。", 
						"申し訳ありませんが、今はこの任務を遂行できません。", 
						"申し訳ありません――まだこの任務を引き受ける準備ができておりません。");
						link.l2.go = "exit";
						break;
					}
					pchar.GenQuest.DestroyGang.Terms = hrand(2) + 2;
					pchar.GenQuest.DestroyGang.Money = ((hrand(6)+4)*500)+5000+(sti(pchar.rank)*500);
					makearef(arName, pchar.GenQuest.DestroyGang);
					arName.nation = PIRATE;
					arName.sex = "man";
					SetRandomNameToCharacter(arName);
					dialog.text = "ただいま、あなたに任務があります。近くのジャングルで "+XI_ConvertString("Colony"+npchar.city+"Gen")+" 盗賊団が現れ、その首領の名前がわかっているんだ\n "+GetFullName(arName)+"。この暴漢どもを見つけ出して始末してください。";
					link.l1 = "私の条件に何か制限がありますか？";
					link.l1.go = "DestroyGang";
				break;
			}
		break;

		case "GovQuestGroup2":
			// Группа 2 - За границами острова, но не государственные
			if (CheckAttribute(npchar, "work_date") && GetNpcQuestPastDayParam(npchar, "work_date") <= 1)
			{
				dialog.text = RandPhraseSimple("本日はこの手の仕事はございません。また明日お越しくださいませ…", 
						"残念ながら、今はこの手の依頼はございません。\n一日か二日後にまた来てみてください。", 
						"今日はそのようなお願いはできません。また別の機会にお会いできれば嬉しいです。");
				link.l1 = RandPhraseSimple("「残念だ……」","「ああ、残念ですわ」 "+GetAddress_FormToNPC(NPChar)+". ");
				link.l1.go = "exit";
				break;
			}
			pchar.GenQuest.Governor.Group2.index = hrand(3);
			i = pchar.GenQuest.Governor.Group2.index;
			switch (i)
			{
				case 0: // Нет заданий
					dialog.text = RandPhraseSimple("本日はこの手の仕事はございません。明日またお越しくださいませ…", 
							"あいにく、今はこの種の依頼はございません。\n一日か二日後にまた来てみてください。", 
							"今日はそのようなご負担をおかけするわけにはまいりません。また別の機会にお目にかかれるのを楽しみにしております。 ");
					link.l1 = RandPhraseSimple("「残念だ……」","「ああ、なんと残念だ」 "+GetAddress_FormToNPC(NPChar)+". ");
					link.l1.go = "exit";
				break;
						
				case 1:  // ОЗГ - захватить пассажира
					if (CheckAttribute(pchar, "GenQuest.Governor.Group2.day") && sti(pchar.GenQuest.Governor.Group2.day) == GetDataDay())
					{
						dialog.text = "自分を証明するチャンスを逃さないと決めたのか？あの悪党は生きたまま、できるだけ早く連れてきてほしい。";
						link.l1 = "「この任務の詳細をもう一度ご説明いただけますか、閣下。」";
						link.l1.go = "TakePassenger";
						link.l2 = RandPhraseSimple("申し訳ありませんが、今はこの任務を引き受ける準備ができておりません。", 
						"申し訳ありませんが、今はこの任務を遂行できません。", 
						"申し訳ありません——まだこの任務を引き受ける準備ができておりません。");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "ちょうどいいところに来てくれました、旦那。あなたにぴったりの緊急任務があります。ある人物を捜索し、 捕らえていただきたいのです……";
					link.l1 = "人狩りですか？私に何を期待しているのか、もう少し詳しく教えていただけますか？";
					link.l1.go = "TakePassenger";
				break;
						
				case 2: // Найти дезертира
					if (CheckAttribute(pchar, "GenQuest.Governor.Group2.day") && sti(pchar.GenQuest.Governor.Group2.day) == GetDataDay())
					{
						dialog.text = "気が変わったのか、船長？結局逃亡者を追うことにしたのか？";
						link.l1 = "この任務の詳細をもう一度ご説明いただけますか、閣下。";
						link.l1.go = "FindFugitive";
						link.l2 = RandPhraseSimple("申し訳ありませんが、今はこの任務を引き受ける準備ができておりません。", 
							"申し訳ありませんが、今はこの任務を遂行できません。", 
							"申し訳ありません――まだこの任務を引き受ける準備ができておりません。");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "カリブ海のいくつかの植民地を訪れる任務を君に頼みたい。\n長い旅の準備はできているか？";
					link.l1 = "はい、私と部下たちはすぐに出発する準備ができております。\n具体的には何をすればよろしいのでしょうか？";
					link.l1.go = "FindFugitive";
				break;
						
				case 3: // Уничтожить корабль пиратов
					if (CheckAttribute(pchar, "GenQuest.Governor.Group2.day") && sti(pchar.GenQuest.Governor.Group2.day) == GetDataDay())
					{
						dialog.text = "海賊はまだ商船を襲っています、船長。今回はしっかり対処していただけますか？";
						link.l1 = "この任務の詳細をもう一度ご説明いただけますか、閣下。";
						link.l1.go = "TakePirateship";
						link.l2 = RandPhraseSimple("申し訳ありませんが、今はこの任務を引き受ける準備ができておりません。", 
						"申し訳ありませんが、今はこの任務を遂行できません。", 
						"申し訳ありません――私はまだこの任務を引き受ける準備ができておりません。");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "はい、あなたに重要な任務があります。それを果たすには、あなたのすべての技能を駆使しなければなりません。 これは海賊が関わっております…";
					link.l1 = "海賊たち？それでは、私に何を期待しているのか、もう少し詳しく教えていただけますか？";
					link.l1.go = "TakePirateship";
				break;
			}
		break;

		case "GovQuestGroup3":
			// Группа 3 - Государственные разборки, тяжелые бои
			if (CheckAttribute(npchar, "work_date") && GetNpcQuestPastDayParam(npchar, "work_date") <= 1)
			{
				dialog.text = RandPhraseSimple("本日はこの手の仕事はございません。明日また来てみてはいかがでしょうか…", 
						"残念ながら、今はこの手の依頼はございません。\n一日か二日後にまた来てみてください。", 
						"今日はそのようなご負担をおかけするわけにはまいりません。また別の機会にお会いできれば嬉しいです。");
				link.l1 = RandPhraseSimple("「哀れだな……」","「ああ、残念ですわ」 "+GetAddress_FormToNPC(NPChar)+". ");
				link.l1.go = "exit";
				break;
			}
			pchar.GenQuest.Governor.Group3.index = hrand(3);
			i = pchar.GenQuest.Governor.Group3.index;
			switch (i)
			{
				case 0: // Отказ
					dialog.text = RandPhraseSimple("本日はこの手の仕事はございません。明日また来ていただけますか……", 
							"残念ながら、今はこの種の依頼はございません。\n一日か二日後にまたお越しください。", 
							"今日はそのようなことをあなたにお願いするわけにはいきません。また別の機会にお会いできれば嬉しいです。");
					link.l1 = RandPhraseSimple("「残念だな……」","「ああ、残念ですわ」 "+GetAddress_FormToNPC(NPChar)+". ");
					link.l1.go = "exit";
				break;
						
				case 1: // Контркурьер
					if (CheckAttribute(pchar, "GenQuest.Governor.Group3.day") && pchar.GenQuest.Governor.Group3.day == GetDataDay())
					{
						dialog.text = "時間がなくなってきたぞ。やるのか、それともまた世間話しに来ただけか？";
						link.l1 = "「この任務の詳細をもう一度ご説明いただけますか、閣下。」";
						link.l1.go = "TakePostcureer";
						link.l2 = RandPhraseSimple("申し訳ありませんが、今はこの任務を引き受ける準備ができておりません。", 
						"申し訳ありませんが、今はこの任務を遂行できません。", 
						"申し訳ありません――まだこの任務を引き受ける準備ができておりません。");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "はい、あなたに任務があります。その達成には素早さと海戦の腕前が必要となります。 ご自身の価値を証明するご準備はできていますか？";
					link.l1 = "閣下、この任務についてもう少し詳しく教えていただけますか？";
					link.l1.go = "TakePostcureer";
				break;
						
				case 2: // Контрфрахт - уничтожить корабль с арсеналом
					if (CheckAttribute(pchar, "GenQuest.Governor.Group3.day") && pchar.GenQuest.Governor.Group3.day == GetDataDay())
					{
						dialog.text = "とうとう勇気を出したのですね、船長？敵の補給線を叩く準備はできましたか？";
						link.l1 = "この任務の詳細をもう一度ご説明いただけますか、閣下。";
						link.l1.go = "TakeArsenalship";
						link.l2 = RandPhraseSimple("申し訳ありませんが、今はこの任務を引き受ける準備ができておりません。", 
						"申し訳ありませんが、今はこの任務を遂行できません。", 
						"申し訳ありません——この任務を引き受ける準備はまだできておりません。");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "はい、あなたに任務があります。この任務を果たすには、並外れた勇気と海戦の腕前を示していただく必要がございます。 ご自身の価値を証明するご覚悟はできておりますか？";
					link.l1 = "閣下、これからの任務についてもう少し詳しく教えていただけますか？";
					link.l1.go = "TakeArsenalship";;
				break;
						
				case 3: // Проникновение во враждебный город
					if (CheckAttribute(pchar, "GenQuest.Governor.Group3.day") && pchar.GenQuest.Governor.Group3.day == GetDataDay())
					{
						dialog.text = "この任務についてはすでにお尋ねになりましたね、船長。今回は単なる興味本位ではないことを願っておりますが？";
						link.l1 = "この任務の詳細をもう一度ご説明いただけますか、閣下。";
						link.l1.go = "Intelligence";
						link.l2 = RandPhraseSimple("申し訳ありませんが、今はこの任務を引き受ける準備ができておりません。", 
						"申し訳ありませんが、今はこの任務を遂行できません。", 
						"申し訳ありません――まだこの任務を引き受ける準備ができておりません。");
						link.l2.go = "exit";
						break;
					}
					sTemp = GetSpyColony(npchar);
					if (sTemp == "none")
					{
						dialog.text = RandPhraseSimple("本日はこの手の仕事はございません。明日またお越しくださいませ…", 
								"残念ながら、今はこの種の依頼はございません。\n一日か二日後にまた来てみてください。", 
								"今日はそのようなご負担はおかけできません。また別の機会にお会いできれば嬉しいです。");
						link.l1 = "承知いたしました。 "+GetAddress_FormToNPC(NPChar)+".";
						link.l1.go = "exit";
						break;
					}
					pchar.GenQuest.Intelligence.Terms = hrand(10) + (42 - MOD_SKILL_ENEMY_RATE);
					pchar.GenQuest.Intelligence.Money = ((hrand(5)+11)*2000)+(sti(pchar.rank)*1500);
					pchar.GenQuest.Intelligence.City = sTemp;
					sTemp = ", which is on " + XI_ConvertString(GetIslandByColony(&colonies[FindColony(pchar.GenQuest.Intelligence.City)])+"Dat");
					dialog.text = "あなたに任務がありますが、かなりの危険を伴います。潜入してほしいのです "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc")+sTemp+"、そこである人物に会い、その者が渡す物を私に届けてください。";
					link.l1 = "ふむ、その中ではないと思うが "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" 私は歓迎される客人となりましょう……";
					link.l1.go = "Intelligence";
				break;
			}
		break;
		//---------------------------- генератор квестов мэра -------------------------------

		case "sell_prisoner":
            dialog.text = "誰を身代金で解放したいのですか？";

            qty = 1;
            for(i=0; i < GetPassengersQuantity(pchar); i++)
            {
                cn = GetPassenger(pchar,i);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if(CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                            attrLoc = "l"+qty;
                            link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
                            link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                            qty++;
                        }
                    }
                }
            }
			link.l99 = "誰もいない。";
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  "So, this is captain " + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation))+ ".";
            // цена зависит от губернатора
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
			if(HasShipTrait(pchar, "trait14")) qty = makeint(qty * 1.35);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
                attrLoc = attrLoc + " I am ready to pay the ransom for my compatriot in the amount of  " + FindRussianMoneyString(qty) + ".";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
                    attrLoc = attrLoc + " I can give " + FindRussianMoneyString(qty) + "  for this gallowsbird. And then we'll execute the scoundrel at once.";

                }
                else
                {
                    qty = qty / 2;
                    attrLoc = attrLoc + " " + FindRussianMoneyString(qty) + "for that man, not a peso more.";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = "「取引成立だ。あとはお前の好きにしろ。」 "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = "いいえ。それでは困ります。";
			link.l3.go = "exit";
		break;


		case "sell_prisoner_3":
			dialog.text = "それは良いことです。";
			link.l1 = "ごきげんよう。";
			link.l1.go = "exit";
			OfficersReaction("bad");

			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
			if (sti(offref.nation) == sti(NPChar.nation))
            {
                AddCharacterExpToSkill(pchar, "Commerce", 25);
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    ChangeCharacterComplexReputation(pchar,"nobility", -2);
                }
                else
                {
                    AddCharacterExpToSkill(pchar, "Commerce", 5);
                }
            }

        	offref.location = "";
        	ReleasePrisoner(offref); // освободили пленника
		break;
		////   CAPTURE //////////
		case "CAPTURE_Main":
            NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // всё, все свободны
			
			// --> Левассер
			if (pchar.location == "Tortuga_townhall" && CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga"))
			{
                dialog.Text = "「うおおっ！これは一体どういうことだ、ド・モール！？フランス人が自国の仲間を襲うなんて、 いつからそんなことになったんだ！？」";
                Link.l1 = "総督フランソワ・ロンヴィリエ・ド・ポワンシーの命令により、ルヴァスール旦那、 あなたはトルトゥーガ総督の職を解かれ、死刑を宣告される！\nそして、この判決を執行するのは私でございます！";
                Link.l1.go = "levasser";
				break;
			}
			// <-- Левассер
            // fix от грабежа 5 раз на дню -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
                dialog.Text = "お前はもうすべて奪っただろう。これ以上何を望むんだ？";
                Link.l1 = "ああ、そうだな、間違った街だぜ。";
                Link.l1.go = "Exit_City";

                NPChar.NoGiveMoney = true;

            	ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
                // вернём диалог после разговора и спрячем
                SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix от грабежа 5 раз на дню <--

            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
            { // а форт-то ЖИВ, значит с суши прошли
                dialog.Text = "前代未聞の無礼だ！すぐに砦から援軍が来るぞ、貴様はその報いを受けることになる！";
                Link.l2 = "私は彼らが来るまでここにいるつもりはありません。\nさっさと報酬を払ってくれ、そしたらこの町を出るぜ。";
                Link.l2.go = "Summ";
                Pchar.HalfOfPaymentByCity = true; // токо половина денег
            }
            else
            {
				dialog.Text = "今回はお前の勝ちだが、我々の海賊狩りの艦隊が必ずお前を追い詰めて、 その汚い海賊の身からペソを一枚残らずむしり取ってやるからな！";
	            if (!bWorldAlivePause || bBettaTestMode)
	            {
	                int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
	    				{
	    					Link.l1 = "静かにしろ！この町は今から俺のものだ。お前らの海賊狩りどもなんざ、 デイヴィ・ジョーンズの棺桶に直行させてやるぜ。\nおい野郎ども、この豚を捕まえて牢にぶち込め！";
	    				}
	    				else
	    				{
	    					Link.l1 = "この街はもう俺のものだ。野郎ども、元総督を新しい「部屋」まで案内してやれ、へっへっへ。";
	    				}
	    				Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
	            {
	                Link.l2 = "砦からの援軍だと？たっぷり身代金を払ってくれりゃ、俺たちは町を出てやるぜ。";
				}
				else
				{
	            	Link.l2 = "海賊狩りの艦隊だと？ふん……金さえ払えば、俺たちはあんたの町から出ていくぜ。";
	            }
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
	            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
	            {
					// восстановим нацию патента
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = "前代未聞の無礼だ！よくも の植民地を攻撃したな "+NationNameGenitive(sti(NPChar.nation))+"？！貴様が流した血と我が国に与えた損害、その代償は高くつくぞ。";
	                Link.l1 = "今この瞬間から、この植民地は俺のものだ。俺の権威に逆らう奴は、地獄行きだぜ。";
	                Link.l1.go = "City_patent";
	                Link.l2 = "下がれ。私は～の名のもとに行動している "+NationNameGenitive(sti(PChar.nation))+"。これより、この植民地は "+NationKingsCrown(PChar)+"!";
	                Link.l2.go = "City_nation";
	                Link.l3 = "素敵な町だな。もしこの町が焼け野原になり、総督が広場で吊るされるなんてことになったら、本当に悲劇だぜ。 そうならないために、いくら身代金を払う気があるのか、話し合おうじゃねえか。 ";
	                Link.l3.go = "Summ_patent";
	            }
            }
        break;
		
		// --> Левассер
		case "levasser":
            dialog.Text = "ポワンシーだと！？くそったれなカトリック野郎め！俺がケリをつけてやる……そして貴様、ろくでなし、お前もこれで終わりだ！ここから生きては出られねえ――この俺が直々に息の根を止めてやる！";
			Link.l1 = "説教は結構だ、異端者め。貴様のユグノーの魂を地獄に送るときは、 ルシファーとジャン・カルヴァンによろしく伝えてくれ。覚悟しろ！";
			Link.l1.go = "levasser_1";
        break;
		
		case "levasser_1":
			chrDisableReloadToLocation = true;//закрыть локацию
            DialogExit();
			LAi_SetImmortal(npchar, false);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto6");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LevasserDiedResidence");
			AddDialogExitQuest("MainHeroFightModeOn");	
        break;
		// <-- Левассер
        
        case "City":
            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 400);

            Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
            AddDialogExitQuest("Residence_Captured_Any");

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            // ремонт
            RepairAllShips();
            Log_Info("All ships have been repaired.");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
            NextDiag.CurrentNode = "Prison";
			DialogExit();
        break;

        case "City_patent":
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -20); // пираты мы, но у нас патент
            dialog.Text = "今回はお前の勝ちだが、我々の戦隊がすぐに到着して、お前たちを跡形もなく消し去ることを知っておけ！";
			Link.l1 = "黙れ。この町はこれから俺のものだ。お前の艦隊も地獄に送ってやるぜ。\n野郎ども、元総督を新しい“部屋”までご案内してやれ、へっへっへ。";
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = "私に他に何かご用ですか？";
            Link.l1 = "何か見落としたことがないか、ちょっと確認しているだけだ…";
            Link.l1.go = "exit";

            NextDiag.TempNode = "Exit_for_pay";
		break;

        case "Exit_City":
		    NextDiag.CurrentNode = "Exit_for_pay";
		    Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		    if (sti(NPChar.NoGiveMoney) == false) // себе берем
		    {
				// вернём диалог после разговора и спрячем
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
            }
            DialogExit();
        break;

        case "Summ":
            dialog.Text = "あなたの条件に同意するしかありません。さっさとこの血塗られた金を持って、我々の植民地から立ち去ってください。";
            Link.l1 = "お取引できて光栄です。";
            Link.l1.go = "Exit_City";
            NPChar.NoGiveMoney = false;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
            AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 300);
            AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 300);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
        break;

        case "Summ_patent":
            dialog.Text = "よし、条件を述べてくれ……";
            Link.l1 = "ああ、vae victis（敗者に災いあれ）！金を数え始めな。";
            Link.l1.go = "Summ";
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -10); // не на службе
        break;

        case "City_nation":
			dialog.Text = "わかった、お前の慈悲に身を委ねるぜ。";
			Link.l1 = "できるだけ早く町を離れることをお勧めします――これからの変化はあなたの健康にとって非常に悪いものになるかもしれません。ごきげんよう。";
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", 5);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 600);
            AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 400);
            SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

            PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
            //  СЖ -->
	    	sTemp =  GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			//  СЖ <--
			AddTitleNextRate(sti(PChar.nation), 1);  // счетчик звания
            SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// нечего не даёт, тк работает OtherChar - а это губер, но он и так друг
            UpdateRelations();

            // 22.03.05  fix вернём диалог после разговора и спрячем
            //  внутри диалога не работало
            SetReturn_Gover_Dialog_Exit(NPChar);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
	    break;
	    
	    case "Prison":
			dialog.Text = "俺にまだ何を望んでやがるんだ、この悪党め？";
            Link.l3 = "閣下は新しいお部屋をお気に召されましたか？十分に広うございますか？それでは、私はこれで失礼いたします！";
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = "「和解する？それはどういうつもりだ？」";
            link.l1 = "「私が思うに、金額は」 "+iTotalTemp*6000+" ペソがまだ俺を救えるはずだろ、そうじゃねえか？";
			link.l1.go = "arestFree_2";
			link.l2 = "いいや。そろそろ失礼する時間だ。ごきげんよう。";
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= hrand(7) && iTotalTemp < 21)
            {
    			dialog.text = "このような形で我々の事件を解決することもできましょう。 まだ事態を取り返しのつかないところまで悪化させてはいません。";
    		    link.l1 = "素晴らしいです。とても嬉しく思います。どうぞ、私の寄付をお受け取りください。";
    		    link.l1.go = "Exit";
    		    AddMoneyToCharacter(pchar, -iTotalTemp*6000);
    		    ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -iTotalTemp);
    		    AddCharacterExpToSkill(pchar, "Fortune", 100);
            }
            else
            {
    			dialog.text = "私に賄賂を渡そうとしているのか？なんてことだ！お前の悪行はただ一つの方法でしか償えぬ……衛兵！連れて行け "+GetSexPhrase("彼","彼女")+" 錨を下ろせ！";
    		    link.l1 = "「待て！」";
    		    link.l1.go = "arest_2";
    		    AddCharacterExpToSkill(pchar, "Fortune", 10);
            }
		break;

		case "arest_1":
			dialog.text = "もちろん、時間です。お見送りいたしましょう。\n護衛たち！捕らえよ "+GetSexPhrase("彼","彼女")+"!";
		    link.l1 = "ありえねえ！";
		    link.l1.go = "fight";
		break;

		case "arest_2":
			dialog.text = "十分に考える時間はあっただろう！衛兵！";
			link.l1 = "俺を簡単には捕まえられねえぞ！";
		    link.l1.go = "fight";
		break;    
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение банды
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			pchar.GenQuest.Governor.Group1.day = GetDataDay();
			dialog.text = "もちろんでございます。この任務を遂行するために、あなたにお渡しするのは "+FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms))+"、そして成功した暁には、あなたへの報酬は "+FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money))+".";
			link.l1 = "ああ、この任務、引き受けるぜ。";
		    link.l1.go = "DestroyGang_agree";
			link.l2 = "うーん……いや、遠慮しておくよ。";
		    link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //тип квеста
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //определяем локацию,где банда
			pchar.GenQuest.DestroyGang.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			if (pchar.GenQuest.DestroyGang.Location == "none") //на всякий случай
			{
				dialog.text = "待ってくれ、昨日の報告を思い出した。要するに、この一味はすでに我々の島を離れてしまったんだ。だから、 この任務は中止せざるを得ない。";
				link.l1 = "なるほど。残念です。";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = "よし、素晴らしい！君と君の報告を私の邸宅で待っているぞ。";
				link.l1 = "「長くはお待たせしません」 "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "exit";
				pchar.quest.DestroyGang.win_condition.l1 = "location";
				pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
				pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
				pchar.quest.DestroyGang.again = true; //тупо дожидаться своего часа бандиты не будут
				SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
				//==> энкаунтеров в квестовой локации не будет 
				locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "1");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				makearef(arName, pchar.GenQuest.DestroyGang);
				AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контркурьер
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePostcureer":
			//установка параметров
			pchar.GenQuest.questName = "TakePostcureer"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index)); //вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("本日はあなたにお仕事をお出しできません。","本日はもうあなたに頼める仕事は残っておりません。","本日はもう仕事はありません、申し訳ありません。明日また来ていただければ、どうなるか見てみましょう…");
				link.l1 = RandPhraseSimple("「残念だ……」","「ああ、残念ですわ」 "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePostcureer.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakePostcureer.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakePostcureer.Island = GetArealByCityName(pchar.GenQuest.TakePostcureer.City);
			pchar.GenQuest.TakePostcureer.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePostcureer.Island)+5;
			pchar.GenQuest.TakePostcureer.LoginDay = sti(pchar.GenQuest.TakePostcureer.Terms)-1;
			pchar.GenQuest.TakePostcureer.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePostcureer.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePostcureer.Nation));
			pchar.GenQuest.TakePostcureer.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePostcureer.ShipType));
			pchar.GenQuest.TakePostcureer.Money = ((hrand(5)+hrand(6, "1")+42)*600)+(sti(pchar.rank)*1600);
			pchar.GenQuest.Governor.Group3.day = GetDataDay();
			dialog.text = "もちろんです。そのためには、の運び船を見つける必要があります "+NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation))+" 『という名の』"+pchar.GenQuest.TakePostcureer.ShipName+"「乗り込んで船長室で見つかるはずの書類を持ってきてくれ。この船は近くを通るはずだ」 "+XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen")+" おおよそ "+FindRussianDaysString(pchar.GenQuest.TakePostcureer.Terms)+".";
			link.l1 = "よし、この任務を引き受けよう。で、俺が探すべき書類ってどんなものだ？";
		    link.l1.go = "TakePostcureer_agree";
			link.l2 = "ふむ……いや、遠慮しておくよ。";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePostcureer_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePostcureer.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "郵便だ。私にとって非常に重要な書類がある。だが、書類を一つ一つ探す必要はない、 全部まとめて私のところに持ってきてくれればいい。報酬は支払う。 "+FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money))+"\nそれでは、あなたとその成果を私の邸宅でお待ちしております。";
			link.l1 = "「長くはお待たせしません」 "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.quest.TakePostcureer.win_condition.l1 = "location";
			pchar.quest.TakePostcureer.win_condition.l1.location = pchar.GenQuest.TakePostcureer.Island;
			pchar.quest.TakePostcureer.win_condition.l2 = "Timer";
			pchar.quest.TakePostcureer.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakePostcureer.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.function = "TakePostcureer_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePostcureer.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "3");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePostcureer.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePostcureer.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контрфрахт - уничтожить корабль с арсеналом
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakeArsenalship":
			//установка параметров
			pchar.GenQuest.questName = "TakeArsenalship"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("本日はお仕事をご用意できません。","本日はもうあなたに頼む仕事は残っておりません。","本日はもう仕事はありません、申し訳ありません。明日また来ていただければ、どうなるか見てみましょう…");
				link.l1 = RandPhraseSimple("「哀れだな……」","「ああ、残念ですわ」 "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakeArsenalship.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakeArsenalship.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakeArsenalship.Island = GetArealByCityName(pchar.GenQuest.TakeArsenalship.City);
			pchar.GenQuest.TakeArsenalship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakeArsenalship.Island)+5;
			pchar.GenQuest.TakeArsenalship.LoginDay = sti(pchar.GenQuest.TakeArsenalship.Terms)-1;
			pchar.GenQuest.TakeArsenalship.ShipType = SelectArsenalShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.TakeArsenalship.ShipTypeA = SelectArsenalShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.TakeArsenalship.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakeArsenalship.Nation));
			pchar.GenQuest.TakeArsenalship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipType));
			pchar.GenQuest.TakeArsenalship.CannonA = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipTypeA)); // Addon 2016-1 Jason пиратская линейка
			pchar.GenQuest.TakeArsenalship.Money = ((hrand(5)+hrand(6, "1")+36)*700)+(sti(pchar.rank)*1600);
			pchar.GenQuest.Governor.Group3.day = GetDataDay();
			dialog.text = "もちろんでございます。軍用輸送船を見つけていただく必要がございます "+NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation))+"、火薬と弾薬を積んでいる。その船の名は『"+pchar.GenQuest.TakeArsenalship.ShipName+"「見つけて破壊せよ。そうすれば敵を弱体化できる\n輸送船は護衛付きで植民地へ向かう」 "+XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City)+"、そしておおよそ～にいるだろう "+FindRussianDaysString(pchar.GenQuest.TakeArsenalship.Terms)+"、だから急いだほうがいい。";
			link.l1 = "承知しました、引き受けましょう。\nその軍艦を沈めればいいのか、それとも拿捕を狙うべきですか？";
		    link.l1.go = "TakeArsenalship_agree";
			link.l2 = "ふむ……いや、今回は遠慮しておこう。";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakeArsenalship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakeArsenalship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "俺は気にしねえ、どうするかはお前次第だ。\n大事なのは、この積み荷を目的地に到達させないことだぜ。\nうまくやったら、報酬は払う。 "+FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money))+"「……もうこれ以上、あなたを引き止めません、船長。」";
			link.l1 = "「長くはお待たせしません」 "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.quest.TakeArsenalship.win_condition.l1 = "location";
			pchar.quest.TakeArsenalship.win_condition.l1.location = pchar.GenQuest.TakeArsenalship.Island;
			pchar.quest.TakeArsenalship.win_condition.l2 = "Timer";
			pchar.quest.TakeArsenalship.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakeArsenalship.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.function = "TakeArsenalship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakeArsenalship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "8");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakeArsenalship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakeArsenalship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - уничтожить корабль пиратов
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePirateship":
			//установка параметров
			pchar.GenQuest.questName = "TakePirateship"; //тип квеста
			pchar.GenQuest.TakePirateship.City = FindQuestCity(npchar, "all", -1, true, true); // belamour legendary edition 
			pchar.GenQuest.TakePirateship.Island = GetArealByCityName(pchar.GenQuest.TakePirateship.City);
			pchar.GenQuest.TakePirateship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePirateship.Island)+5;
			pchar.GenQuest.TakePirateship.ShipType = SelectPirateShipType();
			pchar.GenQuest.TakePirateship.ShipName = GenerateRandomNameToShip(PIRATE);
			pchar.GenQuest.TakePirateship.Name = GenerateRandomName(PIRATE, "man");
			pchar.GenQuest.TakePirateship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePirateship.ShipType));
			pchar.GenQuest.TakePirateship.Money = ((hrand(5) + hrand(6, "1")+4)*800)+13000+(sti(pchar.rank)*1250);
			pchar.GenQuest.Governor.Group2.day = GetDataDay();
			dialog.text = "もちろんです。ある海賊船長の行いには本当に憤慨しております。その名は "+pchar.GenQuest.TakePirateship.Name+"。あの悪党め、我々の商船を襲っており、植民地間の交易に甚大な被害を与えているのだ。 今こそあの野郎を始末する絶好の機会だ、なぜなら今やつがどこに隠れているか、私には分かっているからな。そなた、 このろくでなしを神の裁きの座へ送る覚悟はできているか？";
			link.l1 = "光栄です！その海賊はどこで見つけられますか？";
		    link.l1.go = "TakePirateship_agree";
			link.l2 = "ふむ……いや、今回は遠慮しておこう。";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePirateship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePirateship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "「最寄りの」 "+FindRussianDaysString(pchar.GenQuest.TakePirateship.Terms)+" 「彼の船の名は『」"+pchar.GenQuest.TakePirateship.ShipName+"「」は近くの沿岸を巡航する予定だ "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+"。奴を見つけて殺せ。奴の船ごと魚の餌にしても、乗り込んで奪っても構わん。私が望むのは、あの忌々 しい海賊がこの海を汚すのを止めることだけだ\nこの任務のためなら、あなたに報酬を支払う用意がある "+FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money))+"。時間を無駄にしてはなりませんぞ、船長。この悪党は であなたを待ってはくれませんぞ "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+"。行きなさい、神のご加護がありますように！";
			link.l1 = "「もう錨を上げるのか」 "+GetAddress_FormToNPC(NPChar)+"！すぐに待たせはしません。";
			link.l1.go = "exit";
			pchar.quest.TakePirateship.win_condition.l1 = "location";
			pchar.quest.TakePirateship.win_condition.l1.location = pchar.GenQuest.TakePirateship.Island;
			pchar.quest.TakePirateship.function = "TakePirateship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePirateship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "9");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePirateship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePirateship.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePirateship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - захватить пассажира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePassenger":
			//установка параметров
			pchar.GenQuest.questName = "TakePassenger"; //тип квеста
			pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));//вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("本日はあなたにお仕事をお出しできません。","本日はもうあなたにお任せできる仕事は残っておりません。","本日はもう仕事はありません、申し訳ありません。明日また来ていただければ、どうなるか見てみましょう…");
				link.l1 = RandPhraseSimple("「残念だ……」","「ああ、残念ですわ」 "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePassenger.City = FindQuestCity(npchar, "enemy", sti(pchar.GenQuest.TakePassenger.Nation), false, false); // belamour legendary edition
			pchar.GenQuest.TakePassenger.CityA = SelectAnyColony(pchar.GenQuest.TakePassenger.City);
			pchar.GenQuest.TakePassenger.Terms1 = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, GetArealByCityName(pchar.GenQuest.TakePassenger.City));
			pchar.GenQuest.TakePassenger.Terms2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.TakePassenger.City), GetArealByCityName(pchar.GenQuest.TakePassenger.CityA))+1;
			pchar.GenQuest.TakePassenger.Terms = sti(pchar.GenQuest.TakePassenger.Terms1)+sti(pchar.GenQuest.TakePassenger.Terms2);
			pchar.GenQuest.TakePassenger.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePassenger.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePassenger.Nation));
			pchar.GenQuest.TakePassenger.Name = GenerateRandomName(sti(pchar.GenQuest.TakePassenger.Nation), "man");
			pchar.GenQuest.TakePassenger.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePassenger.ShipType));
			pchar.GenQuest.TakePassenger.Money = ((hrand(5) + hrand(6, "1")+4)*500)+12500+(sti(pchar.rank)*1000);
			pchar.GenQuest.Governor.Group2.day = GetDataDay();
			string sText = SelectPassText();
			dialog.text = "もちろんです。私が言っているのは、"+pchar.name+"という名の悪党のことです "+pchar.GenQuest.TakePassenger.Name+". "+sText+" 私は長い間彼を探しておりましたが、ついに彼の居場所について確かな情報を手に入れました。\nあなたには、何としても生きたままその男を私のもとへ連れてきていただきたいのです。\n私は町の広場で彼を公開処刑したいと思っております。\nこの任務を引き受けるご覚悟はおありですか？";
			link.l1 = "準備はできております。 "+GetAddress_FormToNPC(NPChar)+"。その悪党はどこにいるんだ？";
		    link.l1.go = "TakePassenger_agree";
			link.l2 = "ふむ……いや、今回は遠慮しておこう。";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePassenger_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePassenger.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "ただいま "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms1)+"、彼は『という名の船の乗客として"+pchar.GenQuest.TakePassenger.ShipName+"「」、出航する "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen")+" そして向かい "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc")+"。あなたは "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms)+" 指定された航路でこの船を見つけて乗り込み、あの野郎を捕まえろ。指示通りにやれば、報酬を支払おう "+FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money))+"。ご武運を、船長！";
			link.l1 = "これ以上時間を無駄にはしません。 "+GetAddress_FormToNPC(NPChar)+"！すぐに出航いたします。";
			link.l1.go = "exit";
			SetFunctionTimerCondition("TakePassenger_CreateShip", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms1), false);
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "10");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sCityA", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc"));
			AddQuestUserData("MayorsQuestsList", "sDay1", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms1)));
			AddQuestUserData("MayorsQuestsList", "sDay2", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePassenger.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePassenger.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Таможенный патруль
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "CustomPatrol":
			//установка параметров
			pchar.GenQuest.questName = "CustomPatrol"; //тип квеста
			pchar.GenQuest.CustomPatrol.Nation = sti(npchar.nation);//нация
			pchar.GenQuest.CustomPatrol.Island = Islands[GetCharacterCurrentIsland(PChar)].id;
			pchar.GenQuest.CustomPatrol.LoginDay = rand(2)+1;
			pchar.GenQuest.CustomPatrol.Loginlocator = rand(3)+3;
			pchar.GenQuest.CustomPatrol.ShipType = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.CustomPatrol.ShipTypeA = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.CustomPatrol.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.CustomPatrol.ShipType));
			pchar.GenQuest.CustomPatrol.Money = ((hrand(5)+hrand(6, "1")+4)*450)+8200 + (sti(pchar.rank) * 750);
			pchar.GenQuest.Governor.Group1.day = GetDataDay();
			dialog.text = "ある信頼できる情報によれば、ある船長が密輸業者と奴隷売買の取引を手配したそうです。ご存知の通り、 我が植民地で個人がこのような取引を行うことは密輸と見なされます。\n問題は、密輸業者が会う正確な時間も日付も場所も分からないことです。分かっているのは、 この犯罪的な取引が今後三日以内に我が島で行われるということだけです。さらに悪いことに、 私の巡回船はすべて修理中か他の任務に就いており、これらの悪党を追跡できません。\nそこで、あなたにこの任務を引き受けていただきたいのです――密輸業者を追跡し、断固たる手段で対処し、見せしめにしてください。この任務を引き受けていただけますか？";
			link.l1 = "準備はできております "+GetAddress_FormToNPC(NPChar)+"。さて、何か追加情報はありますか？例えば船長の名前や、船の名前、あるいは船の種類などですか？";
		    link.l1.go = "CustomPatrol_agree";
			link.l2 = "うーん……いや、遠慮しておくよ。";
		    link.l2.go = "All_disagree";
		break;
		
		case "CustomPatrol_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.CustomPatrol.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "私の情報源によると、取引が準備されていて、まもなく完了するそうです。それだけです。ですから、我々 の領海内にいる怪しい船をすべて注意深く監視してください。うまくいけば、あなたに報酬を支払います。 "+FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money))+"\nさらに、この状況を鑑みて、あなたに見つけられる限りの密輸品をすべて押収することを許可します。 もちろん非公式ですが、我が街で売らないことが条件です。";
			link.l1 = "なかなか気前がいいな。よし、お前さんの植民地の海域を巡回してくるぜ。 "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 4, false);
			pchar.quest.CustomPatrol.win_condition.l1 = "location";
			pchar.quest.CustomPatrol.win_condition.l1.location = pchar.GenQuest.CustomPatrol.Island;
			pchar.quest.CustomPatrol.win_condition.l2 = "Timer";
			pchar.quest.CustomPatrol.win_condition.l2.date.hour  = sti(GetTime()+rand(8));
			pchar.quest.CustomPatrol.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.function = "CustomPatrol_CreateShip";
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "11");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)));
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Найти дезертира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "FindFugitive":
			//установка параметров
			pchar.GenQuest.questName = "FindFugitive"; //тип квеста
			pchar.GenQuest.FindFugitive.Startcity = npchar.city;
			pchar.GenQuest.FindFugitive.City = SelectFugitiveCity();
			pchar.GenQuest.FindFugitive.Chance = rand(2);
			pchar.GenQuest.FindFugitive.Name = GenerateRandomName(sti(npchar.Nation), "man");
			pchar.GenQuest.FindFugitive.Money = ((hrand(5)+hrand(6, "1")+4)*600)+9600+(sti(pchar.rank)*900);
			sText = SelectFugitiveText();
			log_testinfo(pchar.GenQuest.FindFugitive.City);
			log_testinfo(FindRussianDaysString(sti(pchar.GenQuest.FindFugitive.Chance)));
			pchar.GenQuest.Governor.Group2.day = GetDataDay();
			dialog.text = "詳しくすべてお話ししましょう。とても醜い出来事が起きたのです―― "+sText+"。彼の同僚や友人たちに話を聞いた結果、我々は十分な根拠をもって、 その脱走兵が海賊のいずれかの居住地に身を隠していると考えております\nあなたには海賊の巣窟を訪れ、逃亡者を見つけて逮捕し、ここへ連れてきていただきたい。脱走は重大な罪であり、 決して見逃すことはできません。この任務を引き受けるご覚悟はありますか？";
			link.l1 = "準備はできております "+GetAddress_FormToNPC(NPChar)+"。脱走者の名前を教えていただけますか？";
		    link.l1.go = "FindFugitive_agree";
			link.l2 = "ふむ……いや、今回は遠慮しておこう。";
		    link.l2.go = "All_disagree";
		break;
		
		case "FindFugitive_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.FindFugitive.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "はい、もちろんです。彼の名前は "+pchar.GenQuest.FindFugitive.Name+"。やつが制服を着ているとは到底思えんから、あらゆるならず者どもをよく調べてみるのだ。 捜索の猶予は一ヶ月だけ与えよう、それ以降は探しても意味がないと私は思うからな。もし成功したら、 君に報酬を支払おう\n "+FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money))+".";
			link.l1 = "「これ以上時間を無駄にはしません」 "+GetAddress_FormToNPC(NPChar)+"！すぐに出航いたします。";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 30, false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "12");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.FindFugitive.Name);
			//создаем дезертира
			sld = GetCharacter(NPC_GenerateCharacter("Fugitive", "citiz_"+(21+rand(9)), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, sti(npchar.nation), 30, true, "soldier"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			sld.name = pchar.GenQuest.FindFugitive.Name;
			sld.lastname = "";
			sld.dialog.FileName = "MayorQuests_dialog.c";
			sld.greeting = "marginal";
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Проникновение во враждебный город
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "Intelligence":
			pchar.GenQuest.Governor.Group3.day = GetDataDay();
			dialog.text = "なるほど。もしかすると報酬は "+FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money))+" あなたへの良い動機になるでしょう。";
			link.l1 = "ああ、悪くない報酬だな……この依頼、受けるぜ。";
		    link.l1.go = "Intelligence_agree";
			link.l2 = "ふむ……いや、私は断ります。危険すぎます。";
		    link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //на всякий случай
			{
				dialog.text = "完全にあなたを信頼しているとは言えませんが……この任務はお渡ししないことにいたします。";
				link.l1 = "まあ仕方ないな……残念だが、俺にできることは何もねえ。";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			}
			else
			{
				npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
				pchar.GenQuest.questName = "Intelligence"; //тип квеста
				sTemp = pchar.GenQuest.Intelligence.City;
				switch (rand(4))
				{
					case 0:	sTemp += "_Priest";		break;
					case 1:	sTemp += "_trader";		break;
					case 2:	sTemp += "_shipyarder"; break;
					case 3:	sTemp += "_usurer";	    break;
					case 4:	sTemp += "_PortMan";	break;
				}
				pchar.GenQuest.Intelligence.SpyId = sTemp; //Id нашего шпиона в городе
				dialog.text = "素晴らしい！さて、本題に入ろう。 "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" 地元の者を探す必要がある "+GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)],"Gen")+"、彼の名前は "+GetFullName(&characters[GetCharacterIndex(sTemp)])+"。私の名前を彼に伝えれば、書類の包みを渡してくれるはずです。その包みを私の手元に届けてくれたら、あなたに "+FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms))+"。そして、すべては極秘で行わねばならぬことを忘れないでください。もしあなたの正体が露見すれば、 工作員は接触を試みることを控えるでしょう。よろしいですか？";
				link.l1 = "はい、承知しました。 "+GetAddress_FormToNPC(NPChar)+"。すぐに始めます。";
				link.l1.go = "exit";
				pchar.GenQuest.Intelligence.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
				SaveCurrentQuestDateParam("GenQuest.Intelligence"); //запись даты получения квеста
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "6");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc"));
				AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(GetIslandByColony(&colonies[FindColony(pchar.GenQuest.Intelligence.City)])+"Dat"));
				AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
				AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));			
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
				AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			}
		break;
		case "Intelligence_ExecuteLate":
			QuestName = pchar.GenQuest.questName;
			pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / 2);
			dialog.text = RandPhraseSimple("悪くはありません。しかし、期限に間に合わなかったので、報酬を少し減額せざるを得ません。今回の報酬は "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+"。さあ、どうぞ。","それは良い。しかし、期限に間に合わなかったし、私はこの手紙をずっと待っていたのだ。 おかげで私の計画が台無しになった、だから報酬を少し減らさざるを得ない。それでも、 あなたに正当な報酬を渡せることは嬉しいですわ― "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+"。さあ、どうぞ。");
			link.l1 = "私にとって快いことだとは言えませんが、結局のところ、期限は確かに守られませんでした。ですから、 私からは何も不満はありません。 "+GetAddress_FormToNPC(NPChar)+".";
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(RandPhraseSimple("You know, governor " + GetFullName(npchar) + " are not very pleased with the quickness of a captain " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is not very pleased with captain " + GetMainCharacterNameDat() + ", "+ GetSexPhrase("who","who") +" complied with his orders, but did not in due time..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		
		// -------------- общий набор для всех квестов мэра ------------------
		case "All_disagree":
			dialog.text = RandPhraseSimple(
				"ふむ。そうか、私が"+pchar.name+"船長の覚悟を過大評価していたようですな。",
				"私を失望させるのですね、船長。どうやらこのような事柄に必要な資質が本当に欠けているようです。",
				"次回は、船長、無駄話で私の時間を浪費する前にもう一度よく考えてください。");
			link.l1 = "申し訳ありません。 "+GetAddress_FormToNPC(NPChar)+"、しかしこの仕事はお引き受けできません。";
		    link.l1.go = "exit";
			//ChangeCharacterComplexReputation(pchar,"nobility", -2);
			
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
		break;
		case "All_Late":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("うむ、非常に悪い、他に言うことはない。私は君に期待していたが、結局は時間の無駄だったようだ。失望したぞ。","いやはや、あなたにはまったく失望しましたわ……私の邸宅には、こういった用事をいつでも引き受ける者が大勢おりますのに、あなたに時間を割いてしまいましたわ。 まあ、仕方ありませんけれど……");
			link.l1 = "「申し訳ありません」 "+GetAddress_FormToNPC(NPChar)+"、私にできることはすべてやりました。";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Just imagine - he failed to fulfill his assignment in time!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " put his shoulder to the wheel, but fail to fulfill his assignment in time. That's too bad...", 
				"I heard that governor " + GetFullName(npchar) + " is very displeased with you, captain " + GetFullName(pchar) + ", since you failed to meet the deadline while trying to fulfill his assignment."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("私はただただ驚いております！目標を見つけたにもかかわらず、優位を確保しようとしなかったとは――それは極めて無謀です。失望しました！","まあ、あなたには失望しましたわ……標的を見つけるだけでは不十分ですのよ――それを滅ぼす手段を持たねばなりませんわ。私の邸宅には、 いつでもこのような仕事を引き受ける用心棒どもが大勢おりますのに。どうしてあなたに頼もうと思ったのかしら？");
			link.l1 = "「申し訳ありません」 "+GetAddress_FormToNPC(NPChar)+"、しかし、私自身の命を無謀に危険にさらす気はございません。";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Imagine, "+ GetSexPhrase("he turned out to be a downright coward","she turned out to be a downright coward") +"!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " took the job, but failed to carry it out because of their own indecision. Hee-hee, what wilt captains!", 
				"I heard that Governor " + GetFullName(npchar) + " very displeased with you, Captain " + GetFullName(pchar) + ". They say you're nothing but a coward"+ GetSexPhrase("","") +"..."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("素晴らしい知らせです！さて、そろそろ総括の時ですね。あなたの報酬は "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+"。さあ、どうぞ。","素晴らしい！これは皆にとって最善ですな……さて、あなたに正当な報酬をお渡しできて嬉しいですわ― "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+"。さあ、どうぞ。");
			link.l1 = "ありがとうございます。 "+GetAddress_FormToNPC(NPChar)+", "+RandPhraseSimple("お取引できて光栄です！","入植地の明瞭さには驚かされますね。");
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + "  was praising for diligence"+ GetSexPhrase("a captain","a young lady") +" " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is praising captain " + GetMainCharacterNameGen() + ", "+ GetSexPhrase("he","she") +" is always a flawless performer when it comes to governor's assignments. An irreplaceable person for the governor, I say...", 
				"I heard that governor " + GetFullName(npchar) + " is very much pleased with you, captain " + GetFullName(pchar) + ". He defines you as a very careful and thorough officer. That's very nice to hear, captain..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("よろしいです。また私のところに来てくださって構いません――もしかしたら他の仕事を見つけて差し上げられるかもしれません。","おお、素晴らしい！またあなたにこのような仕事を頼むことになるでしょう。");
			link.l1 = RandPhraseSimple("「素晴らしい。」","よろしい。");
		    link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
			CloseQuestHeader("MayorsQuestsList");
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(PChar, "Leadership", 180);
			OfficersReaction("good"); // dlc
			
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			// инкремент в базу заданий мэров
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
//<-- осады homo
		case "siege_task":
            makearef(aData, NullCharacter.Siege);
            aData.HelpColony = true;
			dialog.text = "このような苦しい時期には、どんな助けでも大変ありがたいです。あなたの援助を受け入れましょう――我々の植民地防衛に協力してくだされば、必ず報酬を差し上げます。";
			link.l1 = "それでは、時間を無駄にしないようにしましょう。";
		    link.l1.go = "exit";
		break;
		
		//Jason --> Бремя гасконца
		case "Sharlie":
			dialog.text = "ミシェル・ド・モンペールを探しているのか？面白いな……で、あいつに何の用だ？";
			link.l1 = "私は彼の兄です。父がミシェルが困っていて助けを必要としていると私に言ったので、私が…";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
			DelLandQuestMark(sld);
			dialog.text = "そうか？モンペール旦那に兄弟がいたとは記憶にないな……それに、旦那、あなたはとても怪しく見える……よって、さらなる調査のために逮捕する。\n中尉！この男を拘束しろ！";
			link.l1 = "「しかしご領主様！」";
			link.l1.go = "exit";
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}	
			AddDialogExitQuestFunction("Sharlie_enterSoldiers");
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Sharlie_2":
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload3_back");
			dialog.text = "それでも、償いをしたいのです。こちらを――どうぞ、この剣と、このピストル、それにこの軽装鎧を受け取ってください。これはあなたへの贈り物です。 きっとお役に立つと信じております。";
			link.l1 = "ありがとうございます、旦那。あなたの衛兵たちが私の持ち物をすべて奪ったことを考えると、これは本当に助かります。 ";
			// belamour legendary edition -->
			link.l1.go = "Sharlie_5";		
			link.l2 = "ありがとうございます、旦那。ほかに何か助けていただける方法はありませんか？紳士同士として。ご覧の通り、 私は本当にひどい状況なのです！";
			link.l2.go = "Sharlie_3";	
		break;
		
		case "Sharlie_3":
			dialog.text = "さて、チャールズ……（机をゴソゴソと探る）ほら、この聖なるお守りを持っていきなさい。幸運を祈るよ。もうこれ以上は手助けできない、 すまない。\nここ植民地では、自分自身だけを頼りにしなければならないんだ。";
			link.l1 = "まあ、少なくとも何かはあるな。贈り物をありがとう、旦那。";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Commerce", 10);
			Log_Info("You'have received equipment");
			Log_Info("You have received the 'Holy Water' amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Sharlie_5":
			// <-- legendary edition
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 10);
			Log_Info("You'have received equipment");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		//<-- Бремя гасконца
		
		//Sinistra --> Травля крысы		
		case "TK_TravlyaKrys":
			dialog.text = "なんという運命のいたずらだ、チャールズ……この世界でこれほど早く頭角を現す者は滅多にいない。私とあなたはきっと良い関係を築ける気がしますよ。";
			link.l1 = "光栄です。もしかして、私に何かご用がありますか？";
			link.l1.go = "TK_TravlyaKrys_2";
			DeleteAttribute(pchar, "questTemp.TK_TravlyaKrys");
			PChar.quest.TK_Timer.over = "yes";
		break;
		
		case "TK_TravlyaKrys_2":
			dialog.text = "もちろんでございます！特にル・フランソワ近海でバルバゾンの海賊の一人と見事に交戦された後では……";
			link.l1 = "あの出会いを良い思い出だったとは言えませんね。バルバゾンとは一体何者ですか？";
			link.l1.go = "TK_TravlyaKrys_3";
		break;
		
		case "TK_TravlyaKrys_3":
			dialog.text = "ジャック・バルバゾン、別名「善人ジャック」はル・フランソワの盗賊の巣を率いている。いわゆる海賊男爵の一人で、 小アンティル諸島で海賊行為や密輸で厄介事を起こしている悪名高い犯罪者だ。私の言葉を覚えておきなさい、 いつか必ずサン・ピエールの絞首台で最期を迎えることになるぞ！";
			link.l1 = "失礼ですが、マルティニークで本当の権力者はあなたではありませんか？あの巣窟を排除することくらいできるでしょう？ 私も行きましたが、正直言って大した場所じゃありませんよ。";
			link.l1.go = "TK_TravlyaKrys_4";
		break;
		
		case "TK_TravlyaKrys_4":
			dialog.text = "私の島のいかがわしい場所について知っていることを自慢するのはやめたほうがよろしいですわ、チャールズ。 それは貴族らしくありませんわ。ご質問についてですが\nこの世のすべてが力ずくで解決できるわけではありませんの。政治や商業の利害も絡んでおります。でも、 余計な詳細には立ち入りませんわ。実は、少々の武力を必要とする特別な任務がございますの。";
			link.l1 = "どうぞ続けてください。";
			link.l1.go = "TK_TravlyaKrys_5";
		break;
		
		case "TK_TravlyaKrys_5":
			dialog.text = "バルバゾンは、楽に金を稼ぎたい小物の船乗りどもを引き寄せるんだ。時々、奴は連中の一人に餌を投げ与えて、 皆がそれを奪い合う様子を楽しむんだぜ。たまに生き残った奴を使い走りにすることもあるが、大抵は追い出してしまう。 信じてくれ、絶望した海賊ほど危険なものはねえんだよ。";
			link.l1 = "理解できたと思いますが、自分にできるかどうかは自信がありません。私は最近ようやく自分の船を任されたばかりで、 まだ色々と勉強中なんです……";
			link.l1.go = "TK_TravlyaKrys_6";
		break;
		
		case "TK_TravlyaKrys_6":
			dialog.text = "馬鹿なことを言うな！お前はすでに勝利の味を知っている――私の部下の怠け者どもよりもずっとな！バルバゾンの手下をもう一隻沈めれば、市から五千ペソの報酬が出るぞ、 しかも無税だ。生け捕りにして連れてくれば八千ペソ――もちろん、きちんと処刑するためにな。";
			link.l1 = "確かに金は必要だ。そいつの海賊はどこにいるんだ？";
			link.l1.go = "TK_TravlyaKrys_7";
			link.l2 = "申し訳ありませんが、私にはまだこのような任務を引き受ける準備ができていないと思います。";
			link.l2.go = "TK_TravlyaKrys_Otkaz";
		break;
		
		case "TK_TravlyaKrys_Otkaz":
			dialog.text = "それは残念です、Charles。では、これ以上お引き止めしません。";
			link.l1 = "ごきげんよう、閣下。";
			link.l1.go = "exit";
		break;
		
		case "TK_TravlyaKrys_7":
			dialog.text = "乗船してくれて嬉しいよ、チャールズ。\n我々の情報によれば、ハター号というラガー船が現在ル・フランソワを出航する準備をしているそうだ。\nぐずぐずしている暇はない、すぐに出航して迎撃してくれ。\n心配はいらない、友よ、君ならきっとやれるさ。";
			link.l1 = "「神のご加護がありますように、閣下。」";
			link.l1.go = "TK_TravlyaKrys_8";			
		break;
		
		case "TK_TravlyaKrys_8":
			DialogExit();
			SetQuestHeader("TravlyaKrys");
			AddQuestRecord("TravlyaKrys", "1");
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, true, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			FantomMakeSmallSailor(sld, SHIP_LUGGER, "Hater", CANNON_TYPE_CANNON_LBS3, 20, 40, 20, 25, 35);
			SetCharacterGoods(sld, GOOD_GOLD, 1);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("HeiterAttack");
			Group_SetType("HeiterAttack", "pirate");
			Group_AddCharacter("HeiterAttack", "TK_Heiter");

			Group_SetGroupCommander("HeiterAttack", "TK_Heiter");
			Group_SetTaskAttack("HeiterAttack", PLAYER_GROUP);
			Group_SetAddress("HeiterAttack", "Martinique", "Quest_Ships", "Quest_Ship_6");
			Group_LockTask("HeiterAttack");
			
			PChar.quest.TK_Potopil.win_condition.l1 = "Character_sink";
			PChar.quest.TK_Potopil.win_condition.l1.character = "TK_Heiter";
			PChar.quest.TK_Potopil.win_condition = "TK_Potopil";
		break;
		//<-- Травля крысы
		
		//Jason --> Португалец
		case "Portugal":
			dialog.text = "もちろんできますよ、船長！だからこそお呼びしたのです。";
			link.l1 = "それでは、耳を傾けましょう。";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "昨夜、地元の漁師たちが島の近くで奇妙な船を見たそうです。巨大な戦艦、戦列艦のような船で、 旗も信号灯もなかったと言っています。私としては、その船が実際にフリゲート艦より大きいとは思えませんが、 それでも十分に脅威です！";
			link.l1 = "恐れは小さなことを大きく見せるものだな、確かに……だが、それに何の意味があるんだ？";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "私はあなたに頼ります、船長。私の交易相手たちはこの噂に怯えております――海賊やスペインの私掠船だと思い込み、商売に悪影響です。最悪なのは、今この植民地には軍艦が一隻もおらず、 防衛用のスループが二隻と、密輸船狩りにしか使えぬ古いスクーナーがあるだけなのです。\n放置するわけにはまいりません……ともかく、今やこの謎の船の噂は町の半分に知れ渡っております！どうか、あなたの船で我々に加わり、 発見の手助けをしていただけませんか――あなたは立派な船長と存じておりますし、たとえ本当にただのフリゲートであったとしても、 あなたの大砲ならば奴らを他所へ追いやることもできましょう！";
			link.l1 = "旦那……実は、他に考えがありましたの……";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "お願いです、船長！せめて数日だけでも、この不穏な噂が収まるまでお願いします！もちろん、 その間のお礼もいたします。1万枚のエイトでいかがでしょうか？";
			link.l1 = "うーむ……しかし、閣下、私は……";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "そして、もし本当にその船と戦闘になれば報酬は倍、沈めたなら三倍にいたしましょう！さて、どうなさいますか？";
			link.l1 = "わかった、どうせここに二、三日滞在するつもりだったんだ。";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "素晴らしいですわ、わたくしはあなたを疑ったことなど一度もありませんの、船長旦那！覚えておいてくださいませ――我が領海に二日間いるだけで、報酬はあなたのものですわ。\nもし戦闘を余儀なくされた場合は、その結果に応じてお支払いいたしますわ。";
			link.l1 = "承知いたしました、閣下。お取引成立でございますので、これより私の船へ戻ります。";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "帰りを待っております、船長！";
			link.l1 = "お暇させていただきます。";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			DialogExit();
			AddQuestRecord("Portugal", "10");
			NextDiag.CurrentNode = "Portugal_8";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", false);//открыть выходы из города
			bDisableFastReload = true;//закрыть быстрый переход
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.Portugal_Seapatrol.win_condition.l1 = "location";
			pchar.quest.Portugal_Seapatrol.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_Seapatrol.function = "PortugalSeapatrolGo";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1 = "location";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Portugal_SeapatrolAvendel.function = "AvendelSpeach";
		break;
		
		case "Portugal_8":
			dialog.text = "船長、あなたには二日間我々の沿岸海域を巡回するという約束があったはずですぞ！";
			link.l1 = "はい、もちろんです。それは覚えております。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Portugal_8";
		break;
		
		case "Portugal_9":
			dialog.text = "よくやってくれましたな。約束通り、これが報酬の1万ペソでございます。";
			link.l1 = "ありがとうございます！ご覧の通り、ご心配には及びませんでした。ご武運を祈ります！";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			DialogExit();
			AddMoneyToCharacter(pchar, 10000);
			NextDiag.CurrentNode = "First time";
			pchar.quest.MartiniqueGovernorOver.over = "yes"; //снять таймер
		break;
		//<-- Португалец
		
		// Warship, 16.05.11. Генер "Правосудие на продажу".
		case "JusticeOnSale_1":
			dialog.text = "Oh "+GetAddress_Form(NPChar)+"、私を驚かせましたね！あの悪党どもは本当にそこまで図々しくなったのですか？すぐに司令官に知らせて、 沿岸警備隊を派遣しなければなりません！";
			link.l1 = "お力になれて嬉しかったです。では、これで失礼してもよろしいでしょうか？";
			link.l1.go = "JusticeOnSale_2";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
			
			DeleteQuestCondition("JusticeOnSale_MapEnter");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "もちろんでございます、船長。こちらを――どうぞ、私からささやかな報酬をお受け取りくださいませ。";
			link.l1 = "ありがとうございます。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("JusticeOnSale_DlgExitAfterMayor_1");
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "おっしゃる通りです、船長！このまま放っておくわけにはいきません！あなたに向かっていただきたいのは "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+"、奴らの船を見つけて一味全員を逮捕せよ！抵抗した場合は、力を使ってもためらうな！";
			link.l1 = "お暇させていただきます。";
			link.l1.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "さあ、行きなさい。そこへ航海し、誰一人として正義から逃さぬようにしてください。 まずは岸に上陸する必要があると思います、その後で船の処理をなさってください。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("JusticeOnSale_DlgExitAfterMayor_2");
		break;
		
		case "JusticeOnSale_7":
			dialog.text = "ご協力いただきありがとうございます。あの悪党どもは当然の報いを受けました。どうぞ、 私からささやかながらこの報酬をお受け取りください。私の町の秩序と平和を大いに重んじております。";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			AddMoneyToCharacter(PChar, sti(PChar.rank) * 300 + hrand(1000));
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			DialogExit();
		break;
		//<-- Правосудие на продажу
		
			//--> Jason регата
		case "Regata":
			// belamour legendary edition -->
			if(sti(pchar.rank) < 15)
			{
				Notification_Level(false, 15);
				dialog.text = "ああ、素晴らしい、お会いできて嬉しいです、船長！あなたの才能は伺っておりますが、 本当に準備ができた時にまたお越しください。";
				link.l1 = "はい、もちろんでございます。ご希望通りにいたします。";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "おお、素晴らしい、会えて嬉しいぞ、船長！ちょうどいい時に来てくれたな――数日後にレガッタが始まるところだ。規則書は従者から受け取って読んだか？";
				link.l1 = "はい、旦那、やりました。";
				link.l1.go = "Regata_1";
				RemoveItems(PChar, "letter_open", 1);//уберем письмо
				DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
			}
		break;
		
		case "Regata_1":
			dialog.text = "そして、五万ペソ――入場料として賞金に加算される分――はご用意されましたか？";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "はい、もちろんでございます。どうぞ私の謝礼をお受け取りください。";
				link.l1.go = "Regata_2";
			}
			link.l2 = "今は少し金が足りない。しかし、必ず必要な額を用意するつもりだ。";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "よろしい。勝てば賭け金の五倍が返ってくるぞ。さて、まずはレガッタの規則をよく知っておく必要がある。\n詳しいことはヘンリー・スティブンソン旦那から聞くといい。彼は邸宅のどこかの部屋にいるはずだ。 彼のところへ行きなさい――すべて説明してくれるだろう。";
			link.l1 = "わかった。その通りにしよう。";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "よろしいですが、どうかあまりお時間をかけないでください、船長。レガッタはまもなく始まります。";
			link.l1 = "なるほど。できるだけ早くお金を持ってくるようにいたします。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "おお！ここにレガッタの勝者がいるではないか！ごきげんよう、船長 "+GetFullName(pchar)+"！この当然の成功を心よりお祝い申し上げます！レガッタの勝者は常にイギリス植民地で人気者でございます――それも当然のことですわ。";
			link.l1 = "ありがとうございます、旦那！";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "さて、いよいよ一番楽しい部分、表彰式に移りましょう。\n第一賞は25万ペソです。おめでとうございます！";
			link.l1 = "ありがとう！";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			// belamour legendary edition в регате только один приз -->
			GiveItem2Character(pchar, "blade_26");
			GiveItem2Character(pchar, "cirass4");
			GiveItem2Character(pchar, "bussol");
			
			dialog.text = "さらに、貴重な賞品も受け取れますぞ。伝説のトレド鋼レイピア「アソレダ」、ミラノ製の鎧一式、 そして上質なコンパスです。すべてあなたのものです。";
			// <-- legendary edition
			link.l1 = "私はとても嬉しいです、旦那。本当に、このようなご寛大さは予想しておりませんでした。";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "イギリス植民地の全臣民を代表して、レガッタへのご参加に感謝申し上げます。 そして改めてご勝利おめでとうございます！もし賭けをされたのであれば、 まだ受け取っていなければヘンリー・スティーブンソン卿のところへ行き、賞金をお受け取りください。\nご武運をお祈りします、船長！";
			link.l1 = "ご丁寧なお言葉、ありがとうございます、旦那！それに加えて、 このような盛大な催しに参加する機会を与えてくださったことにも感謝申し上げます。\nそれでは、これにて失礼させていただきます。";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}

string GetGangLocation(ref npchar)
{
    int n;
	string island = GetArealByCityName(npchar.city);
	string LocationId, sAreal;
	int storeArray[2];
	SetArraySize(&storeArray, MAX_LOCATIONS);  
    int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if (GiveArealByLocation(&locations[n]) == island)
		{			
			//==> на всякий случай
			if (CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if (findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[hrand(howStore-1)];
	return locations[n].id;
}

string GetSpyLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) //если взят квест по доставке малявы
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GetSpyColony(ref NPChar)
{
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		// Rebbebion, чуть изменил функцию, чтобы условно испанцы не просили пробраться к испанцам, французы к французам и т.д
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].id != npchar.City && colonies[n].nation != npchar.nation)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[Rand(howStore-1)]].id;
}

int SelectCureerShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL + FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
}

int SelectCustomPatrolShipType(int iFlagType)
{
	if(CheckAttribute(pchar, "questTemp.StatusCity"))
	{
		return SHIP_CAREERLUGGER;
	}
	
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

int SelectArsenalShipType(int iFlagType)
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

string SelectPassText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "That Judas, using his position, sold an important state secret to an enemy power."; break;
		case 1: sText = "That foul scoundrel killed his relative, a well-known and noble man, in order to inherit his fortune."; break;
		case 2: sText = "That foul scoundrel insulted my family and me personally."; break;
		case 3: sText = "This thieving rogue stole a decent sum of money from our city's treasury."; break;
		case 4: sText = "That villain is guilty of deaths of nearly a dozen of our citizens."; break;
		case 5: sText = "That rogue used his connection to take possession of a merchant vessel, and then he stole it and sold at the neighboring shipyard."; break;
	}
	return sText;
}

string SelectFugitiveCity()
{
	string sCity;
	switch (rand(3))
	{
		case 0: sCity = "LaVega"; break;
		case 1: sCity = "PuertoPrincipe"; break;
		case 2: sCity = "LeFransua"; break;
		case 3: sCity = "FortOrange"; break;
	}
	return sCity;
}

string SelectFugitiveText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "one of the junior officers in our garrison has deserted and left the colony on board of a merchant ship."; break;
		case 1: sText = "one of our officers deserted right on duty and escaped on board of a smuggler ship."; break;
		case 2: sText = "one of our naval officers serving on a patrol brig deserted for unknown reason, hijacked a long boat and disappeared on it."; break;
		case 3: sText = "one of our prison guards threw up his service for  unknown reason and left our colony aboard a private vessel."; break;
		case 4: sText = "one of the soldiers in our garrison abandoned his post while keeping guard, went to the cove and left this place aboard an unknown vessel."; break;
		case 5: sText = "one of our military officers, captain of a patrol lugger, abandoned his ship in the open sea and went south on a fishing long boat."; break;
	}
	return sText;
}
