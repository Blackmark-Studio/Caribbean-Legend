// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Co sądzisz o naszej fortecy? Wygląda dobrze, prawda? A garnizon też się jeszcze nie pogorszył, ha...","Życie żołnierza w forcie jest dość nudne... Stróżowanie i patrolowanie, spanie i odpoczynek, a potem to samo od nowa. Ale w mieście jest inaczej... Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Zawracanie głowy żołnierzowi głupimi pytaniami nie jest mile widziane, "+GetAddress_Form(NPChar)+"...","To już trzeci raz, kiedy próbujesz mnie zapytać dzisiaj...","Niełatwo być żołnierzem, a jednak znowu tu jesteś"+GetSexPhrase(", głupcze,  "," ")+" próbujesz mnie wkurzyć. Uważaj, bo skończysz w piwnicy fortu...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie, przepraszam za kłopot.","Nie mam nic do powiedzenia, przepraszam."),"Masz rację, przepraszam.","Masz rację, to już trzeci raz. Wybacz mi.","Przepraszam, to nic takiego.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
