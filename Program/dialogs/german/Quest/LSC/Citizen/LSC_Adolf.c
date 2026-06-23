// Адольф Барбье - авантюрист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && int(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Ich will nicht mit dir reden. Du greifst friedliche Zivilisten ohne Grund an und provozierst sie zum Kampf. Verschwinde!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hallo, Hallo... Ich habe dich noch nie gesehen. Kürzlich?";
				link.l1 = "Du meinst kürzlich auf der Insel? Ja, du hast recht. Mein Name ist "+GetFullName(pchar)+", ein Seemann und ein Abenteurer.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Willst du etwas?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die letzten Klatsch und Tratsch erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ha, genau wie ich. Ich bin zwar kein Seemann, aber meine Leidenschaft für Abenteuer hat mich hierher geführt. Jetzt muss ich auf diesem Schiffsfriedhof verrotten, genau wie die anderen. Übrigens, mein Name ist Adolf Barbier.";
			link.l1 = "Es war schön dich kennenzulernen, Adolf. Auf Wiedersehen.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Ist auf der Insel etwas Neues passiert?","Wirst du mir die neuesten Klatschgeschichten erzählen?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		//----------------------------------Адольф Барбье----------------------------------------
		case "Adolf":
			dialog.text = "Warum zum Teufel bist du ohne meine Erlaubnis in meine Behausung eingedrungen?";
			link.l1 = "Du zeigst schlechte Manieren gegenüber deinem Gast, Adolf. Und ich habe ein Geschäft für dich.";
			link.l1.go = "Adolf_1";
		break;
		
		case "Adolf_1":
			dialog.text = "Ich mache keine Geschäfte mit Leuten, die ich nicht kenne! Raus!";
			link.l1 = "So einfach? Du machst also Geschäfte mit Narwalen, aber nicht mit mir? Schande...";
			link.l1.go = "Adolf_2";
		break;
		
		case "Adolf_2":
			dialog.text = "Wovon redest du, Narr? Was für Geschäfte mit Narwalen? Dies ist deine letzte Chance, von hier weg zu kommen, oder ich werde dich selbst wegwerfen müssen!";
			link.l1 = "Du hast nicht den Mumm dazu, 'Wurfmeister'... Hör mir jetzt zu. Wo ist der Stutzen, den du benutzen wirst, um den Admiral zu erschießen? Wirst du es mir selbst sagen oder soll ich überredender werden?";
			link.l1.go = "Adolf_3";
		break;
		
		case "Adolf_3":
			dialog.text = "Was? Was Stutzen? Welcher Admiral? Bist du verrückt, Kumpel? Ich habe meinen Stutzen verkauft und habe ihn nicht mehr. Und es geht dich einen Dreck an, wem ich ihn verkauft habe. Es ist mir scheißegal, was sie damit machen. Und ich werde niemanden erschießen - weder Admiräle, noch Generäle. Verstehst du mich, Arschloch?";
			link.l1 = "Ich verstehe nur, dass du ein Lügner und Mörder bist, Adolf. Ich weiß, dass du es nicht verkauft, sondern eingelöst hast. Ich weiß auch, dass du eine riesige Summe erhalten hast, um deine Schulden zu begleichen und diese Hütte zu kaufen...";
			link.l1.go = "Adolf_4";
		break;
		
		case "Adolf_4":
			dialog.text = "Das ist mein Geld, du Trottel! Ich habe es verdient! Und ich habe meinen Stutzen verkauft!";
			link.l1 = "Du lügst, Adolf. Du wurdest von den Narwalen angeheuert, um den Admiral zu erschießen. Sie haben dir Geld gegeben, um deinen Stutzen einzulösen. Sie haben auch für diesen Ort bezahlt. Du weißt besser als ich, dass der Bugspriet hinter dieser Tür der einzige Ort auf der Insel ist, um den hinteren Balkon der Shark Residenz zu beschießen.";
			link.l1.go = "Adolf_5";
		break;
		
		case "Adolf_5":
			dialog.text = "Du bist verrückt, Trottel! Du musst sofort isoliert werden! Ich habe ein halbes Jahr auf diese Kabine gewartet, bevor Sessile hier wegging...";
			link.l1 = "Genug. Ich werde dich und deine Kabine durchsuchen, ich werde das Stutzen und einige weitere Beweise finden, da bin ich sicher. Und dann gehen wir zusammen zum Hai. Er wird sich freuen, dir in die Augen zu schauen.";
			link.l1.go = "Adolf_6";
		break;
		
		case "Adolf_6":
			dialog.text = "Ach, du bist ein kranker Bastard! Ich würde lieber sterben, als dass irgendein verrückter Abschaum meine Sachen anfasst!";
			link.l1 = "Dann werde ich sie ohne deine Erlaubnis berühren...";
			link.l1.go = "Adolf_7";
		break;
		
		case "Adolf_7":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "barmen", "stay");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_AdolfDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
			dialog.text = "Nun, lass uns reden. Was möchtest du wissen?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Wie bist du hierher gekommen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Was kannst du mir über die lokalen Clans erzählen?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Haben Sie den äußeren Ring der Schiffe erkundet?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Hat die Insel irgendwelche Verbindungen zu Kuba oder Maine?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ich hatte ein Manuskript eines Seemanns gefunden - Alvarado, er war Spanier. Er beschrieb die Insel mit vielen Details. Er erwähnte ein paar interessante Schiffe - San Augustine, San Geronimo und Tartarus. Alle waren Teil der Staffel von de Betancourt, die vor über fünfzig Jahren verschwand\nIch habe eine Untersuchung über diese Expedition gemacht. Es stellte sich also heraus, dass es ein viertes Schiff namens St. Anna gab, das den Schatz der Staffel trug - einen Haufen Dublonen! Außerdem hatten die Schiffe Gold-Erz in ihren Laderäumen. Ich beschloss, die Insel zu finden\nIch machte einen Deal mit einem Kapitän, den ich kannte, und wir segelten auf seiner Schoner. Es ist klar, wie die Geschichte endete, denke ich. Wir haben die Insel, die Schiffe von Betancourt, sogar seine Nachkommen gefunden - er lebt hier, sein Name ist Antonio de Betancourt. Aber es gelang mir nicht, diesen Ort zu verlassen\nDer Schoner wurde von Riffen zerstört, mein Begleiter starb und ich habe es mit anderen Überlebenden geschafft, hierher zu kommen. Das Schlimmste ist, dass ich nicht das gefunden habe, was ich suchte - weder den Schatz der St. Anna, noch das Gold-Erz.";
			link.l1 = "Ich habe auch Alvarados Notizen gelesen. Faszinierende Geschichte.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Rivados sind verdammte heidnische Abschaum. Sie sind Nachkommen von Negersklaven, die von de Betancourt aus Afrika hierher gebracht wurden. Obwohl sie von den Weißen gelernt haben, wie man Klingen und Musketen benutzt, sind sie immer noch Wilde\nNarwale sind gute Leute, klug und anständige Kämpfer. Sie haben hervorragende Handwerker unter ihnen. Ich kenne viele von ihnen. Vielleicht werde ich eines Tages ihrem Clan beitreten\nPiraten sind ein Ärgernis, verdammt sie. Wir haben sie nicht gerufen, aber sie sind angekommen, haben unsere Vorräte erobert und es gewagt, uns unser eigenes Essen zu verkaufen! Bastarde, hey? Schade, dass wir sie nicht vertreiben können und mit ihrer Anwesenheit leben müssen.";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sicher. Ein Mann muss Geld verdienen. Verfluchte Piraten verlangen Gold, Pesos oder andere Wertsachen für das Essen. Sie verkaufen es viel billiger an Einheimische wie mich als an die Clans, aber es ist trotzdem keine Wohltätigkeit. Gott sei Dank gibt es genug Schiffe im äußeren Ring zum Plündern, viele von ihnen bleiben seit ihrem Untergang von jemandem unberührt\nEine interessante Beschäftigung, doch gefährlich: man kann in den gefluteten Laderaum fallen, Knochen brechen, sich in Seilen verfangen, von Holzteilen zerschmettert werden oder riesige Krabben treffen - sie besuchen oft die Laderäume dort draußen.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Ach, das tut es nicht. Sie sagen, dass Freibeuter und Schmuggler aus Kuba diesen Ort schon vor langer Zeit besucht haben - sie haben Proviant gegen Gold und Waren eingetauscht. Sogar Narwale besuchten Siedlungen. Aber das ist jetzt Geschichte. Niemand würde es wagen, auf zerbrechlichen und kleinen Booten zu segeln. Stürme zerstören kleine Boote in einer Sekunde und wir haben hier keine besseren Schiffe.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum war ich in Gedanken versunken, hast du dich entschieden, meine Truhe zu überprüfen!","Entschieden, meine Truhen zu überprüfen? Du wirst damit nicht davonkommen!");
			link.l1 = "Scheiße!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du beschlossen, meine Truhen zu überprüfen? Damit kommst du nicht durch!";
			link.l1 = "Dummes Mädchen!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier wird es nicht geduldet, mit einer Klinge herumzulaufen. Nimm sie weg.","Hör zu, spiel hier nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin Bürger der Stadt und ich bitte dich, dein Schwert niederzulegen.","Hör zu, ich bin Bürger der Stadt und ich würde dich bitten, dein Schwert niederzuhalten.");
				link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, wenn du mit einer Waffe läufst. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezogener Waffe vor mir herlaufen. Es macht mir Angst...");
				link.l1 = RandPhraseSimple("Habs verstanden.","Ich nehme es weg.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
