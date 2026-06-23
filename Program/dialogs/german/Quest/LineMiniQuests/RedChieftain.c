void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Das ist ein Fehler. Sag es den Entwicklern.";
			link.l1 = "Ich werde!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "RedChieftain":
			dialog.text = "Wie, bleichgesicht. Ich sehe, dass du Kapitän eines großen Kanus bist. Ich bin Kanauri. Ich bin der Häuptling von Cayman - mächtiger Stamm der Arawak. Ich möchte mit dir sprechen.";
			link.l1 = "Ich höre zu, Häuptling. Welche Sorgen haben Sie zu mir gebracht?";
			link.l1.go = "RedChieftain_0";
			link.l2 = "Was willst du von mir, du abscheulicher rothäutiger Affe? Geh zurück in deine Dschungel und belästige mich nicht mit deinen Anfragen.";
			link.l2.go = "RedChieftain_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
		break;
		
		case "RedChieftain_exit":
			dialog.text = "Gu-u! War der weiße Kapitän nicht darauf erzogen, höflich zu sein? Ich habe ein Angebot gemacht. Du verdienst einen Haufen viel Wampum, aber jetzt gehe ich. Lebewohl, Bleichgesicht.";
			link.l1 = "Geh, verschwinde...";
			link.l1.go = "RedChieftain_exit_1";
		break;
		
		case "RedChieftain_exit_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.RedChieftain");
			chrDisableReloadToLocation = false;
			ChangeIndianRelation(-3.0);
		break;
		
		case "RedChieftain_0":
			dialog.text = "Weißer Bruder klug wie Eule, schlau wie Schlange. Ärger geschieht dem Indianer. Groß-großes Kanu der weißen Männer kommt zu meinem Dorf. Sie nehmen viele Cayman, mein Volk, setzen sie auf ihr Kanu und bringen sie zur Mutter aller Gewässer...";
			link.l1 = "Warte... sagst du, dass dein Volk von weißen Männern von einem Schiff versklavt wurde?";
			if (int(pchar.Basenation) == SPAIN) link.l1.go = "RedChieftain_2";
			else link.l1.go = "RedChieftain_1";
		break;
		
		case "RedChieftain_1":
			dialog.text = "Du sprichst wahr, weißer Bruder. Ich weiß, diese Bleichgesichter sind keine Freunde von dir. Diese grausamen weißen Männer vom spanischen Stamm. Sie nehmen mein Volk. Aber ich finde sie. Die Spanier lassen den Indianer von der Morgendämmerung bis zur Abenddämmerung arbeiten, tief in der Mutter der Gewässer tauchen, Muscheln finden, gefüllt mit den Tränen der Götter.";
			link.l1 = "Perlentauchen... Das ist ein brutaler Job.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Spa = "true";
			pchar.questTemp.RedChieftain.AttackNation = SPAIN;
		break;
		
		case "RedChieftain_2":
			dialog.text = "Du sprichst wahr, weißer Bruder. Ich weiß, dass diese Leute keine Freunde von dir sind. Sie vom englischen Stamm. Sie nehmen mein Volk. Aber ich finde sie. Die Engländer lassen den Indianer von der Morgendämmerung bis zur Abenddämmerung arbeiten, tief in die Mutter der Gewässer tauchen, Muscheln gefüllt mit Tränen der Götter finden.";
			link.l1 = "Perlentauchen... Das ist eine harte Arbeit.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Eng = "true";
			pchar.questTemp.RedChieftain.AttackNation = ENGLAND;
		break;
		
		case "RedChieftain_3":
			dialog.text = "Indianer krank und sterben von Sklaverei. Weißer Mann hat kein Mitleid für Indianer. Peitsche und Pistole sind Gesetz des Weißen für den Indianer. Ich alt. Habe keine Männer zum Kämpfen. Kaiman-Arawaks friedliches Volk, wir erfinden Friedenspfeife. Ich bitte dich, weißer Bruder, ziehe Peitsche und Pistole gegen das böse Weiß, rette den Indianer-Arawak.";
			link.l1 = "Fragst du mich, Krieg zu erklären? Du musst verstehen, Häuptling, meine Ressourcen sind begrenzt.";
			link.l1.go = "RedChieftain_4";
		break;
		
		case "RedChieftain_4":
			dialog.text = "Nein, geh auf Kriegspfad. Freier Indianer. Mein Volk. Wir geben dir alle Tränen der Götter, die wir auf Kanus haben. Töte bösen Weißen, helfe Indianer, bekomme Tränen der Götter, verkaufe sie für viel-viel Wampum. Haufen Wampum";
			link.l1 = "Ach, jetzt verstehe ich. Nein, Canauri, ich kann dir nicht helfen. Ich kann es jetzt nicht tun - mein Schiff muss repariert werden, es sind keine Vorräte mehr übrig...";
			link.l1.go = "RedChieftain_wait";
			link.l2 = "In diesem Fall wäre es mir eine Freude. Lassen Sie uns Einzelheiten besprechen. Wo sind Ihre Leute? Sie sagten, dass Sie sie bereits gefunden haben...";
			link.l2.go = "RedChieftain_5";
		break;
		
		case "RedChieftain_wait":
			dialog.text = "Gu-u! Ich kann warten, weißer Bruder... Ich bleibe in diesem Hafen noch einen Mond, suche den Beschützer meines Volkes. Du findest mich hier, wenn du bereit bist.";
			link.l1 = "...";
			link.l1.go = "RedChieftain_wait_1";
		break;
		
		case "RedChieftain_wait_1":
			DialogExit();
			//LAi_ActorGoToLocator(npchar, "quest", "quest1", "RedChieftainStay", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			SetFunctionTimerCondition("RedChieftainDelete", 0, 0, 30, false);
			
			sld = CharacterFromID("RedChieftain");
            //LAi_SetStayType(sld);
			sld.dialog.currentnode = "RedChieftain_wait_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity, false);
		break;
		
		case "RedChieftain_wait_2":
			dialog.text = "Bist du zurück, weißer Bruder? Hilfst du mir, böse Männer zu bestrafen und den Indianer zu retten?";
			link.l1 = "Bereit, wie ich es je sein werde.";
			link.l1.go = "RedChieftain_wait_4";
			link.l2 = "Ich muss mich noch vorbereiten.";
			link.l2.go = "RedChieftain_wait_3";
		break;
		
		case "RedChieftain_wait_3":
			dialog.text = "Ich werde hier sein, weißer Bruder.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.Tempnode = "RedChieftain_wait_2";
		break;
		
		case "RedChieftain_wait_4":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
			dialog.text = "Ich bin sehr froh, dass du zugestimmt hast, weißer Bruder!";
			link.l1 = "Lassen wir uns über die Einzelheiten unterhalten, Canauri. Wo sind deine Leute? Du sagtest, dass du sie bereits gefunden hast...";
			link.l1.go = "RedChieftain_5";
			pchar.quest.RedChieftainDelete.over = "yes"; //снять таймер
		break;
		
		case "RedChieftain_5":
			if (CheckAttribute(pchar, "questTemp.RedChieftain.Spa"))
			{
				AddMapQuestMarkShore("Shore19", true);
				pchar.questTemp.RedChieftain.Island = "Cumana";
				pchar.questTemp.RedChieftain.Shore = "Shore19";
				pchar.questTemp.RedChieftain.Add1 = "Spanish";
				pchar.questTemp.RedChieftain.Add2 = "Carupano Cove, not far from Cumana";
				dialog.text = "Sie lagern in der Bucht von Carupano in der Nähe des spanischen Lagers namens Cumana. Jeden Tag segeln sie auf Booten aufs Meer, tauchen tief, tief...";
				link.l1 = "Ich verstehe. Und die Spanier beobachten sie, während sie tauchen?";
				link.l1.go = "RedChieftain_6";
			}
			else
			{
				AddMapQuestMarkShore("Shore54", true);
				pchar.questTemp.RedChieftain.Island = "SantaCatalina";
				pchar.questTemp.RedChieftain.Shore = "Shore54";
				pchar.questTemp.RedChieftain.Add1 = "English";
				pchar.questTemp.RedChieftain.Add2 = "Cape Perlas, not far from Blueweld";
				dialog.text = "Sie schlagen ihr Lager bei Cape Perlas auf, in der Nähe des englischen Lagers namens Blueweld. Jeden Tag segeln sie auf Booten auf dem Meer, tauchen tief, tief ins Wasser...";
				link.l1 = "Ich verstehe. Und natürlich beobachten die Engländer sie?";
				link.l1.go = "RedChieftain_6";
			}
		break;
		
		case "RedChieftain_6":
			dialog.text = "Ja, zwei große Kanus von Bleichgesichtern mit Feuerstöcken und großen Messern. Lager am Ufer auch bewacht - Indianer kann nicht entkommen.";
			link.l1 = "Welche Art von Schiffen? Können Sie sie beschreiben? Wie groß sind sie? Welche Art von Segeln haben sie?";
			link.l1.go = "RedChieftain_7";
		break;
		
		case "RedChieftain_7":
			dialog.text = "Dieses Kanu ist groß, aber Canauri hat schon größere gesehen. Das vordere Segel ist sehr, sehr schief, macht drei Seiten so. (Er zeichnet drei Lateinersegel und ein trapezförmiges Segel in den Schmutz) Oben ist schmal, unten ist breit.";
			link.l1 = "Sieht und klingt wie eine Schoner...";
			link.l1.go = "RedChieftain_8";
		break;
		
		case "RedChieftain_8":
			dialog.text = "Canauri kennt dieses Wort nicht. Bleichgesichter sehr vorsichtig, wenn sie andere Kanus sehen - sie lassen den Indianer an Land und warten, bis das andere Kanu wegsegelt.";
			link.l1 = "Vorsichtige Hurensöhne...wie kann ich ihnen nahe kommen?";
			link.l1.go = "RedChieftain_9";
		break;
		
		case "RedChieftain_9":
			dialog.text = "Wenn bleichgesicht Bruder kleines Kanu nimmt, dann kann er sich an das Ufer schleichen. Ich zeige den Weg. Aber bring nur ein kleines Kanu mit oder bleichgesicht Hund sieht und treibt Indianer vom Boot in die Dschungel ...";
			link.l1 = "Verstanden. Für diese Operation brauche ich eine Lugger oder eine Sloop. Großartig. Eine Sloop gegen zwei Schooner... Gott... und hier dachte ich, das wird einfach!";
			link.l1.go = "RedChieftain_10";
		break;
		
		case "RedChieftain_10":
			dialog.text = "Gehen wir, weißer Bruder? Wir haben weniger als einen Mond.";
			link.l1 = "Ja. Komm an Bord, Häuptling. Lass uns keine Zeit verschwenden!";
			link.l1.go = "RedChieftain_11";
		break;
		
		case "RedChieftain_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.Red_Chieftain_2.win_condition.l1 = "location";
			pchar.quest.Red_Chieftain_2.win_condition.l1.location = pchar.questTemp.RedChieftain.Island;
			pchar.quest.Red_Chieftain_2.function = "RedChieftain_CreateShooner";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("RedChieftainOver", 0, 0, 30, false);
			AddQuestRecord("RedChieftain", "1");
			AddQuestUserData("RedChieftain", "sText1", pchar.questTemp.RedChieftain.Add1);
			AddQuestUserData("RedChieftain", "sText2", pchar.questTemp.RedChieftain.Add2);
		break;
		
		case "RedChieftain_pearl":
			dialog.text = "Danke dir, weißer Bruder! Du rettest den Cayman Arawak Stamm! Wir schulden dir eine große Schuld. Der Weg ist frei von bleichgesichtigen Hunden und der Indianer kann frei in den Dschungeln laufen. Wir geben dir alle Tränen der Götter, die auf den Booten übrig sind.";
			link.l1 = "Nun, lass uns mal sehen, was du hast...";
			link.l1.go = "RedChieftain_pearl_1";
		break;
		
		case "RedChieftain_pearl_1":
			DialogExit();
			pchar.questTemp.RedChieftain.Ind = 1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_pearl_give":
			int iSmallPearl = rand(200)+rand(250)+rand(200)+250;
			int iBigPearl = rand(100)+rand(100)+rand(50)+150;
			TakeNItems(pchar, "jewelry52", iBigPearl);
			TakeNItems(pchar, "jewelry53", iSmallPearl);
			PlaySound("interface\important_item.wav");
			Log_SetStringToLog("The Chief has given you "+iSmallPearl+" small and "+iBigPearl+" big pearls.");
			dialog.text = LinkRandPhrase("Ich bin froh, dass die Tränen der Götter dir gehören, Bruder der Arawak!","Indianer danken dir, tapferes Bleichgesicht!","Nimm unseren Fang, weißer Bruder!");
			link.l1 = LinkRandPhrase("Freut mich, dir zu helfen!","Danke, rothäutiger Bruder!","Großartig!");
			link.l1.go = "exit";
			pchar.questTemp.RedChieftain.Ind = int(pchar.questTemp.RedChieftain.Ind)+1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_final":
			chrDisableReloadToLocation = false;//открыть локацию
		// belamour legendary edition -->
			if(int(pchar.questTemp.RedChieftain.Tartane) > 5)
			{
				dialog.text = "Canauri dankt dir nochmals, bleichgesichtiger Bruder! Du rettest alle Kanus mit dem Indianer! Für Canauri ist es sehr wichtig, alle Kanus zu retten, weil du auch den Enkel von Canauri rettest, den das böse Bleichgesicht in die Sklaverei nimmt. Als Kind liebte mein Enkel es sehr zu schwimmen, und Kanauri gab ihm dieses verzauberte Amulett, damit der Enkel nicht ertrinkt. Nun will der Enkel nicht mehr schwimmen und gibt das Amulett an mich, damit ich es dir geben kann, bleichgesichtiger Bruder. Ich hoffe, dass die Tränen der Götter und dieses Geschenk eine ausreichende Belohnung für das Leben der Arawak sein werden. Und jetzt verabschieden wir uns - es ist Zeit für uns, in unser Heimatdorf zurückzukehren.";
				link.l1 = "Viel Glück, Cunauri! Schön, dass dein Enkel überlebt hat! Ich bete, dass dieses Übel dich nie wieder trifft!";
				link.l1.go = "RedChieftain_final_1Obereg";
			}
			else
			{
				dialog.text = "Canauri dankt dir nochmals, bleichgesichtiger Bruder! Ich hoffe, dass die Tränen der Götter genug Belohnung für das Leben der Indianer sein werden. Nun auf Wiedersehen, wir gehen in unser Heimatdorf.";
				link.l1 = "Viel Glück, Cunauri! Falle nie wieder in die Sklaverei!";
				link.l1.go = "RedChieftain_final_1";
			}
			if(SandBoxMode)
			{
				//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
				//{
					//if(int(pchar.questTemp.SanBoxTarget) == 2 ||  int(pchar.questTemp.SanBoxTarget) == 5)
					//{
						pchar.questTemp.SanBoxTarget.RedChieftain = true;
						ChangeCharacterComplexReputation(pchar, "fame", 25);
					//}
				//}
			}
		break;
		
		case "RedChieftain_final_1Obereg":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n1 = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n1; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			TakeNItems(pchar, "talisman10", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received Seeker's obereg");
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "9");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		// <-- legendary edition
		
		case "RedChieftain_final_1":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "8");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
