// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania?","Czego sobie życzysz, "+GetAddress_Form(NPChar)+"?"),"Pytania znowu, "+GetAddress_Form(NPChar)+"... ","Pytania, pytania... A co powiesz na wymianę, "+GetAddress_Form(NPChar)+"co?","Słuchaj, jak długo zamierzasz gadać?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Na razie nie mam pytań...","Przykro mi, nie mam teraz nic do powiedzenia..."),"Jeszcze raz, przepraszam...","Może naprawdę nadszedł czas na handel...","Przepraszam, handlujmy...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
