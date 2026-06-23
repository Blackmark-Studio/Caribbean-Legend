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
			dialog.text = "Wir haben nichts zu besprechen!";
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
			dialog.text = NPCStringReactionRepeat("Hallo! Mein Name ist  "+GetFullName(npchar)+". Was kann ich für Sie tun?","Hallo noch einmal!","Gäste sind in dieser gottverlassenen Gegend sehr selten...","Es ist so eine Freude, mit einem neuen Gesicht zu sprechen! Ich bin schon krank von all diesen alten Schnauzen...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ach, nichts...","Auch ich...","Ich sehe...","Heh...",npchar,Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
		break;
		case "PearlMan_1":
			dialog.text = "Wir sammeln hier Perlen, dienen  "+NationNameGenitive(int(npchar.nation))+", weißt du...";
			link.l1 = "Ja, ich weiß...";
			link.l1.go = "exit";
			link.l2 = "He, hör mal, ist es möglich, einige dieser kleinen Krimskrams direkt vom 'Hersteller' zu kaufen, was würdest du sagen?";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "Ach nein, natürlich nicht! Ein Diebstahl von nur einer kleinen Perle wird mit dem Tod bestraft!";
				link.l1 = "Grausame Befehle habt ihr hier, das ist sicher...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ja, wir haben hier strenge Befehle, und man kann leicht seinen Kopf für jegliches Fehlverhalten verlieren. Ich mache nicht mit bei solchen Sachen, aber ich kann dir raten, mit den lokalen Indianern darüber zu sprechen. Sie haben immerhin einen Ort zum fliehen, wenn etwas schief geht, also sollten sie mutiger sein als wir...";
				link.l1 = "Ich verstehe... In Ordnung, danke.";
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase("Bist du total  "+GetSexPhrase("verrückt? Verschwinde, du Idiot","verrückt? Verschwinde, du dumme Närrin")+"!",""+GetSexPhrase("Was?! Bist du verrückt geworden, Trottel","Was?! Bist du aus dem Häuschen, dummes Mädchen")+"?! Verschwinde mit all deinen Fragen...",""+GetSexPhrase("Hast du deinen Verstand verloren? Welche Piraten? Hier?! Verschwinde einfach, du Dummkopf","Hast du deinen Verstand verloren? Welche Piraten? Hier?! Verschwinde einfach, du dummes Mädchen")+"...");
			link.l1 = RandPhraseSimple("Keine Notwendigkeit, unhöflich zu sein...","Achte auf deine Zunge!");
			link.l1.go = "exit";
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Bleichgesicht","Weiße Squaw")+" will reden?","Du schon wieder, "+GetSexPhrase("Bleichgesicht","weiße Squaw")+".",""+GetSexPhrase("Bleichgesicht mag es zu reden. Er sieht aus wie eine Squaw.","Die weiße Squaw plaudert gern.")+"","Geister brachten mein Bleichgesicht "+GetSexPhrase("Bruder","Schwester")+" zu mir.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ja.","Ja, ich schon wieder.","Sehr poetisch.","Ich freue mich auch, dich zu sehen",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "Sag mir, warum bist du gekommen.";
			link.l1 = "Oh, nichts Besonderes, wollte nur hören, was du zu sagen hast.";
			link.l1.go = "exit";
		break;
		
				
		case "CitizenNotBlade":
			dialog.text = "Kapitän, was machen Sie da? Verstecken Sie Ihre Waffe, bevor Sie Ärger machen!";
			link.l1 = LinkRandPhrase("Gut.","Gut.","Mach dir keine Sorgen, ich stecke es schon weg...");
			link.l1.go = "exit";
		break;  

	}
}
