// Эдвард Мэнсфилд, глава буканьеров и авторитетный пират, английская линейка
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
            {
            	if (NPChar.quest.meeting == "0")
				{
					dialog.Text = TimeGreeting() + "! Én vagyok "+ GetFullName(NPChar) + ", ennek a gödörnek az új kormányzója. Nem lesz könnyû rendre utasítani a helyi gengsztereket, de a spanyol gyarmatokra már nem fenyegeti ôket veszély.";
					Link.l1 = "Örülök, hogy megismerhetem. Kapitány vagyok " + GetFullName(Pchar) + ". Sajnálom, de mennem kell.";
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = TimeGreeting() + ". Elfoglalt vagyok, nagyon elfoglalt, a helyi gengsztereket kell irányítanom, hogy megakadályozzam a spanyol kolóniákat fenyegetô veszélyt.";
					Link.l1 = "Akkor nem zavarom.";
					Link.l1.go = "exit";
				}
            }
            else
            {
				dialog.text = NPCStringReactionRepeat("Van valami mondanivalója? Nincs? Akkor "+ GetSexPhrase("el innen!","Kérem, hogy ne zavarjon.") +"",
	                         "Azt hiszem, világosan fejeztem ki magam...", "Bár világosan fejeztem ki magam, te továbbra is idegesítesz!",
	                         "Hát, te mérhetetlenül "+ GetSexPhrase("túl goromba vagy, mon cheri","ilyen udvariatlanság, lány","ilyen udvariatlanság, lány") +"...", "repeat", 30, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Elmegyek.",
	                                               "Igen, " + npchar.name + ", látom.",
	                                               "Sajnálom, " + npchar.name + "...",
	                                               "Aú...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Van valami munkád számomra?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "Felvettem a nyomokat, de kell néhány érme - 30.000 pezó, hogy elôcsalogassam a patkányt a lyukából.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Tessék, nézd ezt a levelet, amit a csempész holttestén találtam.";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "Kész is van. Norman Vigo és a hajója a tengeri ördögé.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm... Munka, azt mondtad? Igazából jó, hogy megkérdeztél. Szükségem van egy külsôs emberre. A legközelebbi városban akarok valamit kideríteni, de az embereimet ott ismerik. Nem ígérhetek sokat, de valamit kapni fogsz.";
			link.l1 = "Mi a küldetés?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Sajnálom, de nem fogom vállalni a kockázatot néhány falatért. Viszontlátásra.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "Akkor figyelj, egy hónapja volt egy üzletem 200 rabszolga leszállítására a schooner kapitányával 'Saintblue'. akartam eladni ôket a helyi ültetvénytulajdonosnak. Eltelt az idô, és a megrendelô aggódni kezdett, de tegnap értesítettek, hogy a szkúnert nem messze a szigettôl látták. De! A kapitány nem jelent meg. Ma az ügyfelem követelte, hogy adjam vissza az elôlegét, és azt mondta, hogy egy másik eladótól ajánlottak neki rabszolgákat. Drágábban, de az egész rabszolgacsapatot egyszerre.";
			link.l1 = "És? Nekem kell 200 rabszolgát találnom néhány nap alatt, hogy megmentsem az elôleg elvesztésétôl? Néhány érméért?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Persze, hogy nem. Idiótának nézek ki? Úgysem fogom visszaadni neki az elôleget. De bizonyítékra van szükségem, hogy a felajánlott rabszolgák az enyémek. Találd meg azokat, akik új üzletet ajánlottak neki, és megkapod a 10.000 pezódat. Megegyeztünk?";
			link.l1 = "Benne vagyok. Van valami gyanúja, hogy ki lehet az?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Semmi esélye. Keressen valaki mást, csak 10.000-ért? Sajnálom, de nem fog menni.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Ha lennének ötleteim, akkor soha nem venném igénybe a szolgáltatásait. Azok az emberek már halottak lennének. De kíváncsian várom, hogyan szereztek tudomást a 'Saintblues' szállítmányról és az ügyfelemrôl. Úgy tûnik, elég könnyû volt nekik. Látod most?";
			link.l1 = "Igen, valaki elárulta magát.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Pontosan! Keresem ôt. A versenytársaim megölése és a rabszolgáim visszaadása nem a te prioritásod. Szükségem van arra a patkányra, pontosabban a fejére egy nyárson, ha ôszinte akarok lenni. Most már érted, miért nem tudnak az embereim semmit a küldetésedrôl? Mindenkit gyanúsítani fogok, amíg ki nem derítem, ki adja el az információt. És ezt nem igazán akarom...";
			link.l1 = "Értem. Akkor nem fogok feltûnést kelteni. Már úton vagyok.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Harmincezret mondott? Ez egy nagy összeg... Csak 5.000 pezót tudok adni, ennyim van. És meg se próbálj megszökni a pénzzel, különben megtalállak és felakasztalak a legközelebbi kerítésre! Megértetted?";
			link.l1 = "Rendben, akkor adj ötezret...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Vedd el. Várom a keresésed eredményét.";
			link.l1 = "Minden rendben lesz.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Kiváló hír! Biztos voltam benne, hogy sikerülni fog. Van néhány érdekes információm.";
			link.l1 = "Elvégeztem a munkámat, és meg akarom kapni a tízezer dolláromat.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Persze, itt a jutalmad. De ne szaladj el, van még egy feladatom számodra.\nPfaifer Norman Vigo legénységének tagja a luggeren 'Septima'. Biztos vagyok benne, hogy Norman Vigo a patkány, még ha közülünk való is. Nemrégiben látták a sziget vizein. A te feladatod, hogy ezt a patkányt elküldd a tengeri ördöghöz. Már az elsô alkalommal sem vallottál kudarcot, ezért arra kérlek, hogy ezzel az üggyel is foglalkozz. Fizetek neked 15.000 pezót. Megegyeztünk?";
			link.l1 = "Megegyeztünk! Tekintsd az árulót halottnak.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Tudod, én nem akarok részt venni ebben... Amúgy sincs idôm. Sajnálom, de én lelépek.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "Tudom, tudom. Az embereim figyelték a csatát, és már beszámoltak nekem a hibátlan gyôzelmedrôl. Rendben, jól végezte a dolgát. Itt van 15.000 pezó, ahogy ígértem. És köszönöm, sokat segítettél nekem.";
			link.l1 = "Rendben van, örömmel segítettem! De most mennem kell, túl sokáig voltam itt, és sok dolgom van. Viszontlátásra!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;
				
 		case "No_Mansfield_first_time":
			dialog.text = "Üdvözletem, a nevem Alistair Good. Mansfield halála után engem választottak a kalózok élére.";
			link.l1 = "Örülök, hogy megismerhetem, Alistair.";
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
  		break;
 		case "No_Mansfield":
			dialog.text = "Nincs idôm beszélgetni veled. Látogass meg késôbb.";
			link.l1 = "Már megyek is.";
			link.l1.go = "exit";
  		break;
		

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("Get","Get") +" out!", "Takarodj az otthonomból!");
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Мэнсфилдом через 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ne zavarj engem, ne feledd.";
        			link.l1 = "Megvan.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
