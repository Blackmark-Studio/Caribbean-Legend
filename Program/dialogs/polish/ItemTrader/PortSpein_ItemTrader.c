// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakiego rodzaju pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Znów pytania, "+GetAddress_Form(NPChar)+"...","Pytania, pytania... Może byśmy pohandlowali, "+GetAddress_Form(NPChar)+"co?","Słuchaj, jak długo zamierzasz gadać?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Na razie brak pytań...","Przykro mi, teraz nie mam nic do powiedzenia..."),"Jeszcze raz, przepraszam...","Może rzeczywiście nadszedł czas na handel...","Przepraszam, handlujmy...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Słuchaj, czy imię 'Juan' coś ci mówi?";
				link.l1.go = "Consumption";
			}			
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Nie, nie ma... Teraz, proszę, nie przeszkadzaj mi, jestem dość zajęty... Co za idiotyczne pytanie...";
			link.l1 = "Rozumiem. Przepraszam za zmarnowanie twojego czasu...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
