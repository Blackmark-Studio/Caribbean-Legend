// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi pytanie jakiś czas temu...","Nie spotkałem ludzi z taką ciekawością ani w mojej stoczni, ani gdziekolwiek indziej w tym mieście.","Co z tymi wszystkimi pytaniami? Moja praca to budowanie statków. Zajmijmy się tym.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz o czym rozmawiać."),"Umph, gdzie się podziała moja pamięć...","Hm, cóż...","Śmiało...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Słuchaj, czy przypadkiem nie zatrzymywał się tu korsarz imieniem Francois Gontier, by z tobą porozmawiać? Wiem, że niedawno był w Porto Bello.";
                link.l1.go = "Portobello_ratS_1";
            }
		break;
		
		case "Portobello_ratS_1":
			dialog.text = "Tak. Nabył ode mnie korwetę i wkrótce wyruszył na morze.";
			link.l1 = "Dziękuję! A czy wiesz, dokąd się udał?";
			link.l1.go = "Portobello_ratS_2";
		break;
			
		case "Portobello_ratS_2":
			dialog.text = "Nie, kumplu, nie mam pojęcia. Naprawiam i sprzedaję statki, nie śledzę, dokąd płyną. To nie moja sprawa.";
			link.l1 = "Cóż, dziękuję... Zobaczmy, dokąd się udałeś...";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello_1";
			AddQuestRecord("Slavetrader", "21_2");
		break;
			
			
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
