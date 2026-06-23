// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Mów, słucham";
			link.l1 = "Pomyliłem się. Żegnaj.";
			link.l1.go = "Exit";
			
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaZalog"))
			{
				link.l1 = "Ostatnio jeden z miejskich żołnierzy aresztował i zatrzymał Charliego Knippela. Czy nadal tu jest?"; 
				link.l1.go = "DTSG_AntiguaZalog_2";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов
		case "DTSG_AntiguaZalog_2":
			dialog.text = "Dokładnie tak, ale dlaczego pytasz?";
			link.l1 = "Rzecz w tym, że Charlie jest jednym z moich oficerów. Chciałbym wiedzieć, o co jest oskarżony. Żołnierze, którzy go zabrali, nic mi nie powiedzieli."; 
			link.l1.go = "DTSG_AntiguaZalog_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaZalog_3":
			dialog.text = "Dobrze. To nie jest powszechnie znana informacja. Niestety, nawet dla ciebie. To tajemnica państwowa, panie.";
			link.l1 = "Więc rozumiem, że kaucja nie wchodzi w grę?"; 
			link.l1.go = "DTSG_AntiguaZalog_4";
		break;
		
		case "DTSG_AntiguaZalog_4":
			dialog.text = "Dokładnie. Rozumiem, że to nieprzyjemne stracić cennego załoganta, ale ani ty, ani ja nic na to nie poradzimy. Bardzo mi przykro, Kapitanie.";
			link.l1 = "Nie ma kaucji, jak widzę. A co powiesz na... rekompensatę? Dodam, że hojną. Dla ciebie i wszystkich twoich ludzi, żeby nikt nie został pominięty."; 
			link.l1.go = "DTSG_AntiguaZalog_5";
		break;
		
		case "DTSG_AntiguaZalog_5":
			dialog.text = "Łapówka? Śmiało z twojej strony, Kapitanie, ale żadna suma pieniędzy nie uchroni nas przed gniewem tych, którzy odkryją, że wypuściliśmy Charliego.";
			link.l1 = "Być może... Ale czy mogę przynajmniej z nim porozmawiać?"; 
			link.l1.go = "DTSG_AntiguaZalog_6";
		break;
		
		case "DTSG_AntiguaZalog_6":
			dialog.text = "Czemu nie? Nie możesz nic zrobić, aby go uratować lub pomóc mu uciec, więc... śmiało. Jest w jednej z cel.";
			link.l1 = "Ha, a jeśli powie mi, o co go oskarżono i ujawni tę tajemnicę państwową, którą tak się martwisz, oficerze?"; 
			link.l1.go = "DTSG_AntiguaZalog_7";
		break;
		
		case "DTSG_AntiguaZalog_7":
			dialog.text = "Nie martwię się o to. Zrozumiesz dlaczego. Idź, porozmawiaj ze swoim byłym oficerem, zanim zmienię zdanie.";
			link.l1 = "Dziękuję."; 
			link.l1.go = "DTSG_AntiguaZalog_8";
		break;
		
		case "DTSG_AntiguaZalog_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaZalog");
			pchar.questTemp.jailCanMove = true;
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto9");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Killer", "sold_eng_10", "man", "man", int(pchar.rank), PIRATE, -1, false, "quest"));
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Killer";
			LAi_SetStayType(sld);
			sld.talker = 5;
			GiveItem2Character(sld, "blade_14");
			EquipCharacterbyItem(sld, "blade_14");
			GiveItem2Character(sld, "pistol4");
			EquipCharacterbyItem(sld, "pistol4");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload12");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			LAi_SetImmortal(sld, true);
		break;
		
		case "DTSG_AntiguaTrevoga_2":
			dialog.text = "Nie ma potrzeby, Kapitanie. Jak już mówiłem, zostałbyś wrzucony do tej samej celi co ten głupiec Charlie. Ale po pierwsze, gubernator docenił, że nie stawiałeś oporu przy aresztowaniu, a po drugie, nie był zadowolony z ostatniej wizyty lichwiarza, którego krzyki prawie roztrzaskały okna w pałacu...";
			link.l1 = "Poprosił o moje aresztowanie?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaTrevoga_3":
			dialog.text = "On nie poprosił - on zażądał. A Jego Ekscelencja nie lubi, gdy mu się czegoś żąda. Dlatego temu lichwiarzowi pokazano drzwi.";
			link.l1 = "Przezabawne. Teraz..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_4";
		break;
		
		case "DTSG_AntiguaTrevoga_4":
			dialog.text = "Teraz sugeruję, abyś zrobił to samo, kapitanie de Maure. I nie zadawaj pytań, na które nie dostaniesz odpowiedzi.";
			link.l1 = "Nie opuszczę tego miejsca bez Charliego Knippela."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H1";
			link.l2 = "Proszę, panie, pozwól mi porozmawiać z Charliem Knippelem. Albo przynajmniej dowiedz się, co..."; 
			link.l2.go = "DTSG_AntiguaTrevoga_Ch1";
		break;
		
		case "DTSG_AntiguaTrevoga_H1":
			dialog.text = "W takim razie dołącz do niego. Nie w celi, lecz w zaświatach.";
			link.l1 = "Więc, nie żyje..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H2";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_H2":
			dialog.text = "Jesteś cholernie spostrzegawczy, kapitanie. I mam nadzieję, że zdajesz sobie sprawę, że nie powiem ci, kto to zrobił ani dlaczego.";
			link.l1 = "Czyżby?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_H3";
		break;
		
		case "DTSG_AntiguaTrevoga_H3":
			dialog.text = "Dokładnie. A teraz nie wystawiaj mojej cierpliwości na próbę - zanim rozkażę wrzucić cię do celi za zabicie angielskiego żołnierza.";
			link.l1 = "Biorąc pod uwagę, że niewielu wychodzi z twoich cel, nie chciałbym tam trafić. Nie życzę ci miłego dnia."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_Ch1":
			dialog.text = "Charlie Knippel nie przemówi do nikogo. Chyba że do Stwórcy...";
			link.l1 = "On nie żyje?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_Ch2";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_Ch2":
			dialog.text = "Wyrok został wykonany. Nie mogę podać żadnych szczegółów. I mam nadzieję, że nie będziesz nalegać - to mogłoby źle się dla ciebie skończyć. Nie tylko celą. Czy jestem jasny, kapitanie de Mor?";
			link.l1 = "Jaśniejsze niż słońce. Żegnaj."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaTrevoga");
			AddQuestRecord("DTSG", "10");
			CloseQuestHeader("DTSG");
			ChangeCharacterComplexReputation(pchar, "authority", -10);
			AddCrewMorale(Pchar, -30);
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
