// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Co myślisz o naszej fortecy? Wygląda dobrze, prawda? A garnizon wcale nie gorszy, ha...","Życie żołnierza w fortecy jest dość nudne... Strzeżenie i patrolowanie, spanie i odpoczynek, a potem znów to samo. Ale w mieście jest inaczej... Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Nękanie żołnierza głupimi pytaniami nie jest mile widziane, "+GetAddress_Form(NPChar)+"...","To już trzeci raz, gdy próbujesz mnie dziś zapytać...","Nie jest łatwo być żołnierzem, a jednak oto znowu jesteś tutaj"+GetSexPhrase(", łotrze,  "," ")+" próbujesz mnie wnerwić. Uważaj, bo skończysz w lochu fortu...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie, przepraszam za kłopot.","Nie mam nic do powiedzenia, przepraszam."),"Masz rację, przepraszam.","Masz rację, to już trzeci raz. Przepraszam.","Przykro mi, to nic.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
