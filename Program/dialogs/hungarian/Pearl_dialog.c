void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Nincs mirôl beszélnünk!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> пиплы в поселении
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat("Helló! A nevem  " + GetFullName(npchar) + ". Mit tehetek érted?", 
				"Üdvözlöm még egyszer!", 
				"A vendégek nagyon ritkák ebben a hátsó túlvilági...",
                "Olyan jó egy új arccal beszélgetni! Már rosszul vagyok a sok régi taknyostól...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ó, semmi...", 
				"Én is...",
                "Értem...", 
				"Heh...", npchar, Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
		break;
		case "PearlMan_1":
			dialog.text = "Mi itt gyöngyöket gyûjtünk, a  " + NationNameGenitive(sti(npchar.nation)) + ", tudod...";
			link.l1 = "Igen, tudom...";
			link.l1.go = "exit";
			link.l2 = "Hé, figyelj, lehetséges, hogy több ilyen kis csecsebecsét közvetlenül a 'termelô', mit szólnál hozzá?";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "Ó, nem, természetesen nem! Már egyetlen kis gyöngy ellopása is halállal büntetendô!";
				link.l1 = "Kegyetlen parancsok vannak itt, az biztos...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Igen, kemény parancsaink vannak itt, és az ember könnyen elveszítheti az életét, ha valami rosszat tesz. Én nem foglalkozom ezzel, de azt tudom tanácsolni, hogy beszéljen errôl a helyi indiánokkal. Nekik van hová menekülniük, ha valami baj történik, így ôk bátrabbak lehetnek, mint mi...";
				link.l1 = "Értem... Rendben, köszönöm.";
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase("Teljesen  "+ GetSexPhrase("ôrült vagy? Tûnj el, te idióta","ôrült? Tûnj el, te hülye bolond") +"!", 
				""+ GetSexPhrase("Mi?! Elment az eszed, te idióta","Mi van?! Elment az eszed, hülye lány") +"?! Tûnj el a kérdéseiddel...", 
				""+ GetSexPhrase("Elment az eszed, drágám? Milyen kalózok? Itt?! Csak tûnj el, te hülye","Elment az eszed, drágám? Milyen kalózok? Itt?! Csak tûnj el, te hülye lány") +"...");
			link.l1 = RandPhraseSimple("Nem kell durvának lenni...", "Vigyázz a nyelvedre!");
			link.l1.go = "exit";
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Sápadtarcú","Fehér squaw") +" akar beszélgetni?", 
				"Már megint te, "+ GetSexPhrase("sápadtarcú","fehér squaw") +".", 
				""+ GetSexPhrase("Paleface szeret beszélgetni. Úgy néz ki, mint a squaw.","Fehér squaw szeret beszélni.") +"",
                "szellemek hozták el hozzám a sápadtarcú "+ GetSexPhrase("bátyámat","húgomat") +" .", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Igen.", 
				"Igen, megint én.",
                "Nagyon költôi.", 
				"Én is örülök, hogy látlak.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "Mondd, miért jöttél?";
			link.l1 = "Ó, semmi különös, csak meg akartam hallgatni, hogy mit akarsz mondani.";
			link.l1.go = "exit";
		break;
		
				
		case "CitizenNotBlade":
			dialog.text = "Kapitány, mit csinál? Rejtsd el a fegyvered, mielôtt nagy bajt okozol!";
			link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ne aggódj, már elraktam...");
			link.l1.go = "exit";
		break;  

	}
}
