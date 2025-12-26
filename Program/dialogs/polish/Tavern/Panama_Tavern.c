// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Wszystkie plotki o "+GetCityName(npchar.city)+" do usług. Czego chciałbyś się dowiedzieć?"," Właśnie o tym rozmawialiśmy. Musiałeś zapomnieć...","To już trzeci raz dzisiaj, kiedy mówisz o jakimś pytaniu...","Powtarzasz to wszystko jak papuga...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wiesz, "+NPChar.name+"Może następnym razem.","Dobrze, zapomniałem z jakiegoś powodu...","Tak, to naprawdę już trzeci raz...","Tak...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = "Słyszałem, że w waszym mieście przebywa kaper o imieniu Francois Gontier. Czy wiesz, gdzie można go znaleźć?";
                link.l1.go = "Panama_rat_1";
            }
			// Addon-2016 Jason ”ЊЉ-ѓваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_panama")
            {
                link.l1 = "Spójrz, szukam człowieka o imieniu Bertrand Pinette, słyszałeś o nim? Przybył do Panamy niedawno. Imponujący dżentelmen w peruce. Mógł tu być...";
                link.l1.go = "FMQG";
            }
		break;

		//-->работорговец
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat("Tak, mieliśmy tu takiego jegomościa. Kręcił się po ciemnych zaułkach... Potem przyszli do niego jego kumple, wyglądali jak banda zbirów. Opuścił miasto razem z nimi.","Już o to pytałeś, a ja ci odpowiedziałem.","Mówiłem ci, że już o to pytałeś Gontiera.","Słuchaj, odejdź i przestań mnie niepokoić! Czyś ty zupełnie stracił rozum?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I gdzie on poszedł, wiesz może?","Hm, chyba tak...","Tak, prawda, pytałem o to...","Przepraszam, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;
		
		case "Panama_rat_2":
			dialog.text = "Cóż, jest tylko jedno wyjście stąd na piechotę - Portobello. I on tam pomaszerował. Więc szukaj go tam.";
			link.l1 = "Dzięki, bardzo mi pomogłeś!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
		break;
		//<--работорговец
		
		// Addon-2016 Jason ”ЊЉ-ѓваделупа
		case "FMQG":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("panama");
			dialog.text = "Bertrand Pinette? Francuz? Nigdy o nim nie słyszałem. Nie, kumplu, nie widzieliśmy tu Francuzów od jakiegoś czasu.";
			link.l1 = "Jaka szkoda... Jesteś pewien? Jest przyjacielem ważnego hidalga o imieniu Don Carlos de Milyar. Mieli przybyć tutaj razem.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Senor de Milyar? Ten jegomość odwiedził Panamę rok temu. Właściwie Don Carlos de Milyar mieszka w Portobello. Jest wielkim przyjacielem miejscowego gubernatora.";
			link.l1 = "Rozumiem. Nie było potrzeby marnować czasu i tchu w dżungli. Dziękuję, kamracie.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			pchar.questTemp.FMQG = "headhunter_portobello";
			AddQuestRecord("FMQ_Guadeloupe", "8");
			AddMapQuestMarkCity("PortoBello", true);
			AddLandQuestMark(characterFromId("PortoBello_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
