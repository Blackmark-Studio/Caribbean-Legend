// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Co sądzisz o naszej fortecy? Wygląda dobrze, prawda? A garnizon jeszcze nie gorszy, ha...","Życie żołnierza w forcie jest dość nudne... Pilnowanie i patrolowanie, spanie i odpoczywanie, a potem to samo od nowa. Ale w mieście jest inaczej... Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Nękanie żołnierza głupimi pytaniami nie jest mile widziane, "+GetAddress_Form(NPChar)+"...","To już trzeci raz, gdy próbujesz mnie dziś zapytać...","Niełatwo być żołnierzem, a jednak znowu tu jesteś"+GetSexPhrase(", łajdaku, "," ")+" próbujesz mnie wkurzyć. Uważaj, bo skończysz w piwnicy fortu...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie, przepraszam, że zawracam głowę.","Nie mam nic do powiedzenia, wybacz."),"Masz rację, przepraszam.","Masz rację, to już trzeci raz. Wybacz mi.","Przepraszam, to nic takiego.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
