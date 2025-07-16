// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Co myślisz o naszej fortecy? Wygląda dobrze, prawda? A garnizon jeszcze nie jest gorszy, ha...","Życie żołnierza fortu jest dość nudne... Straż i patrole, sen i odpoczynek, a potem wszystko to samo od nowa. Ale w mieście jest inaczej... Czego chcesz, "+GetAddress_Form(NPChar)+"? "),"Nękanie żołnierza głupimi pytaniami nie jest mile widziane, "+GetAddress_Form(NPChar)+"... ","To już trzeci raz, kiedy próbujesz mnie dziś zapytać...","Niełatwo być żołnierzem, a jednak znów tu jesteś"+GetSexPhrase(", durniu,  "," ")+" próbujesz mnie wkurzyć. Uważaj, bo skończysz w piwnicy fortu...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie, przepraszam za kłopot.","Nie mam nic do powiedzenia, przepraszam."),"Masz rację, przepraszam.","Masz rację, to już trzeci raz. Wybacz mi.","Przepraszam, to nic.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
