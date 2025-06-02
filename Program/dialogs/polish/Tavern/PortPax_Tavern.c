// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Wszystkie plotki o "+GetCityName(npchar.city)+" do usług. Czego chciałbyś się dowiedzieć?","Rozmawialiśmy właśnie o tym. Musiałeś zapomnieć...","To już trzeci raz dzisiaj, gdy mówisz o jakimś pytaniu...","Powtarzasz to wszystko jak papuga...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wiesz, "+NPChar.name+", może następnym razem.","Racja, zapomniałem z jakiegoś powodu...","Tak, to naprawdę już trzeci raz...","Tak...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince")
			{
				link.l1 = "Powiedz mi, czy galeon o nazwie 'Santa Margarita' zatrzymał się ostatnio w twojej kolonii? Może jako zdobycz korsarza?";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.UV_DialogCitizen"))
			{
				link.l1 = "Czy Tristan Renier nie zaglądał tutaj ostatnio?";
				link.l1.go = "UV_DialogTavern";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Kumplu, rzadko kiedy ktoś zahacza o naszą kolonię z łupami, a galionu o takiej nazwie tu nie widzieliśmy. Hispaniola to dzika wyspa, a my jesteśmy małą kolonią. Jest tu cicho. Handlujemy z bukanierami w górach skórami bydlęcymi i suszoną wołowiną. Kapersi zazwyczaj tu się nie kręcą, nie mamy tu burdeli, a Hiszpanie są blisko. Szukaj swojego galionu gdzie indziej.";
			link.l1 = "Rozumiem. Dzięki za radę!";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "7");
			pchar.questTemp.Guardoftruth = "tortuga";
		break;
		
		//--> Украденное воспоминание
		case "UV_DialogTavern":
			dialog.text = "Tristan? Oczywiście, że był. Właściwie to nadal jest, w jednym z pokoi.";
			link.l1 = "Świetnie, czyli przyszedł"+GetSexPhrase("em","am")+" w samą porę. Mam do niego pilną sprawę, więc niestety będę musiał"+GetSexPhrase("","a")+" zakłócić jego spokój.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RoomInTavern");
			DelLandQuestMark(npchar);
		break;
		//<-- Украденное воспоминание
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
