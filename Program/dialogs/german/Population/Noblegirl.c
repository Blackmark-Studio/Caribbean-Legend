//Jason общий диалог дворянок
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//первая встреча
            if(NPChar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "Hm. Sie segeln unter der Flagge von "+NationNameGenitive(sti(pchar.nation))+", Kapitän. Ich habe keine Lust, mit dem Feind meines Landes zu sprechen. Hmph!";
					link.l1 = "Ach, ja. Ein wahrer Patriot...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = RandPhraseSimple("Was willst du von mir, "+GetAddress_Form(NPChar)+"? Es ist nicht angemessen für einen gewöhnlichen Seemann mit einer edlen Dame zu sprechen, aber ich höre Ihnen zu.","Oh, und was will so ein tapferer Kapitän von mir?");
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Ich werde nicht viel Ihrer Zeit in Anspruch nehmen, ich möchte nur fragen...";
					link.l1.go = "question";
					link.l2 = RandPhraseSimple("Ich muss wissen, was in Ihrer Kolonie vor sich geht.","Ich brauche einige Informationen.");
					link.l2.go = "quests";//(перессылка в файл города)
				}
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Die ganze Stadt ist angespannt - Don Fernando de Alamida, der königliche Inspektor, ist angekommen. Sie wissen, ich habe hier viel gesehen, aber das... Es ist nicht die Trauer, die Menschen verändert, sondern wie sie damit umgehen. Sie sagen, er wurde ein anderer Mann nach dem Tod seines Vaters. Jetzt wirst du keinen unbestechlicheren und... gnadenloseren Diener der Krone im gesamten Archipel finden.","Schau dir nur die 'Heilige Barmherzigkeit' an! Sie sagen, der König selbst habe sie nach besonderen Plänen bauen lassen. Und siehst du - nicht ein einziger Kratzer. Als ob die Jungfrau Maria selbst sie schützt. Obwohl ich Gerüchte gehört habe... vielleicht ist es gar nicht die Jungfrau.","Wissen Sie, wie oft sie versucht haben, Don Fernando zu töten? Zwölf Angriffe in offenen Gewässern - und das nur im letzten Jahr! Nun, mit einer so treuen und geschulten Mannschaft und unter dem Schutz des Herrn - wird er auch das dreizehnte überleben!"),LinkRandPhrase("Haben Sie gehört? Don Fernando de Alamida ist in unserer Stadt angekommen, und man sagt, er sei gerade jetzt irgendwo auf den Straßen. Würde ihn gerne mit meinen eigenen Augen sehen...","Ein komplizierter Mann, dieser Don Fernando. Einige sagen, er sei ein Heiland, der das Mutterland von Unrat reinigt. Andere flüstern, dass nach dem Tod seines Vaters etwas in ihm zerbrochen ist und wir bald alle weinen werden. Aber ich sage dir dies: Fürchte ihn nicht. Fürchte diejenigen, die ihn zu dem gemacht haben, was er ist.","So ein hübscher Mann, dieser Don Fernando! Aber weißt du, was merkwürdig ist? Es ist, als würde er niemanden bemerken. Alles Pflicht und Dienst. Ich hörte, es gab ein Mädchen... aber nach einem Treffen mit einem Priester verzichtete er völlig auf weltliche Freuden. Als hätte er ein Gelübde abgelegt."),RandPhraseSimple(RandPhraseSimple("Verdammter Inspektor! Solange er hier ist, ist die Stadt wie tot. Kein Handel, kein Spaß. Selbst das Atmen, so scheint es, muss leiser sein. Und wissen Sie, was am erschreckendsten ist? Es ist in jedem Hafen dasselbe. Wie ein Uhrwerk. Seine Königliche Majestät hätte diese Folter für uns alle nicht absichtlich erfinden können!","Don Fernando hat das Waisenhaus wieder besucht. Spendet großzügig, betet stundenlang. So ein würdiger Mann sollte den verfluchten Unterschlagern als Beispiel vorgehalten werden!"),RandPhraseSimple("Ha! 'Heiliger' Fernando hat wieder alle Bordelle geschlossen. Nun, macht nichts, er wird bald absegeln und sie werden gleich wieder öffnen.","Der Insp... Inspektor ist angekommen, das ist es! Don Fernando de Almeyda, oder wie war sein Name, Alamida! So wichtig, dass der Gouverneur selbst um ihn herum schleicht. Sie sagen, er sieht dir in die Augen und sieht sofort all deine Sünden. Schrecklich!")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Soll ich mich wiederholen? Ich möchte nicht als Freund verdächtigt werden "+NationNameAblative(sti(pchar.nation))+"! Geh weg oder ich rufe die Wachen! Sie würden sich freuen, mit dir zu sprechen.";
					link.l1 = "Gut, gut, beruhige dich. Ich gehe jetzt.";
					link.l1.go = "exit";
				}
				else
				{
				dialog.text = NPCStringReactionRepeat("Was? Du schon wieder? Such dir jemand anderes zum Reden. Es laufen viele gemeine Leute herum, die sind eher dein Typ. Ich muss jetzt gehen, es wird heute Abend ein Bankett in der Residenz des Gouverneurs geben und meine Allongeperücke ist noch nicht fertig!","Nein, jetzt bist du wirklich nervig! Verstehst du es nicht? Oder bist du begriffsstutzig?","Herr, ich beginne zu vermuten, dass Sie nicht nur ein Idiot, sondern auch ein Schurke und ein Tölpel sind. Ich warne Sie, dass ich meinen Ehemann rufen werde, wenn Sie nicht aufhören, mich mit Ihren dummen Fragen zu belästigen!","Noch ein Wort und ich sage dem Kommandanten, er soll sich um dich kümmern!","Block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Ich verstehe. Lebewohl.","Ja-ja, ich erinnere mich, habe nur vergessen zu fragen...","Du hast mich falsch verstanden...","Beruhigen Sie sich, Dame, ich gehe schon...",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = LinkRandPhrase("In Ordnung, lass uns zuhören.","Oh, gut. Was willst du?","Fragen? Gut, Seemann, ich höre zu.");
			link.l1 = LinkRandPhrase("Können Sie mir das neueste Gerede dieser Stadt erzählen?","Ist hier kürzlich etwas Interessantes passiert?","Gibt es Neuigkeiten aus der Karibik, meine Dame?");
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Bist du verrückt?! Du machst mir Angst! Stecke deine Waffe weg oder ich sage dem Kommandanten, er soll dich im Fort aufhängen!","Bist du verrückt?! Du machst mir Angst! Stecke deine Waffe weg oder ich werde dem Kommandanten sagen, dass er dich im Fort aufhängen soll!");
			link.l1 = LinkRandPhrase("Gut.","Wie Sie wünschen.","Gut.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
