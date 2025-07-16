// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi to pytanie niedawno...","Tak, pozwól, że zgadnę... Znowu krążysz w kółko?","Słuchaj, ja tu zajmuję się finansami, nie odpowiadam na pytania...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz o czym rozmawiać."),"Umph, gdzie podziała się moja pamięć...","Zgadłeś, przepraszam...","Rozumiem...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail":
			dialog.text = "Witaj, Kapitanie. Jak mogę ja i moja firma służyć Tobie?";
			link.l1 = "Chciałbym złożyć darowiznę na fundusz emerytalny znakomitego garnizonu Tortugi.";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Rozumiem. Ostatnio to staje się dość popularne! Ile jesteś winien... to znaczy, chcesz ofiarować?";
			link.l1 = pchar.questTemp.TonzagQuest.Bail+"  дублонów. Powiedz mi, czy przyjmujesz w pesos?";
			link.l1.go = "tonzag_bail_2";
		break;
		
		case "tonzag_bail_2":
			dialog.text = "Oczywiście, jednakże będzie to dla ciebie nieco droższe. Pozwól, że dokładnie ci powiem... "+pchar.questTemp.TonzagQuest.Bail+"  дублони będą "+sti(pchar.questTemp.TonzagQuest.Bail)* 150+" pesos.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail) || sti(pchar.money) >= sti(pchar.questTemp.TonzagQuest.Bail) * 150) {
				link.l1 = "Trochę drożej, powiadasz? Proszę bardzo, oto pełna wymagana kwota.";
				link.l1.go = "tonzag_bail_give";
			} else {
				link.l1 = "„Trochę droższe, powiadasz? Niestety, w tej chwili nie mam takiej kwoty. Czy jest możliwe zaciągnięcie pożyczki na tę sprawę?”";
				link.l1.go = "tonzag_bail_loan";
			}
		break;
		
		case "tonzag_bail_give":
			dialog.text = "Cudownie. Natychmiast poinformujemy twojego kontrahenta! Żegnaj, Kapitanie. I... powodzenia, od dawna czekaliśmy na twój występ.";
			link.l1 = "Do zobaczenia.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail)) {
				RemoveDublonsFromPCharTotal(sti(pchar.questTemp.TonzagQuest.Bail));
			} else {
				AddMoneyToCharacter(pchar, -(sti(pchar.questTemp.TonzagQuest.Bail) * 150));
			}
			sld = CharacterFromID("TortugaJailOff");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "tonzag_bailed";
		break;
		
		case "tonzag_bail_loan":
			dialog.text = "Taka okazja jest zawsze dostępna dla Ciebie, Kapitanie! Powiedzmy, z zwrotem dwustu tysięcy peso za sześć miesięcy?";
			link.l1 = "Nie mam wyboru. Gdzie mam podpisać?";
			link.l1.go = "tonzag_bail_give";
			
			pchar.quest.loans.tortuga.sum = 200000;
			pchar.quest.loans.tortuga.interest = 0;
			pchar.quest.loans.tortuga.period = 6;
			pchar.quest.loans.tortuga.StartDay = GetDataDay();
			pchar.quest.loans.tortuga.StartMonth = GetDataMonth();
			pchar.quest.loans.tortuga.StartYear = GetDataYear();
			pchar.quest.loans.tortuga.StartTime = GetTime();
			SetTimerCondition("Loans_Tortuga", 0, makeint(pchar.quest.loans.tortuga.period), 0, false);
			pchar.quest.Loans_Tortuga.CityId = "Tortuga";
			pchar.quest.Loans_Tortuga.win_condition = "LoansForAll";
			
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.TonzagQuest.Bail) * 150);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
