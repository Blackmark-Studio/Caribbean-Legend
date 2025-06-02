// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Śmiało, czego chcesz?","Przed chwilą o tym rozmawialiśmy. Musiałeś zapomnieć...","To już trzeci raz dzisiaj, gdy mówisz o jakimś pytaniu...","Słuchaj, to jest sklep. Ludzie tu kupują rzeczy. Nie przeszkadzaj mi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wiesz, "+NPChar.name+"Może następnym razem.","Racja, z jakiegoś powodu zapomniałem...","Tak, to naprawdę już trzeci raz...","Hm, nie będę...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Słuchaj, mały ptaszek powiedział mi, że ceny czerwonego drewna i kakao w Belize wkrótce wzrosną. Niedawno zrobiłem dobry interes i napchałem sakiewkę dublonami, he-he... Chciałbym nabyć trochę tego towaru. Czy mogę liczyć na zniżkę?";
                link.l1.go = "StoreDone";
            }
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados1")
			{
				link.l1 = "Galera o nazwie 'Admirable' niedawno zacumowała w twojej kolonii pod dowództwem kapitana Gaiusa Marchais. Powiedz mi, czy mógł się tutaj zaopatrzyć w amunicję lub towary do odsprzedaży?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "StoreDone":
			dialog.text = "Cóż, panie, jeśli partia jest naprawdę duża, to oczywiście możemy omówić rozsądny rabat.";
			link.l1 = "Cudownie! Słyszałem, że nowy fluita powinien wkrótce pojawić się na sprzedaż w stoczni. Poczekam i kupię ten statek. Nawet jeśli zdjąłem wszystkie działa z mojego brygu, wciąż nie ma wystarczająco miejsca w ładowni na te wszystkie towary! Wpadnę później!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-11");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ha! Pamiętam tego dziwnego gościa! Uwierzył w jakąś głupią plotkę, że Guadeloupe będzie desperacko potrzebować wanilii, bo jakaś wielka karawana europejskich kupców zatrzyma się tam, żeby kupić tyle przypraw, ile tylko mogą załadować\nSłyszę takie bzdury co miesiąc, ale Marchais wziął to bardzo poważnie. Spędził tu tydzień, kazał mi zebrać wystarczająco wanilii, aby wypełnić jego ładownie\nWygląda na to, że wydał na to każdy grosz. Czuję się źle z powodu tego człowieka, ale nie mogę powstrzymać ludzi przed popadaniem w szaleństwo, jeśli tego chcą.";
			link.l1 = "Więc, może teraz jest na Gwadelupie?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Najprawdopodobniej. Bo będzie dalej czekał na swoich wymyślonych 'kupców' aż do drugiego przyjścia Chrystusa i tylko straci pieniądze, sprzedając wanilię. Jeśli jest mądry, pozostanie w Basse-Terre, aż popyt na wanilię gwałtownie wzrośnie lub dopóki nie dowie się na pewno, że gdzieś indziej jest bardziej potrzebna.";
			link.l1 = "Dziękuję, bardzo mi pomogłeś!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "14");
			pchar.questTemp.Guardoftruth = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1 = "location";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1.location = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.function = "GuardOT_CreateTwoShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
