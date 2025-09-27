// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit gondolsz az erôdünkrôl? Jól néz ki, ugye? És a helyôrség sem rosszabb, ha...", "Az erôd katonáinak élete elég unalmas... Ôrködés és járôrözés, alvás és pihenés, majd ugyanez elölrôl. De a városban más a helyzet... Mit akarsz, " + GetAddress_Form(NPChar) + "?"), "Egy katonát ostoba kérdésekkel zaklatni nem szívesen, " + GetAddress_Form(NPChar) + "...", "Ma már harmadszor próbálsz kérdezni...",
                          "Nem könnyû katonának lenni, és mégis itt vagy megint"+ GetSexPhrase(", bunkó,  "," ") +" próbálsz felbosszantani. Vigyázz magadra, különben az erôd pincéjében végzed...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam, elnézést a zavarásért.", "Nincs mit mondanom, elnézést."), "Igazad van, elnézést kérek.",
                      "Igazad van, ez már a harmadik alkalom. Bocsáss meg.", "Bocsánat, ez semmiség.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
