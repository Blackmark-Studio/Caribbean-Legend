// Чад Каппер - боцман Акулы и тюремщик
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Brauchst du etwas?";
			link.l1 = "Nein, es ist nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// вариант R
		case "Chimiset":
			dialog.text = "Nun, nun ... Also bist du der geheimnisvolle Dieb? Hm ... Du siehst nicht wie ein elender Plünderer aus.";
			link.l1 = "Hören Sie, Herr, Sie irren sich. Ich bin neu hier, also wie könnte ich wissen, dass der Laderaum, in dem Ihre Leute mich gefangen haben, Ihre private Zone war?";
			link.l1.go = "Chimiset_1";
		break;
		
		case "Chimiset_1":
			dialog.text = "Ach wirklich? Netter Versuch Kumpel... Woher kommst du dann hierher?";
			link.l1 = "Von Main... Durch eine seltsame Statue. Ich selbst weiß nicht, wie ich erklären soll, was passiert ist.";
			link.l1.go = "Chimiset_2";
		break;
		
		case "Chimiset_2":
			dialog.text = "Statue? Ha-ha! Du bist ein lustiger Bursche, nicht wahr... Gut, ich erkläre dir alles selbst: du bist durch das Loch im Schiff geschwommen und wolltest dich in unser Lagerhaus schleichen. Warum erkenne ich dein Gesicht nicht? Ich kenne alle Rivados...";
			link.l1 = "Was Rivados? Ich weiß nicht, wovon du redest! Hör mal, ich bin vor etwa einer Stunde hier angekommen...";
			link.l1.go = "Chimiset_3";
		break;
		
		case "Chimiset_3":
			dialog.text = "Schrei nicht, ich bin kein Idiot. Ja, ich habe genug von deinem Unsinn über die Statue gehört und finde es ziemlich amüsant. Ich finde es verdammt lustig. Wie wäre es, wenn wir zusammen darüber lachen? Ha-ha-ha!... Warum lachst du nicht? Es war ein guter Witz... Rivados. Aber jetzt ist Schluss mit den Witzen. Ich werde dich im Gefängnis verrotten lassen, Kumpel.";
			link.l1 = "Ich bin nicht Rivados! Mein Name ist Charles de Maure!";
			link.l1.go = "Chimiset_4";
		break;
		
		case "Chimiset_4":
			dialog.text = "Das erste Mal, was? Hm ... vielleicht sagst du die Wahrheit. Antworte mir, bist du einer von ihnen?!";
			link.l1 = "Ich schwöre Ihnen, ich habe den Namen noch nie gehört, ich gehöre nicht dazu!";
			link.l1.go = "Chimiset_5";
		break;
		
		case "Chimiset_5":
			dialog.text = "Wirklich? Gut. Beweise es. Geh nach unten, dort sitzt ein Rivados in einem Käfig. Er ist ein gefährlicher Zauberer. Töte ihn, erst dann werde ich überzeugt sein. Ich werde auch deine illegale Eindringen in unser Lager vergessen\nAlso? Bist du bereit? Hab keine Angst, der Zauberer ist unbewaffnet und schwach. Nun, er könnte dich mit einem Zauberspruch zu Staub verwandeln, wie den, der dich in den Halt von San Augustine gebracht hat...";
			link.l1 = "Wenn du diesen Zauber in Aktion gesehen hättest, wärst du nicht so skeptisch. Ich bezweifle, dass du ihn überhaupt überlebt hättest...";
			link.l1.go = "Chimiset_6";
		break;
		
		case "Chimiset_6":
			dialog.text = "Genug geredet! Machst du das oder nicht? Wenn ja, dann nimm diese Machete und kümmere dich um den Zauberer. Sonst wirst du den Rest deines Lebens in einem Käfig verbringen. Verstanden?";
			link.l1 = "Von zwei Übeln wähle ich das kleinere. Gib mir die Machete.";
			link.l1.go = "Chimiset_7";
		break;
		
		case "Chimiset_7":
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "slave_02");
			EquipCharacterbyItem(pchar, "slave_02");
			dialog.text = "Guter Junge. Nimm es, geh und töte den schwarzen Mann. Sein Käfig ist offen. Versuch jetzt nichts Dummes, wir zögern nicht, dich zu erledigen, wenn du auch nur daran denkst! Jetzt geh!";
			link.l1 = "Warum? Hast du Angst, dass ich euch Jungs mit diesem rostigen Stück Metallschrott aufschlitzen werde?";
			link.l1.go = "Chimiset_8";
		break;
		
		case "Chimiset_8":
			dialog.text = "Meine Geduld geht zur Neige. Geh zum Frachtraum und mach, was dir gesagt wird!";
			link.l1 = "Gut, gut, entspann dich. Ich gehe schon...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//разлочим Ф2
		break;
		
		case "Chimiset_9":
			dialog.text = "Du strapazierst meine Geduld, Bastard! Du willst mich nicht reizen...";
			link.l1 = "Gut, gut, entspann dich.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
		break;
		
		case "Fightfail_Final":
			dialog.text = "Hast du diesen Negerzauberer getötet? Gut... Ich bin froh. Du hast bewiesen, dass du kein Rivados bist.";
			link.l1 = "Wann werde ich endlich von dieser verdammten Wanne befreit? Ich muss sofort den Hai treffen.";
			link.l1.go = "Fightfail_Final_1";
		break;
		
		case "Fightfail_Final_1":
			dialog.text = "Du wirst ihm sicher begegnen... Du wirst ihm auf dem Weg zur Hölle begegnen!";
			link.l1 = "Was?!";
			link.l1.go = "Fightfail_Final_2";
		break;
		
		case "Fightfail_Final_2":
			DialogExit();
			DoQuestCheckDelay("LSC_ChadGuardAttack_Fail", 0.1);
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Ha! Schau dir das an. Was machst du hier in meinem Gefängnis?";
			link.l1 = "Dein Name ist Chad Kapper, richtig? Mein Name ist "+GetFullName(pchar)+" und ich bin hier im Auftrag von Shark Dodson. Er hat mir die Schlüssel gegeben.";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Vom Admiral? Hm, ich sehe. Bist du sein neuer Laufbursche?";
			link.l1 = "Zeigen Sie etwas Respekt, Herr. Ich diene niemandem, weder Hai noch Ihnen, und ich werde eine solche Sprache nicht tolerieren.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Ha-ha, du gefällst mir, Kumpel! Vergiss, was ich gesagt habe... Also, was machst du hier?";
			link.l1 = "Shark hat den Befehl gegeben, Chimiset zu befreien, er ist hier eingesperrt.";
			link.l1.go = "prisoner_3";
		break;
		
		case "prisoner_3":
			dialog.text = "Der Rivados Zauberer? Hm. Das ist seltsam, ich bin wirklich überrascht, das zu hören...";
			link.l1 = "Hai gab einen Befehl. Er will Frieden mit den Rivados schließen.";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "A-ah, ich verstehe jetzt. Gut, ich werde einen Mann zu Rivados schicken. Sie werden hierher kommen und ihren Hofnarren mitnehmen.";
			link.l1 = "Warum kannst du ihn nicht einfach gehen lassen?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Ich könnte, aber das wäre zu gefährlich für ihn. Chimiset ist hier bekannt, sein Leben wird nichts wert sein, sobald er auf der 'Esmeralda' - einem Territorium seiner Feinde, den Narwalen - landet. Es gibt keinen anderen Weg aus dem Tartarus, wir können den alten Mann nicht um die Insel schwimmen lassen!\nUnd wenn ihn jemand tötet, werden die Rivados uns die Schuld geben, mich um genau zu sein! Siehst du, ich will keine Probleme, die vermieden werden können. Also werde ich ihn nur unter dem Schutz der Kämpfer seines Clans raus lassen. Vielleicht möchtest du selbst mit Chimiset sprechen? Er ist ein lustiger Typ...";
			if (CheckAttribute(npchar, "quest.chimiset_talk")) link.l1 = "Ich habe schon mit ihm gesprochen, er ist wirklich ein seltsamer Mann. Wie auch immer, ich muss gehen. Bis dann, Chad!";
			else link.l1 = "Das ist es, was ich vorhatte. Ich werde mit ihm sprechen.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			DialogExit();
			sld = characterFromId("Chimiset");
			sld.quest.capper_talk = "true"; // разговор с Каппером состоялся
			if (!CheckAttribute(npchar, "quest.chimiset_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "Ich werde einen Kurier zu den Rivados schicken und sie werden ihren Zauberer mitnehmen. Mach dir keine Sorgen, Kumpel, du kannst gehen.";
			link.l1 = "Gut.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_7";
		break;
		
		// вариант M
		case "Aeva_attack":
			dialog.text = "...er muss das Fass bereits geöffnet haben, da bin ich sicher. Das ist sein liebster Whiskey, verdammt, dieser Ire. Es wird bald vorbei sein, ich habe genug Arsen hineingetan, um eine Herde zu töten...";
			link.l1 = "";
			link.l1.go = "Aeva_attack_1";
			CharacterTurnToLoc(npchar, "quest", "quest2");
		break;
		
		case "Aeva_attack_1":
			dialog.text = "Ach? Verdammt, was machst du hier? Verschwinde!";
			link.l1 = "Ich habe lange nach dir gesucht... Giftmischer. Das ist seltsam, ich sehe den Zyklopen nicht. Du wolltest die Position des Hais einnehmen, oder?";
			link.l1.go = "Aeva_attack_2";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Aeva_attack_2":
			dialog.text = "Ha-ha, der Hai muss jetzt tot sein! Und du wirst ihm bald folgen, Spion!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Aeva_attack_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("ChadNarval_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CapperDieAeva");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Aeva_attack_3":
			dialog.text = "Ach, Spürhund! Nun, dann stirbst du zuerst! Jungs, zu den Waffen!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
