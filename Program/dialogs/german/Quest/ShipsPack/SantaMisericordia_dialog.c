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
			dialog.text = "Was braucht ihr?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Alamida_church":
			dialog.text = "...und des Heiligen Geistes. Amen.";
			link.l1 = "Ich sehe selten Militärmänner in Kirchen.";
			link.l1.go = "Alamida_church_2";
		break;
		
		case "Alamida_church_2":
			dialog.text = "Viele glauben, dass Glaube und Schwert unvereinbar sind. Aber schneidet nicht ein Chirurg, um zu heilen? Bestraft nicht ein Vater, um zu schützen?";
			link.l1 = "Hört sich wie eine Rechtfertigung an.";
			link.l1.go = "Alamida_church_3";
			link.l2 = "Da ist Weisheit drin. Manchmal ist Grausamkeit notwendig.";
			link.l2.go = "Alamida_church_4";
		break;
		
		case "Alamida_church_3":
			dialog.text = "Du irrst dich. Das ist keine Rechtfertigung - es ist Verständnis. Als ich meinen Dienst antrat, war jeder Tod... schwierig. Aber dann... wurden meine Augen geöffnet. 'Grausamkeit ist die Manifestation der höchsten Liebe.'";
			link.l1 = "Ich überlasse dich deinen Gebeten.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_4":
			dialog.text = "Ja... ja! Das ist genau das, was er gesagt hat, derjenige, der mich auf diesen Weg geführt hat. 'Barmherzigkeit ohne Stärke ist nutzlos, wie ein Schwert ohne Hand.'";
			link.l1 = "Ich überlasse dich deinen Gebeten.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_5":
			dialog.text = "Bete für uns alle. Für das, was wir tun... und was wir noch tun müssen.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_guber":
			dialog.text = "Sieben Prozent Defizit. Letztes Mal waren es fünf. Wächst wie Unkraut in einem verlassenen Garten...";
			link.l1 = "Gibt es einen neuen Gouverneur in der Stadt?";
			link.l1.go = "Alamida_guber_2";
		break;
		
		case "Alamida_guber_2":
			dialog.text = "Was? Ah, nein. Seine Exzellenz ist dort drüben, in der Ecke. Ich bin don Fernando de Alamida, königlicher Inspektor.";
			link.l1 = "Muss schwere Arbeit sein.";
			link.l1.go = "Alamida_guber_3";
		break;
		
		case "Alamida_guber_3":
			dialog.text = "Weißt du, was das Schwierigste am Kampf gegen Korruption ist? Die Schuldigen sind nicht unbedingt schlechte Menschen. Sie haben Kinder, Familien. Und jedes Mal musst du dich daran erinnern: Gift bleibt Gift, auch wenn es in einem goldenen Becher serviert wird.";
			link.l1 = "Aber kann man so hart urteilen? Wir sind alle Menschen...";
			link.l1.go = "Alamida_guber_4";
			link.l2 = "Du bist zu weich. Nur das Gefängnis wird sie reformieren.";
			link.l2.go = "Alamida_guber_5";
		break;
		
		case "Alamida_guber_4":
			dialog.text = "Gnade für den Wolf ist Grausamkeit für das Schaf. So sagte... ein weiser Mann. Und mit jedem vergehenden Tag verstehe ich seine Weisheit mehr und mehr.";
			link.l1 = "Ich werde Sie nicht länger von Ihrer Arbeit ablenken.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_5":
			dialog.text = "Hm. Weißt du, ich dachte früher genauso. Aber Gefängnis ist zu einfach. Etwas mehr ist nötig... Reinigung.";
			link.l1 = "Ich werde Sie nicht länger von Ihrer Arbeit ablenken.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_6":
			dialog.text = "Ja. Die Papiere warten nicht. Obwohl es mir manchmal so vorkommt, als würde hinter jeder Zahl hier jemandes Schicksal verbergen.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_city":
			dialog.text = "Ich höre aufmerksam zu, "+GetAddress_Form(NPChar)+"? Was hat dich dazu veranlasst, mich einfach so, auf der Straße, anzusprechen?";
			link.l1 = "Du stichst aus der Masse heraus.";
			link.l1.go = "Alamida_city_2";
		break;
		
		case "Alamida_city_2":
			dialog.text = "Don Fernando de Alamida, königlicher Inspektor. Du bist der erste so neugierige heute. Jeder versteckt sich, jeder fürchtet mich. Doch ein ehrlicher Mensch hat nichts zu befürchten. Was sagt uns das?";
			link.l1 = "Dass dein Ruf sie erschreckt?";
			link.l1.go = "Alamida_city_3";
			link.l2 = "Ehrliche Leute sind wenige?";
			link.l2.go = "Alamida_city_4";
		break;
		
		case "Alamida_city_3":
			dialog.text = "Amüsant. Das dachte ich auch. Bis ich verstand - Angst reinigt. Wenn eine Person Angst hat, wird sie ehrlicher. Näher an ihrer wahren Natur. Zu Gott.";
			link.l1 = "Interessanter Gedanke. Ich muss gehen. Guten Tag, Don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_4":
			dialog.text = "Interessant... Du argumentierst genau wie jemand, den ich kannte. Schade, dass nicht jeder diese Wahrheit akzeptieren kann.";
			link.l1 = "Interessanter Gedanke. Ich muss gehen. Guten Tag, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_5":
			dialog.text = "Gut? Ja, vielleicht. Solange es gerecht ist.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_exit":
			DialogExit();
			
			sld = CharacterFromID("SantaMisericordia_clone_church");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_city");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_guber");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
		break;
		
		case "Alamida_repeat":
			dialog.text = "Sonst noch etwas, Kapitän?";
			link.l1 = "Nein, Don Fernando, nur ein Hallo, nichts weiter.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alamida_repeat";
		break;
		
		case "Alamida_abordage":
			if (startHeroType == 4)
			{
				dialog.text = "Eine Maid mit einem Schwert? Nun, ich hätte nie gedacht, dass ich so eine Szene erleben würde. Und wer könnten Sie sein, Señorita, um es zu wagen, die 'Heilige Barmherzigkeit' anzugreifen?";
				link.l1 = "Kapitän Helen McArthur. Und dieser überraschte Ausdruck in Ihrem Gesicht ist einer, den ich gut kenne.";
				link.l1.go = "Alamida_HelenaCaptain";
			}
			else
			{
				dialog.text = "Wie könnt ihr es wagen?! Den 'Heilige Gnade' angreifen?! Ein Schiff, das den Willen des Königs trägt und... Nun. Da du hier bist, sag mir - warum? Warum hast du diesen Wahnsinn gewählt?";
				link.l1 = "Ich bin ein Pirat. Und deine Galeone ist sicherlich voller Schätze.";
				link.l1.go = "Alamida_abordage_Gold";
				link.l2 = "Solch ein wunderschönes Schiff... Ich muss es besitzen.";
				link.l2.go = "Alamida_abordage_Ship";
				link.l3 = "Ich bin ein Feind deines Landes, don Fernando.";
				link.l3.go = "Alamida_abordage_Hater";
				link.l4 = "Einfach so. Warum nicht?";
				link.l4.go = "Alamida_abordage_Prikol";
			}
		break;
		
		case "Alamida_HelenaCaptain":
			dialog.text = "Wie sehr du der Jungfrau Maria ähnelst, Beschützerin unseres Schiffes... Ebenso schön. Aber Sie beschützt die Gerechten, während du...";
			link.l1 = "Ich bin wegen deines Schiffes gekommen. Und Komplimente werden hier nicht helfen, don Fernando.";
			link.l1.go = "Alamida_HelenaCaptain_2";
		break;
		
		case "Alamida_HelenaCaptain_2":
			dialog.text = "Wie traurig. Ich muss dir dann Demut beibringen. Mit Gewalt, da es keinen anderen Weg gibt.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Gold":
			dialog.text = "Ach ja. Natürlich. Gold. Immer Gold. Das Gift, das Seelen zersetzt. Für es wirst du sterben.";
			link.l1 = "Sei nicht so dramatisch. Das ist nur Geschäft.";
			link.l1.go = "Alamida_abordage_Gold_2";
		break;
		
		case "Alamida_abordage_Gold_2":
			dialog.text = "Jede Münze im Laderaum ist die Sündenbezahlung für die Reinigung. Du willst es? Dann teile ihr Schicksal.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Ship":
			dialog.text = "Viele haben die 'Heilige Gnade' begehrt. Ihre Schönheit war der Untergang vieler Kapitäne.";
			link.l1 = "Dann werde ich der Erste sein, der es beansprucht.";
			link.l1.go = "Alamida_abordage_Ship_2";
		break;
		
		case "Alamida_abordage_Ship_2":
			dialog.text = "Barmherzigkeit ohne Stärke ist nutzlos, wie ein Schwert ohne Hand. Diese Lektion wirst du heute lernen.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Hater":
			dialog.text = "Also ist das so. Ein weiterer neidisch auf die Größe des Imperiums.";
			link.l1 = "Welche Größe? Deine starren Wege halten diese Welt zurück.";
			link.l1.go = "Alamida_abordage_Hater_2";
		break;
		
		case "Alamida_abordage_Hater_2":
			dialog.text = "Lüge dir selbst nicht vor. Die Angst vor Spanien macht dich ehrlicher. Näher an deiner wahren Natur. Du wirst es jetzt selbst sehen.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Prikol":
			dialog.text = "Verrückter. Oder vielleicht wurdest du mir als Prüfung geschickt?";
			link.l1 = "Nicht alles braucht einen Grund, señor.";
			link.l1.go = "Alamida_abordage_Prikol_2";
		break;
		
		case "Alamida_abordage_Prikol_2":
			dialog.text = "Er sagte, Leute wie du seien die gefährlichsten. Aber das wird meine Hand im Kampf nur stärken.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_SecondRound":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_BRDENEMY);
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, false);
			LAi_SetCheckMinHP(npchar, 1, true, "SantaMisericordia_TrirdRound");
		break;
		
		case "Alamida_abordage_TrirdRound":
			if (startHeroType == 4)
			{
				dialog.text = "Solche Stärke des Geistes... Solcher Wille...";
				link.l1 = "Überrascht?";
			}
			else
			{
				dialog.text = "Nicht schlecht. Es ist eine Weile her, seit ich einen würdigen Gegner getroffen habe.";
				link.l1 = "Ich werde dir keine Zeit zum Ausruhen geben.";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_2";
		break;
		
		case "Alamida_abordage_TrirdRound_2":
			if (startHeroType == 4)
			{
				dialog.text = "Ich wurde gewarnt... vor solch einer Prüfung. Über Schönheit, die den Glauben eines Kriegers erschüttern könnte.";
				link.l1 = "Komplizieren Sie immer so sehr einfache Dinge, don Fernando?";
			}
			else
			{
				dialog.text = "Der Herr gibt Stärke denen, die einer gerechten Sache dienen. Obwohl... manchmal bin ich mir nicht mehr sicher, wem ich diene.";
				link.l1 = "Hast du Zweifel?";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_3";
		break;
		
		case "Alamida_abordage_TrirdRound_3":
			if (startHeroType == 4)
			{
				dialog.text = "Einfach? Nein... Es muss eine höhere Bedeutung geben. Dies ist eine Prüfung. Ich kann mich nicht irren.";
			}
			else
			{
				dialog.text = "Nein. Er hat mir beigebracht, nicht zu zweifeln. Niemals.";
			}
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_TrirdRound_4";
		break;
		
		case "Alamida_abordage_TrirdRound_4":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			npchar.MultiFighter = 2.5;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_BRDENEMY);
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, false);
			LAi_SetCheckMinHP(npchar, 1, true, "SantaMisericordia_Molitva");
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			PlaySound("Ambient\Horror\Fear_breath_01.wav");
		break;
		
		case "Alamida_abordage_Molitva":
			dialog.text = "Warte... Warte. Du hast gewonnen. Ich bin verwundet, verblute. Lass mich beten vor dem Tod.";
			link.l1 = "Sehr gut.";
			link.l1.go = "Alamida_abordage_Molitva_2";
		break;
		
		case "Alamida_abordage_Molitva_2":
			if (startHeroType == 4)
			{
				dialog.text = "Herr... vergib mir meine Sünden und gib mir Kraft in dieser Stunde der Prüfung. Segne die Seelen meiner gefallenen Kameraden. Treue Seeleute, sie starben im Glauben, dass sie die Gerechtigkeit trugen\nVater, ich habe versucht, nach deinen Lehren zu leben, die Ungerechtigkeit zu bekämpfen. Aber dein Sohn hat die Ehre der Familie Alamida befleckt. Vergib mir\nHeimatland... Ich schwor, dir treu und wahrhaftig zu dienen. Aber mein Eifer, mein Zorn... Ich wurde zu dem, was ich bekämpfen wollte\nDiego... Hat er vielleicht gelogen? Die ganze Zeit... Wehe mir, wenn es so ist\nUnd segne diese Frau, Herr. Vielleicht hast du sie in deiner letzten Barmherzigkeit zu mir gesandt... damit ich sehen könnte, wie weit ich mich verirrt hatte. Amen.";
			}
			else
			{
				dialog.text = "Herr... vergib mir meine Sünden und gib mir Stärke in dieser Stunde der Prüfung. Segne die Seelen meiner gefallenen Kameraden. Treue Matrosen, sie starben im Glauben, dass sie Gerechtigkeit trugen\nVater, ich habe versucht, nach deinen Lehren zu leben, um Ungerechtigkeit zu bekämpfen. Aber dein Sohn hat die Ehre der Familie Alamida befleckt. Vergib mir\nHeimatland... Ich schwor, dir treu und wahrhaftig zu dienen. Aber mein Eifer, mein Zorn... Ich wurde zu dem, was ich bekämpfen wollte\nDiego... Hat er vielleicht gelogen? Die ganze Zeit... Wehe mir, wenn es so ist\nHeilige Jungfrau Maria, bete zu Gott für uns und gewähre uns deine Barmherzigkeit. Amen.";
			}
			link.l1 = "Ich erkenne Sie nicht wieder, Don Fernando. Sie scheinen jetzt eine andere Person zu sein. Und über wen sprachen Sie?";
			link.l1.go = "Alamida_abordage_Molitva_3";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Church_Stay_1", "", 5.0);
		break;
		
		case "Alamida_BitvaEnd":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SantaMisericordia_CanLeaveCauta", 5);
		break;
			
		case "Alamida_abordage_Molitva_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			
			DoQuestFunctionDelay("Alamida_abordage_OfficerPodhodit", 2.0);
		break;
		
		//Элен
		case "Alamida_Helena":
			dialog.text = "Mein Kapitän, Glückwunsch! Was für ein heftiger Kampf. Dieser Kapitän war geschickt, oh so geschickt. Aber du... du hast dich als noch besser erwiesen. Wie stolz ich auf dich bin...";
			link.l1 = "Danke dir, meine Liebe. Bist du verletzt?";
			link.l1.go = "Alamida_Helena_2";
		break;
		
		case "Alamida_Helena_2":
			dialog.text = "Nein, nein. Obwohl ich dachte, wir wären ein paar Mal am Rande - sowohl vor dem Einsteigen als auch währenddessen. Und du, geht es dir gut?";
			link.l1 = "Ich bin in Ordnung, danke nochmal. Geh in die Kajüte und ruh dich aus, ich komme bald zu dir.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Мэри
		case "Alamida_Mary":
			dialog.text = "Charles, bist du in Ordnung? Ich kam so schnell ich konnte, in Ordnung.";
			link.l1 = "Ich bin in Ordnung, danke, Liebes. Es war allerdings ein ziemlicher Kampf.";
			link.l1.go = "Alamida_Mary_2";
		break;
		
		case "Alamida_Mary_2":
			dialog.text = "Ich bin froh! Aber... Hör mal, Charles? Warum haben wir diese Leute angegriffen? Der Herr wird uns das nicht vergeben, nein. Dieses Schiff... wie ein großer Tempel. Als ich es sah, zitterte mein Herz, genau wie beim ersten Mal, als ich eine echte Kirche sah, nicht nur in Büchern. Und jetzt blutet es!";
			link.l1 = "Mary... Du weißt, dass der Schein trügen kann. Und hinter der Maske der Frömmigkeit waren diejenigen, die Geld von einfachen Gläubigen nahmen - genau wie du. Verstehst du?";
			link.l1.go = "Alamida_Mary_3";
		break;
		
		case "Alamida_Mary_3":
			dialog.text = "Ich... Ich glaube dir, Charles. Gut. Nur... lass uns zumindest einen Teil des Goldes, das wir hier gefunden haben, an diejenigen spenden, die es wirklich brauchen? Es würde mein Herz erleichtern.";
			link.l1 = "Wir werden das tun, Mary. Ich verspreche es. Nun sammle deine Gedanken und versuche dich zu beruhigen. Es ist alles vorbei.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Томми
		case "Alamida_Tommi":
			dialog.text = "Ha, nun, Gratulation zu deinem Sieg, Kapitän! Das nenne ich Geschäft! Was für eine Beute auf dieser Galeone!..";
			link.l1 = "Dein Grinsen ist heute noch breiter als sonst, Tommy.";
			link.l1.go = "Alamida_Tommi_2";
		break;
		
		case "Alamida_Tommi_2":
			dialog.text = "Klar doch! Was für eine Beute. Und was für ein Kampf. Erinnerte mich an die Revolution. Und auch... heh.";
			link.l1 = "Was ist los, Tommy? Komm schon, sprich lauter.";
			link.l1.go = "Alamida_Tommi_3";
		break;
		
		case "Alamida_Tommi_3":
			dialog.text = "Wie sie das ganze Schiff wie eine schwimmende Kathedrale geschmückt haben. Und so viel Gold von überall her zusammengetragen haben. Wahre papistische Heilige! Schande und lächerlich.";
			link.l1 = "Das ist ein Schatzschiff, Tommy. Kein Kirchenschiff.";
			link.l1.go = "Alamida_Tommi_4";
		break;
		
		case "Alamida_Tommi_4":
			dialog.text = "Nicht viel Unterschied in unserem Fall. So oder so, ich war froh, diesen Dons und Papisten eine gute Lektion zu erteilen! Kann keinen von beiden ausstehen. Ich habe diesen Tag wirklich genossen, ha-ha-ha!";
			link.l1 = "Du änderst dich nie! Gut, entlassen. Hier ist alles unter Kontrolle.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Тичингиту
		case "Alamida_Tichingitu":
			if (startHeroType == 1)
			{
				dialog.text = "Kapitän Charles, wir erzielen Sieg. Das war ein schwieriger Kampf. Selbst Tichingitu fand es hart, und ich bin einer der besten Krieger im Dorf.";
				link.l1 = "Wahrlich, mein Freund. Sie waren in der Tat würdige Gegner.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Herr de Montoya, das Schiff gehört uns.";
				link.l1 = "Sehr gut, Tichingitu. Ich habe hier auch gerade fertig.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Kapitän Paterson, letzter Widerstand an Bord niedergeschlagen.";
				link.l1 = "Du bist spät dran, Tich! Das nächste Mal bleibst du besser bei mir. Nicht dass ich es nicht alleine schaffen könnte, verstehe mich nicht falsch...";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Kapitän McArthur, geht es Ihnen gut?";
				link.l1 = "Ja, Tichingitu, mir geht es gut, danke der Nachfrage. Und hör auf, an deinem Kapitän zu zweifeln - ich habe das ganz alleine perfekt gemeistert.";
			}
			link.l1.go = "Alamida_Tichingitu_2";
		break;
		
		case "Alamida_Tichingitu_2":
			if (startHeroType == 1)
			{
				dialog.text = "Geister erzählen mir dies während des Kampfes. Und fragen, warum ich sie töte. Jetzt frage ich dich dasselbe. Tichingitu sieht in ihren Augen, sie sind noch keine Schurken. Noch nicht.";
				link.l1 = "Ach, was kann ich dir sagen? Ich habe keine Antwort, Tichingitu.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Mich will dich fragen, Kapitän de Montoya.";
				link.l1 = "Ich höre zu.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Tichingitu möchte Ihnen eine Frage stellen, Kapitän William, wenn Sie es erlauben.";
				link.l1 = "Gewährt.";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Mich nicht Zweifel, mich Sorgen um dich, Kapitän.";
				link.l1 = "In Ordnung, in Ordnung. Ich kann in deinen Augen sehen, dass du mir etwas anderes fragen möchtest.";
			}
			link.l1.go = "Alamida_Tichingitu_3";
		break;
		
		case "Alamida_Tichingitu_3":
			if (startHeroType == 1)
			{
				dialog.text = "Hmm, wie Sie sagen, Kapitän. Sind wir hier fertig?";
				link.l1 = "Ja. Ich werde noch ein bisschen herumschauen, dann treffe ich die anderen.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Diese Leute, sie sind nicht aus demselben Stamm wie du? Sie sind nicht Spanier? Warum hast du beschlossen anzugreifen?";
				link.l1 = "Das ist wahr. Aber kämpfen nicht auch indische Stämme gegeneinander? Oder gibt es nicht Streitigkeiten und Fehden innerhalb eines Stammes?";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Dieses Schiff sieht aus wie eine Kirche. Hasst du die Kirche und den weißen Gott?";
				link.l1 = "Ganz und gar nicht. Aber es ist nur Dekoration, verstehst du? Das ist ein Schatzschiff. Aber du würdest es nicht verstehen - ich habe gehört, dass dein Volk nicht einmal weiß, was Steuern sind. Glückliche Teufel.";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Ja. Sei ehrlich. Kapitän MacArthur, warum greifen wir diese schwimmende Kirche an?";
				link.l1 = "Schwimmende Kirche, ha-ha-ha! Nein, nein. Dies ist ein Schatzschiff. Hmm, ich sehe, du verstehst nicht ganz. Nun, sie transportierten Gold. Ich kann mir vorstellen, wie stolz Jan sein wird, wenn ich ihm erzähle, dass ich Fernando de Alamida besiegt habe!";
				link.l1.go = "Alamida_Tichingitu_4";
			}
		break;
		
		case "Alamida_Tichingitu_4":
			if (startHeroType == 2)
			{
				dialog.text = "Hmm, du hast recht, Kapitän. Aber mit Indianern passiert das weniger als mit weißem Mann.";
				link.l1 = "Vielleicht. Nun, dieser Mann hat... mich gestört.";
				link.l1.go = "Alamida_Tichingitu_5";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Sei ehrlich, die Maskogi haben keine Schlösser und Steuern.";
				link.l1 = "Genau. Du kannst gehen, du bist sowieso zu spät. Später werden wir entscheiden, was wir mit dieser schönen Galeone machen. Ich mag diese Wannen nicht, aber verdammt, sie ist eine Schönheit.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Tichingitu ist auch stolz auf dich, Kapitän. Und gratuliert zum Sieg in diesem harten Kampf.";
				link.l1 = "Danke dir. Jetzt teilen wir die Beute.";
				link.l1.go = "Alamida_BitvaEnd";
			}
		break;
		
		case "Alamida_Tichingitu_5":
			dialog.text = "Einmischen, Señor de Montoya?";
			link.l1 = "Genau. Dieses Archipel ist zu klein für uns beide. Und ich bin für unseren Staat hier von weit größerem Nutzen. Erinnere dich an Kakaoblatt - er hat seinen Brüdern mehr geschadet als genutzt. Gleiches gilt hier.";
			link.l1.go = "Alamida_Tichingitu_6";
		break;
		
		case "Alamida_Tichingitu_6":
			dialog.text = "Jetzt verstehe ich. Darf Tichingitu gehen, Kapitän?";
			link.l1 = "Ja, geh. Ich werde euch allen auch bald beitreten.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			dialog.text = LinkRandPhrase("He, was soll das ganze Waffenschwingen?! Leg es sofort weg!","Ich befehle Ihnen, sofort Ihre Waffe wegzulegen!","He, "+GetAddress_Form(NPChar)+", hört auf, die Leute zu erschrecken! Legt eure Waffe weg.");
			link.l1 = LinkRandPhrase("In Ordnung, ich räume es weg ...","Bereits erledigt.","Wie du sagst...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Verpiss dich!","Ich denke, ich werde es benutzen!","Ich werde es weglegen, wenn die Zeit reif ist.");
			link.l2.go = "fight";
		break;
		
	}
} 