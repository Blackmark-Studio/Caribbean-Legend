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
			if (GetNationRelation2MainCharacter(int(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple("Brüder, es gibt einen Feind in den Reihen der Inquisition!","Schlagt Alarm, Brüder!");
					link.l1 = "Gewiss, die Feinde der Inquisition sind auf der Hut...";
					link.l1.go = "fight";			
			}
			else
			{	
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hallo, "+GetSexPhrase("mein Sohn","meine Tochter")+". Was hat dich hierher gebracht?..","Ich freue mich, dich in unserer Behausung zu sehen, "+GetSexPhrase("mein Sohn","meine Tochter")+". . Was hat dich hierher gebracht?"),""+GetSexPhrase("Mein Sohn","Meine Tochter")+", wir haben heute schon gesprochen. Brauchst du noch etwas?",""+GetSexPhrase("Mein Sohn","Meine Tochter")+", die Akolythen unserer Ordnung sind nicht für ihre grenzenlose Geduld bekannt. Also, lass mich dich noch einmal fragen: Brauchst du etwas?",RandPhraseSimple("Du lenkst die Anderen von ihren Pflichten ab. Ich werde nicht mehr mit dir reden.",""+GetSexPhrase("Mein Sohn","Meine Tochter")+", Ich mag sinnlose und nutzlose Gespräche nicht. Ich werde nicht mehr mit dir sprechen."),"block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Einfach reingeschneit..","Völlig voll mit Geschäften..."),"Oh, nein, Vater......","Nein, padre, ich wollte nur sprechen...",RandPhraseSimple("Hmm...","Nun, wie Sie wünschen, Vater..."),npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //гарды на камерах
			{
				if (GetNationRelation2MainCharacter(int(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = "Zu den Waffen! Es ist ein Spion! Ergreift ihn!";
					link.l1 = "Verdammt noch mal!";
					link.l1.go = "fight";
				}
				else
				{
					dialog.text = LinkRandPhrase("Das ist eine bewachte Zelle und sie ist strengstens verboten.","Denk gar nicht erst daran, einzutreten, das wird mit dem Tod bestraft.","Nur ein Schritt in diese Zelle und du bist erledigt.");
					link.l1 = RandPhraseSimple("Ich verstehe, Soldat.","Habs verstanden...");	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //заключенные
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("Ho-ho, ist es nicht lustig, diese 'Heiligen' direkt zur Hölle gehen zu sehen?!","Ach du meine Güte, hat wirklich jemand es gewagt, sie herauszufordern?!","Sie haben mich fast zu Tode gefoltert, und ich werde bald sterben, aber du hast mich das letzte Mal in meinem Leben glücklich gemacht...");
					link.l1 = RandPhraseSimple("Heh!","Bitte sehr...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("Diese Heuchler sind absolut unmenschlich. Sie werden in der Hölle brennen für alles, was sie uns angetan haben...","Sie haben mich jeden Tag gefoltert und gequält! Aber ich bin unschuldig vor dem Gesicht unseres Herrn!","Mein Zellengenosse ist gestern gestorben... Sie haben ihn zwei Tage lang auf der Streckbank gefoltert... Und wer weiß, wie lange ich noch aushalte ...");
					link.l1 = RandPhraseSimple("Hmm... Nun, ich weiß nicht...","Ach, ich verstehe...");
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
