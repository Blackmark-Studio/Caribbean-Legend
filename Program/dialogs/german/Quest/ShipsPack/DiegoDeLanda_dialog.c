void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Was wollen Sie?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;

		//--> Встреча
		case "DiegoDeLanda_Meeting":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Eine traurige Geschichte, nicht wahr?";
				link.l1 = "Wer sind Sie?";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Guten Tag, Kapitän.";
				link.l1 = "Warten Sie! Wir haben uns schon einmal getroffen!";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "Eins. Zwei. Drei.";
				link.l1 = "Lassen wir dieses Theater. Wer sind Sie wirklich?";
				link.l1.go = "DiegoDeLanda_Meeting_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
			DelLandQuestMark(npchar);
		break;
		
		case "DiegoDeLanda_Meeting_2":
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				dialog.text = "Wissen Sie, was an diesem Grab besonders ist? Hier ruhen zwei Seelen, verbunden durch... Blutsbande. Vater und Sohn de Alameda. Einer fiel durch die Hand von Sündern, der andere... Hm, fand seinen Weg zu Gott.";
				link.l1 = "Das Tagebuch von Don Fernando hat mich hierhergeführt.";
				link.l1.go = "DiegoDeLanda_SantaMisericordia_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				dialog.text = "Haben Sie Lady Bishop gesehen? Ein tragisches Schicksal, nicht wahr? Aber, ich fürchte, ein verdientes.";
				link.l1 = "Sie kennen Elisabeth?";
				link.l1.go = "DiegoDeLanda_LadyBeth_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				dialog.text = "Mortimer Grim.";
				link.l1 = "Sie kannten ihn natürlich?";
				link.l1.go = "DiegoDeLanda_Memento_2";
			}
		break;

		case "DiegoDeLanda_Meeting_Third_2":
			dialog.text = "\nNoch drei. Bei der Zahl sechs werden Sie alles erfahren.";
			link.l1 = " Wenn ich nicht sofort klare Antworten bekomme, dann werde ich...";
			link.l1.go = "DiegoDeLanda_Meeting_Third_3";
		break;

		case "DiegoDeLanda_Meeting_Third_3":
			dialog.text = "\nSie machen gute Fortschritte, Kapitän. Sie verdienen es, meinen Namen zu erfahren. Ich heiße Diego de Landa.";
			link.l1 = " Sind Sie wirklich ein Priester?";
			link.l1.go = "DiegoDeLanda_Meeting_Third_4";
		break;

		case "DiegoDeLanda_Meeting_Third_4":
			dialog.text = "Zuerst und vor allem bin ich ein Künstler. Aber lassen Sie uns nicht voreilig sein...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		//<-- Встреча
		
		//--> Святое Милосердие
		case "DiegoDeLanda_SantaMisericordia_2":
			dialog.text = "Ah... Das Tagebuch. Etwas Erstaunliches – das geschriebene Wort. Es ist wie... ein Pfad durch die Dunkelheit. Führt dorthin, wo... eine Offenbarung wartet. Unsere Gemeinde besuchte Don Fernando oft. Besonders im letzten Jahr.";
			link.l1 = "Dienen Sie in der örtlichen Gemeinde? Kannten Sie Don Fernando?";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_3";
		break;

		case "DiegoDeLanda_SantaMisericordia_3":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_4";
		break;

		case "DiegoDeLanda_SantaMisericordia_4":
			dialog.text = "Ich... beobachtete seinen Weg. Und dieses Buch, das Sie mitgenommen haben. Wissen Sie, was daran so besonders ist?";
			link.l1 = "Es sieht alt aus.";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_5";
		break;

		case "DiegoDeLanda_SantaMisericordia_5":
			dialog.text = "Alt? Oh nein. Es ist... erleuchtet. Die Bibel von Don de Alameda dem Älteren. Jedes Wort darin – ein Leuchtfeuer in der Dunkelheit. Nehmen Sie sie. Helfen Sie Ihren Brüdern in Christus, und vielleicht wird auch Sie etwas... Größeres erwarten.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		//<-- Святое Милосердие

		//--> Леди Бет
		case "DiegoDeLanda_LadyBeth_2":
			dialog.text = "Oh ja. Eine arme Frau. Ihr Ehemann... ist kein guter Mensch. Man sagt, seine Plantagen auf Barbados seien die produktivsten. Und die grausamsten. Wissen Sie, wie viele Sklaven dort jeden Monat sterben? Vor kurzem hat er einen echten Arzt aus England zu Tode geprügelt – einen Mann großen Geistes und Talents. Aber ihr eigenes Schicksal ist kaum besser, glauben Sie mir.";
			link.l1 = "Sie scheinen gut informiert zu sein.";
			link.l1.go = "DiegoDeLanda_LadyBeth_3";
		break;

		case "DiegoDeLanda_LadyBeth_3":
			dialog.text = "Die Menschen kommen zu mir zur Beichte, Kapitän. Ich höre das, was sie sich nicht einmal ihren Nächsten zu sagen trauen. Ihre Ängste, ihre Sünden... ihren Schmerz.";
			link.l1 = "Und fürchten Sie keine Verfolgung? Für einen katholischen Priester ist es nicht einfach auf englischem Gebiet.";
			link.l1.go = "DiegoDeLanda_LadyBeth_4";
		break;

		case "DiegoDeLanda_LadyBeth_4":
			dialog.text = "Meine Ängste sind nichts im Vergleich zu dem, was Sie gerade hinter der Tür dieses Hauses zurückgelassen haben. Und dieses Büchlein, das Sie der unglücklichen Frau abgenommen haben... Wenn Angst eine Form hätte, dann wäre es genau diese.\n"+
		"Ein guter Tag, Kapitän.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;	
		
		//<-- Леди Бет
		
		//--> Мементо
		case "DiegoDeLanda_Memento_2":
			dialog.text = "Tiger, Tiger, brennende Angst\n"+
			"Du brennst in den nächtlichen Wäldern\n"+
			"Welcher unsterbliche Blick, in Liebe, erschuf dich so furchteinflößend?\n"+
			"Natürlich kannte ich ihn, Kapitän. Aber kannten Sie ihn?";
			link.l1 = "Ich habe nie einen Menschen mit einem tragischeren Schicksal getroffen.";
			link.l1.go = "DiegoDeLanda_Memento_3";
		break;

		case "DiegoDeLanda_Memento_3":
			dialog.text = "Doch, haben Sie – aber Sie haben es noch nicht erkannt\n"+
			"Sie kannten Grim also nicht. Auch wenn Sie seinen Schädel in den Händen halten.";
			link.l1 = "Was?!";
			link.l1.go = "DiegoDeLanda_Memento_4";
		break;

		case "DiegoDeLanda_Memento_4":
			dialog.text = "Es ist nicht christlich, so mit den Verstorbenen umzugehen. Hier, nehmen Sie eine kleine post mortem-Anleitung. Mein Geschenk an Sie\n"+
			"Einen guten Tag, Kapitän.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			SetAlchemyRecipeKnown("blade_SP_3low");	// рецепты от Катласа
			SetAlchemyRecipeKnown("blade_SP_3");
		break;

		//<-- Мементо

		//--> Прощание
		case "DiegoDeLanda_Leaving":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving");
		break;

		case "DiegoDeLanda_Leaving_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Sagen Sie... Warum? Es war gefährlich und töricht. Was ist Ihr Feuer, Kapitän? Was treibt Sie an?";
				link.l1 = "Das geht Sie nichts an.";
				link.l1.go = "DiegoDeLanda_leaving_First_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Der Zweite.";
				link.l1 = "Beim letzten Mal sprachen Sie in Rätseln. Werden Sie das auch diesmal tun?";
				link.l1.go = "DiegoDeLanda_leaving_Second_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "...";
				link.l1 = "Warten Sie, de Landa. Ich kann Sie nicht einfach so gehen lassen.";
				link.l1.go = "DiegoDeLanda_Leaving_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{

			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{

			}
		break;
		
		case "DiegoDeLanda_Leaving_First_2": // Первое прощание
			dialog.text = "Ich verstehe es nicht. Die anderen verstehe ich – aber Sie? Noch nicht.";
			link.l1 = "Die anderen?";
			link.l1.go = "DiegoDeLanda_Leaving_First_3";
		break;

		case "DiegoDeLanda_Leaving_First_3":
			dialog.text = "Einer zum Beispiel strebt nach Gerechtigkeit. Ein anderer... war besessen von den dunklen Wassern des Todes. Menschen verlieren sich so leicht in ihren Sehnsüchten. Nicht wahr?";
			link.l1 = "Sie sind ein seltsamer Priester, Heiliger Vater.";
			link.l1.go = "DiegoDeLanda_Leaving_First_4";
		break;

		case "DiegoDeLanda_Leaving_First_4":
			dialog.text = "...";
			link.l1 = "Ich werde dann wohl gehen.";
			link.l1.go = "DiegoDeLanda_Leaving_First_5";
		break;

		case "DiegoDeLanda_Leaving_First_5":
			dialog.text = "Natürlich. Ihre Arbeit beginnt gerade erst, Kapitän.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_leaving_Second_2": // Второе прощание
			dialog.text = "\nEin wahres Rätsel steht nun vor mir. Sie haben bereits zwei... Reliquien gesammelt. Sammeln Sie solche Dinge gern? Sind Sie ein Sammler?";
			link.l1 = "Woher wissen Sie das?";
			link.l1.go = "DiegoDeLanda_leaving_Second_3";
		break;

		case "DiegoDeLanda_leaving_Second_3":
			dialog.text = "Ein Trophäenjäger?";
			link.l1 = "Ich wiederhole meine Frage: Woher wissen Sie das?";
			link.l1.go = "DiegoDeLanda_leaving_Second_4";
		break;

		case "DiegoDeLanda_leaving_Second_4":
			dialog.text = "Ein Adrenalinliebhaber?";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving_Second_5";
		break;

		case "DiegoDeLanda_leaving_Second_5":
			dialog.text = "\nAh. Natürlich. Selbstverständlich. Nun denn, Kapitän, ich will Sie nicht länger aufhalten.";
			link.l1 = "Moment mal, Heiliger Vater. Sie haben meine Frage noch nicht beantwortet.";
			link.l1.go = "DiegoDeLanda_leaving_Second_6";
		break;
		
		case "DiegoDeLanda_leaving_Second_6":
			dialog.text = "Oh, Kapitän. Ich kann nicht. Manchmal verletzen Antworten mehr als Unwissenheit. Gehen Sie in Frieden. Und hüten Sie Ihre Sammlung... von Trophäen. Sie könnten auf der bevorstehenden Reise nützlich sein.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_Leaving_Third_2": // Третье прощание
			dialog.text = "Na los, Kapitän. Ist es Ihnen nicht spannend? Macht es keinen Spaß? Haben Sie genug Trophäen?\n"+
			"In diesem Feuer liegt Ihre Neugier, Kapitän. Sie wollen wissen, wie es weitergeht. Sie lieben schöne Schiffe und faszinierende Dinge\n"+
			"Sie können einfach nicht anders, als sie alle zu sammeln.\n"+
			"\n"+
			"Sie können mich jetzt erschießen.";
			link.l1 = "Was?!";
			link.l1.go = "DiegoDeLanda_Leaving_Third_3";
		break;

		case "DiegoDeLanda_Leaving_Third_3":
			dialog.text = "Nur zu. Aber dann erfahren Sie nicht alles und bekommen nicht das vollständige Set von Trophäen. Die Schiffe erhalten Sie allerdings trotzdem\n"+
			"Guten Tag, Kapitän.";
			link.l1 = "(Gehen lassen)";
			link.l1.go = "DiegoDeLanda_Leaving_End";
			link.l2 = "(Erschießen)";
			link.l2.go = "DiegoDeLanda_Leaving_Shoot";
		break;
		
		case "DiegoDeLanda_Leaving_End":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_End");
		break;
		
		case "DiegoDeLanda_Leaving_Shoot":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_Shoot");
		break;
		
		
		//<-- Прощание
	}
} 