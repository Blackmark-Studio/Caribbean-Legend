void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple("Testvéreim, ellenség van az inkvizíció soraiban!", "Riadóztassatok, testvéreim!");
					link.l1 = "Valóban, az inkvizíció ellenségei riadókészültségben vannak...";
					link.l1.go = "fight";			
			}
			else
			{	
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Sziasztok, "+ GetSexPhrase("fiam","lányom") +". Mi szél hozta ide?", "örülök, hogy látlak a hajlékunkban, "+ GetSexPhrase("fiam","lányom") +". Mi szél hozott ide?"),
							""+ GetSexPhrase("fiam","lányom") +", ma már beszéltünk. Szükséged van még valamire?", ""+ GetSexPhrase("fiam","lányom") +", rendünk akolitusai nem a határtalan türelmükrôl híresek. Hadd kérdezzem meg tehát még egyszer: van-e bármire szükséged?",
							RandPhraseSimple("Elvonod mások figyelmét a feladataikról. Nem fogok többet beszélni veled.", ""+ GetSexPhrase("fiam","lányom") +", nem szeretem az értelmetlen és értelmetlen beszélgetéseket. Nem fogok veled többet beszélgetni."), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Csak beugrottam...", "Teljesen tele van üzlettel..."), 
							"Ó, ne, atyám.......", "Nem, atyám, csak beszélni akartam...", RandPhraseSimple("Hmm...", "Nos, ahogy kívánja, atyám..."), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //гарды на камерах
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = "Fegyverbe! Ez egy kém! Fogjátok el!";
					link.l1 = "Caramba!";
					link.l1.go = "fight";
				}
				else
				{
					dialog.text = LinkRandPhrase("Ez egy ôrzött cella, és szigorúan tiltott terület.", "Eszedbe se jusson belépni, halálbüntetés jár érte.", "Csak egy lépés ebbe a cellába, és véged van.");
					link.l1 = RandPhraseSimple("Értem, katona.", "Megvan...");	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //заключенные
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("Ho-ho, hát nem vicces nézni, ahogy ezek a 'szentek' egyenesen a pokolra mennek?!", "Ó, te jó ég, tényleg ki merte bárki is kihívni ôket?!", "Majdnem halálra kínoztak, és hamarosan meg is halok, de te életemben utoljára boldoggá tettél...");
					link.l1 = RandPhraseSimple("Heh!", "Szívesen...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("Ezek a képmutatók teljesen embertelenek. A pokolban fognak égni mindazért, amit velünk tettek...", "Minden nap kínoztak és gyötörtek! De én nem vagyok bûnös a mi Urunk elôtt!", "Tegnap meghalt a cellatársam... Két napig kínozták a kínpadon... És ki tudja, meddig fogom még elviselni ...");
					link.l1 = RandPhraseSimple("Hmm... Hát, nem is tudom...", "Ó, értem...");
					link.l1.go = "exit";
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
	}
}
