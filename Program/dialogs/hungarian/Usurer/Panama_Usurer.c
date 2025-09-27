// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek?"), "Nemrég próbálta ezt a kérdést feltenni nekem...", "Igen, hadd találjam ki... Már megint körbe-körbe jársz?",
                          "Figyelj, én itt a pénzügyekkel foglalkozom, nem válaszolok kérdésekre...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Kitaláltad, sajnálom...", "Megértem...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// Реакция ростовщика Панамы на репутацию ГГ или на разграбление Картахены по сюжету
		case "Panama_Deposit_NoReputation":
			dialog.text = "Így van... Egy becsületes embert, akit a király alattvalói szeretnek, soha nem utasít el a bankom, függetlenül attól, hogy milyen nemzetiségû.";
			link.l1 = "Megértem. Viszontlátásra.";
			link.l1.go = "exit";
		break;
		
		case "Panama_Deposit_Cartahena":
			dialog.text = "De a lányomnak és az apósomnak sajnos volt. Cartagenában éltek. Menj el, "+GetAddress_Form(NPChar)+". Nem látunk itt szívesen.";
			if (pchar.questTemp.Mtraxx.Retribution.Choice == "good")
			{
				link.l1 = "Bocsásson meg. Viszontlátásra.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "A te veszteséged. Viszontlátásra.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
		
		case "Panama_Deposit_SgorelVklad":
			dialog.text = "A pénzt a korona lefoglalta, hogy Cartagena város kifosztásának áldozatait segítse. Nem tudok segíteni. Megkérem, hogy azonnal hagyja el a bankomat, mielôtt kihívom az ôrséget!";
			link.l1 = "Ezt még megbánja...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
