void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		dialog.text = "Fehler. Sag es den Entwicklern.";
		link.l1 = "Sicher.";
		link.l1.go = "exit";
		break;
		
		case "Avendel_tavern":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Oh, ein weiterer tapferer Seemann! Ich kenne deinesgleichen, mein gottverdammtes Auge hat sich an euch gewöhnt, ha! Fragst du dich warum?";
			link.l1 = "Ich werde Sie zu einer anderen Angelegenheit befragen, es geht um Ihre Schuld, die Sie der Herrin des örtlichen... ähm, Etablissements schulden. Sie hat mich gebeten, Sie an Ihre Schuld zu erinnern, ich schlage vor, Sie tun etwas dagegen, sonst wird sie morgen die Wachen damit beauftragen müssen.";
			link.l1.go = "Avendel_tavern_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_1":
			dialog.text = "Lokale Est... oh, verdammt! Johanna, sie kann das nicht mit mir machen! Bist du sicher? Hat sie wirklich gesagt, dass sie mich wegen ein paar verfluchten Münzen in die Kasematten schicken würde?";
			link.l1 = "Absolut. Das hat sie gesagt. Ich nehme an, dass meine Mission vorbei ist, auf Wiedersehen, Mynheer Avendell.";
			link.l1.go = "Avendel_tavern_2";
		break;
		
		case "Avendel_tavern_2":
			dialog.text = "Warte! Bitte, warte! Du siehst aus wie ein erfahrener Kapitän. Sicherlich hast du einige Münzen, ich bin pleite, nur der gute alte Barkeeper füllt meinen Becher auf Kredit wegen unserer alten Freundschaft. Hör dir meinen Vor... Vorschlag an! Du bezahlst meine Schulden und ich schneide dir ein Stück ab\nEs gibt ein Geschäft... ein sehr lukratives Geschäft, verdammt noch mal! Ich schwöre bei meinem blutigen Anker, vertraue mir einfach, Kapitän - wie auch immer du heißt!\nTilge nur eine kleine Schuld, zehntausend Pesos und du hast die Chance, genug Münzen zu verdienen, um alle Bordelle der Neuen-verdammten-Welt zu kaufen! Was sagst du dazu? Du gibst mir, ich gebe dir, wie ehrliche Leute es tun...";
			link.l1 = "Ein zerlumpter Kerl, der Schätze verspricht. Verschone mich mit diesem Mist, ich mache keine Wohltätigkeit für Leute wie dich. Finde das Geld oder du wirst bald in den Kasematten des Forts leben. Lebewohl!";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Eine Scheibe? Und warum sollte ich dem Wort eines betrunkenen Idioten vertrauen? Wegen imaginärer Versprechen?";
			link.l2.go = "Avendel_tavern_4";
		break;
		
		case "Avendel_tavern_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Avendel_tavern_4":
			dialog.text = "Hör mir zu, Kapitän! Hic, schieß mich tot, wenn ich lüge! Aber ich sage die Wahrheit! Denk darüber nach, wenn du mich beim Lügen erwischt, dann wirst du meine Eingeweide mit dieser Schönheit, die du an deinem Gürtel trägst, aufschlitzen! Verdammt, ihr Heft kostet fünfmal mehr als meine elende Schuld! Also was sagst du? Du hast nichts zu verlieren!";
			link.l1 = "Ich habe genug von deinen Reden. Lebewohl.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Gut, Hugo... Ich werde das Risiko eingehen, an diesen Unsinn zu glauben, den du redest. Aber denk daran, dass du mich überzeugen und sicherstellen musst, dass mein Geld nicht umsonst verschwendet wurde, wenn ich zurückkomme, sonst bist du dran.";
			link.l2.go = "Avendel_tavern_5";
		break;
		
		case "Avendel_tavern_5":
			dialog.text = "Keine Drohungen nötig, ich verstehe. Ich gebe dir mein Wort, Kapitän! Wir werden reich sein! Komm zurück, wenn diese verdammte Schuld beglichen ist und wir werden r.. reden! Ja, das werden wir! Du wirst nicht beiseite gelassen!";
			link.l1 = "Also gut, ich werde deine Schulden tilgen, aber bete besser, Hugo Avendell, dass dein 'Vorschlag' mich zufriedenstellen wird.";
			link.l1.go = "Avendel_tavern_6";
		break;
		
		case "Avendel_tavern_6":
			DialogExit();
			pchar.questTemp.Portugal = "HostressMoney";
			Nextdiag.Currentnode = "Avendel_repeat";
			AddLandQuestMark(characterFromId("Marigo_Hostess"), "questmarkmain");
		break;
		
		case "Avendel_repeat":
			dialog.text = "Kapitän, komm so schnell wie möglich zurück - diese Angelegenheit könnte davonlaufen.";
			link.l1 = "Ja, ja, ich werde Ihre Schuld bald begleichen.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_repeat";
		break;
		
		case "Avendel_tavern_7":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Sie sind zurück, Kapitän! Bei Sturm und verdammt noch mal Donner, ich bin so froh, Sie zu sehen! Was ist mit meiner Schuld?";
			link.l1 = "Ich habe mich darum gekümmert, jetzt bist du dran, Hugo. Erzähl mir deine Geschichte und versuche, sie nur ein klein wenig glaubwürdig zu machen!";
			link.l1.go = "Avendel_tavern_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_8":
			dialog.text = "Mach dir keine Sorgen, Kapitän! Wusstest du, dass ich ein Kopfgeldjäger bin? Oder... das war ich zumindest. Ich hatte wohl nicht genug Glück. Vielleicht war sogar der Teufel selbst mit all seinen Taten nicht so ein Verlierer wie ich. Ich habe alles bei meinem letzten Auftrag verloren... Die Crew ist weggelaufen und ich musste mein Schiff wegen der Schulden verkaufen...";
			link.l1 = "Ich bin bereits über deine heroische Vergangenheit informiert. Zur Sache, Hugo, fordere meine Geduld nicht heraus.";
			link.l1.go = "Avendel_tavern_9";
		break;
		
		case "Avendel_tavern_9":
			dialog.text = "Ja, ja, Kapitän..."+GetFullName(pchar)+", habe ich recht? Ich weiß auch etwas über dich. Aber verdammt noch mal, ob es wichtig ist. Hast du den Namen Bartolomeo der Portugiese gehört?";
			link.l1 = "Bart der Portugiese? Natürlich habe ich von ihm gehört. Jeder hat. Er ist ein Pirat, ein Schlächter und ein Abschaum, soweit ich informiert bin. Und was ist seine Rolle in deiner Geschichte?";
			link.l1.go = "Avendel_tavern_10";
		break;
		
		case "Avendel_tavern_10":
			dialog.text = "Verdammt, er spielt eine Hauptrolle darin! Ich habe ihn das letzte anderthalb Jahr verfolgt. Die holländische Gesellschaft hat einen hohen Preis für seinen Kopf ausgesetzt. Aber ich habe versagt und alles verloren. Und die Gesellschaft hat den Preis für ihn kürzlich verdreifacht, nur für ihn lebendig und nur verdammt lebendig!";
			link.l1 = "Aus gutem Grund ist es keine Kleinigkeit, ihn lebendig zu fangen. Wie auch immer, warum sollte mich das interessieren, Hugo? Es sieht so aus, als würdest du versuchen, mich zu übers Ohr hauen!";
			link.l1.go = "Avendel_tavern_11";
		break;
		
		case "Avendel_tavern_11":
			dialog.text = "Ich wollte gar nicht, Kapitän! Sie wissen, der örtliche Arzt Peter Van Stal, ein sehr netter Mann, hat mir einen Trank gegeben, um meine Kopfschmerzen zu heilen! Also, der Arzt war fast drei Tage nicht in seinem Haus und...";
			link.l1 = "Hugo, meine Geduld ist fast am Ende! Ich habe der Dame versprochen, dass ich dich nicht mit meiner Klinge stechen werde, aber meine Fäuste werden es genauso gut machen! Ich schwöre, dass kein Trank in der Lage sein wird, deinen Kopf morgen zu heilen!";
			link.l1.go = "Avendel_tavern_12";
		break;
		
		case "Avendel_tavern_12":
			dialog.text = "Warte, Kapitän! Bitte! Hör mir zu, ich habe einige Kerle in der Nähe des Doktorhauses gesehen und ich habe sie erkannt. Sie sind von der 'Albatros', einer Fregatte der verdammten Portugiesen! Und einer von ihnen sprach über die Gesundheit ihres Kapitäns! Siehst du jetzt, "+pchar.name+", Bartolomeo ist hier, in dieser Stadt! Direkt unter unseren Nasen, er ist entweder verletzt oder krank, deshalb brauchen sie einen verfluchten Arzt!\nIch bezweifle, dass der Portugiese seine ganze Crew hierher gebracht hat, aber ich kann dieses Chaos nicht alleine anfangen! Sicherlich weißt du verdammt nochmal, wie man sein verfluchtes Schwert handhabt! Nimm ein paar harte Kerle mit dir und wir werden die Ratte finden! Dann fangen wir ihn und liefern ihn den Behörden aus!\nUnd zwei Tausend gute Gold-Dublonen sind in unseren Taschen!";
			link.l1 = "Nein, Hugo, ich habe genug von deinem Gerede. Ich werde an diesem Durcheinander nicht teilnehmen, auch wenn du recht hast. Lebewohl.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Hmm, interessant. Wissen Sie, wo er sich versteckt? Wenn es klappt, können wir über Anteile diskutieren, aber wenn das, was Sie mir sagen, die Wahrheit ist, dann müssen wir jetzt schnell handeln!";
			link.l2.go = "Avendel_tavern_13";
		break;
		
		case "Avendel_tavern_13":
			dialog.text = "Nein, ich weiß nicht, wo er ist, Kapitän. Ich hatte zu viel Angst, diesen Burschen nachzujagen. Wenn der Einäugige mich gesehen hätte...fuh! Aber zusammen, plus deine Burschen, werden wir in der Lage sein, diese ganze Stadt zu durchkämmen, ruf deine Männer und lasst uns anfangen! Verdammt, die niederländischen Dublonen warten auf uns! So eine verdammte Chance kommt nur einmal im Leben, beiß mir einen Hering!";
			link.l1 = "Ein lobenswerter Enthusiasmus... Ich hoffe, dass du es schaffst, vom Tisch wegzukommen, ein 'großer' Kopfgeldjäger. Ich werde sofort suchen gehen und du kannst mir folgen, wenn du willst, störe mich nur nicht zu sehr.";
			link.l1.go = "Avendel_tavern_14";
		break;
		
		case "Avendel_tavern_14":
			DialogExit();
			SetFunctionTimerCondition("Portugal_DoctorOver", 0, 0, 2, false);
			pchar.quest.Portugal_Guard.win_condition.l1 = "location";
			pchar.quest.Portugal_Guard.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Portugal_Guard.function = "CreatePortugalGuard";
			AddQuestRecord("Portugal", "1");
			NextDiag.Currentnode = "Avendel_tavern_repeat";
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		
		case "Avendel_tavern_repeat":
			dialog.text = "Ja, ja, Kapitän, lass mich nur mein Getränk beenden und ich werde mich dir anschließen... Wo sollen wir anfangen?";
			link.l1 = "Wo?!... Ich gehe, mit oder ohne dich.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_tavern_repeat";
		break;
		
		case "Portugal_guard":
			dialog.text = "Falsches Haus, Kumpel. Verschwinde, jetzt!";
			link.l1 = "Hm. Und ich glaube, dass es das richtige Haus ist...";
			link.l1.go = "Portugal_guard_1";
		break;
		
		case "Portugal_guard_1":
			dialog.text = "Nun, ich habe dich gewarnt...";
			link.l1 = "...";
			link.l1.go = "Portugal_guard_2";
		break;
		
		case "Portugal_guard_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("PortugalGuard_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.quest.Portugal_Doctor.win_condition.l1 = "location";
			pchar.quest.Portugal_Doctor.win_condition.l1.location = "Marigo_RoomHouseF1";
			pchar.quest.Portugal_Doctor.function = "CreatePortugalDoctor";
		break;
		
		case "Bart_lay":
			dialog.text = "Voll und hart, hoch fliegend, Söhne von... bereitet die Kanonen vor!... ah-ha-ha... oh meine Schönheit...";
			link.l1 = "Hmm, er hat Glück, noch am Leben zu sein...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Bart_lay";
		break;
		
		case "Portugal_doctor":
			pchar.quest.Portugal_DoctorOver.over = "yes";
			dialog.text = "Oh Gott, wer bist du? Bitte leg deine Waffe nieder! Hier liegt ein kranker Mann!";
			link.l1 = "Dieser 'kranke Mann' von Ihnen hat mehr Menschen getötet als Sie in Ihrem Leben gesehen haben, Doktor. Verschwinden Sie!";
			link.l1.go = "Portugal_doctor_1";
		break;
		
		case "Portugal_doctor_1":
			dialog.text = "Er ist mein Patient und er kann nicht mal stehen! Siehst du das nicht? Bitte, leg deine Klinge nieder! Ich flehe dich an!";
			link.l1 = "Und was ist mit ihm los, verdammt noch mal!?";
			link.l1.go = "Portugal_doctor_2";
		break;
		
		case "Portugal_doctor_2":
			dialog.text = "Ich vermute, es liegt alles an seiner Verletzung, einem Schlag von einer vergifteten Waffe eines Kariben... und die Männer, die ihn hierher gebracht haben, sagten, dass ich sterben werde, wenn er stirbt! Aber ich tue alles, was ich kann, sag ihnen das!";
			link.l1 = "Machen Sie sich keine Sorgen um diese Männer, Doktor. Meine Jungs werden auf Ihr Haus aufpassen und ich muss zum Gouverneur gehen. Ich nehme an, er wird sich vor Freude in die Hosen machen. Verlassen Sie diesen Ort nicht, bis ich zurückkehre, Doktor.";
			link.l1.go = "Portugal_doctor_3";
		break;
		
		case "Portugal_doctor_3":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetStayType(npchar);
			Nextdiag.Currentnode = "Doctor_repeat";
			pchar.quest.Avendel_House.win_condition.l1 = "location";
			pchar.quest.Avendel_House.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Avendel_House.function = "AvendelInHouse";
		break;
		
		case "Doctor_repeat":
			dialog.text = "Ich werde nicht gehen, mach dir darüber keine Sorgen. Lassen wir ihn einfach den Behörden übergeben und diesen Albtraum beenden.";
			link.l1 = "Natürlich, ich bin auf dem Weg.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Doctor_repeat";
		break;
		
		case "Avendel_house":
			dialog.text = "Wir haben es geschafft, Kapitän! Wir haben ihn gefunden und werden bald reich sein, genau wie ich es Ihnen gesagt habe! Was ist unser Plan?";
			link.l1 = "Ich hoffe es, Hugo. Wie auch immer, es ist noch nicht vorbei. Ich nehme an, ich muss zum Gouverneur gehen und unsere Belohnung besprechen?";
			link.l1.go = "Avendel_house_1";
		break;
		
		case "Avendel_house_1":
			dialog.text = "Nein-nein, kein Kapitän! Geh nicht zu diesem verdammten Thomas! Vertrau mir, dieser Schurke wird uns unseren Gefangenen wegnehmen und wenn wir Glück haben, wird er uns mit einer Tasse Kaffee behandeln! Seine Exzellenz ist ein zwielichtiger Typ, also wenn du eine volle Belohnung bekommen willst, musst du nach Curacao segeln! Andernfalls wird uns der Portugiese zur Festung gebracht und sie werden uns wie Bettler vertreiben!";
			link.l1 = "Nun, wenn du dir wirklich sicher bist...";
			link.l1.go = "Avendel_house_2";
		break;
		
		case "Avendel_house_2":
			dialog.text = "Ich bin es, Kapitän, verdammt sicher bin ich es! Aber denken Sie daran, dass Bartolomeos Männer irgendwo in der Stadt sein müssen und wir wollen auch nicht die Aufmerksamkeit der Garnison erregen, das ist verdammt sicher! Wir müssen entscheiden, wie wir den Portugiesen zu Ihrem Schiff bringen und wie wir es auf unauffällige Weise tun.";
			link.l1 = "Gut ... Ich möchte nicht gegen seine Fregatte auf dem Weg nach Willemstad kämpfen. Hast du irgendwelche Ideen?";
			link.l1.go = "Avendel_house_3";
		break;
		
		case "Avendel_house_3":
			dialog.text = "Ja, ich habe einen. Wir müssen zuerst einen edleren Anzug für ihn finden, dann schleppen wir ihn als betrunkenen Offizier durch den Hintereingang! Niemand wird vermuten, dass es ein verdammt Pirat ist, vertrau mir!";
			link.l1 = "Hmm, ich bin mir nicht sicher, aber wir haben sowieso noch keinen besseren Plan. Ich werde versuchen, ein hübsches Tuch für unseren Passagier zu besorgen. Du bleibst hier und passt auf Bart und den Doktor auf.";
			link.l1.go = "Avendel_house_4";
		break;
		
		case "Avendel_house_4":
			DialogExit();
			AddQuestRecord("Portugal", "3");
			LAi_ActorRunToLocation(npchar, "reload", "houseF1", "Marigo_houseF1", "goto", "goto2", "", -1);
			pchar.quest.Portugal_Cloves.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Cloves.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Cloves.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Portugal_Cloves.function = "PortugalClovesOver";//1 сутки
			pchar.questTemp.Portugal = "Findcloves";
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "Avendel_house_guard";
			AddLandQuestMark(characterFromId("Marigo_trader"), "questmarkmain");
			QuestPointerToLoc("marigo_town", "reload", "reload6_back");
		break;
		
		case "Avendel_house_guard":
			dialog.text = "Mach dir keine Sorgen, Kapitän. Der Portugiese ist unter meiner zuverlässigen Wache, he-he...";
			link.l1 = "Ich möchte glauben, dass...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_house_guard";
		break;
		
		case "Portugal_doctor_4":
			dialog.text = "Ich sehe die Soldaten nicht, "+GetAddress_Form(NPChar)+". Wo sind sie? Du hast gesagt, dass er verhaftet werden würde, sobald du ihnen von der Situation erzählst. Warum sind die Soldaten also nicht hier?";
			link.l1 = "Es wird keine Soldaten geben, Herr Van Stal. Ich werde die Aufgabe selbst erledigen und ich muss Ihren Patienten so schnell wie möglich nach Curacao bringen.";
			link.l1.go = "Portugal_doctor_5";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_5":
			dialog.text = "Kapitän, hör zu, ich kann seine Wunde nicht behandeln, ich kann nur das Fieber ein wenig senken. Er ist meistens bewusstlos und deliriert, es besteht kein Zweifel, dass er sogar ohne jegliche Einmischung sterben wird und das Rollen des Meeres wird ihn in ein paar Tagen töten. Ich gebe dir einige Mixturen, die helfen werden...";
			link.l1 = "Nein, Doc, Sie segeln mit uns. Erstens, ich bin miserabel in der Medizin und zweitens, ich bezweifle, dass Sie hier bleiben und den Portugiesen erklären möchten, wo ihr Kapitän hin ist?";
			link.l1.go = "Portugal_doctor_6";
		break;
		
		case "Portugal_doctor_6":
			dialog.text = "...Ja, ich vermute, dass du richtig bist. Aber wisse, dass dieser Pirat sehr widerstandsfähig ist, ich habe Leute gesehen, die nur kleine Kratzer von Indianerwaffen hatten und alle starben in weniger als drei Tagen. Und laut seinen 'Freunden' ist er schon seit einer Woche in diesem Zustand! Trotzdem behaupte ich, dass er für eine kurze Zeit auf einem Schiff auf offener See überleben wird. Drei Tage, nicht länger!\nDas ist die ganze Zeit, die wir haben.";
			link.l1 = "Sogar der Vogel würde Curacao in drei Tagen nicht erreichen. Aber ich denke, ich weiß, was ich tun kann! Da ist dieser... Freund von mir, er lebt in St. John's, Antigua. Er weiß, wie man Menschen von tödlichen Wunden heilt. Er ist die einzige Person, die uns jetzt helfen kann. Unser Ziel ist einfach - dort anzukommen, bevor der Portugiese stirbt. Pack deine Sachen, Doc, wir setzen sofort Segel und dein Patient wird als nächstes verlegt!";
			link.l1.go = "Portugal_doctor_7";
		break;
		
		case "Portugal_doctor_7":
			DialogExit();
			AddQuestRecord("Portugal", "5");
			pchar.quest.Portugal_Cloves.over = "yes";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("Avendel");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			RemoveItems(PChar, "suit_1", 1);
			sld = characterFromId("Portugal");
			sld.model = "Port_B"; //меняем модель
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");
			SetFunctionTimerCondition("Portugal_ToAntiguaOver", 0, 0, 4, false);
			pchar.questTemp.Portugal = "ToAntigua";
			QuestPointerDelLoc("marigo_town", "reload", "houseF1");
			//временно для тестов откроем комнату Джино, потом убрать
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);
		break;
		
		case "Avendel_goodbye":
			dialog.text = "Wie schade, Kapitän. Wir haben verloren und wir werden dieses verfluchte Gold nicht sehen. Lebewohl.";
			link.l1 = "Auf Wiedersehen, Hugo.";
			link.l1.go = "Avendel_goodbye_1";
		break;
		
		case "Avendel_goodbye_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		case "Portugal_doctor_9":
			dialog.text = "...";
			link.l1 = "Doktor, bereiten Sie Ihren Patienten auf die Landung vor. Das Beiboot ist bereit. Beeilen Sie sich!";
			link.l1.go = "Portugal_doctor_10";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_10":
			dialog.text = "Ich bin auf dem Weg, "+GetAddress_Form(NPChar)+".";
			link.l1 = "...";
			link.l1.go = "Portugal_doctor_11";
		break;
		
		case "Portugal_doctor_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Portugal_PerenesliVDom1", -1);
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "quest", "quest1");
			sld = characterFromId("Jino");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "goto", "goto3");
			pchar.quest.Portugal_ToAntiguaOver.over = "yes";//снять таймер
			pchar.questTemp.Portugal = "TreatmentStart";
			pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";//не придёт через 7 дня - Португальцу капут
		break;
		
		case "Avendel_Room":
			dialog.text = "Dieses Haus stinkt vor verdammten Mixturen! Es wäre eine große Überraschung, wenn der Portugiese hier stirbt, schon dieser Geruch kann jede Krankheit heilen!\nUnd die Mannschaft des Mannes kann uns dank des Gestanks leicht finden!";
			link.l1 = "Hugo, verschone mich mit deinen Witzen. Ich habe ein paar Männer auf der Straße gelassen, um auf das Haus aufzupassen, aber ein weiterer Wächter wird unserem Gast nicht unnötig sein. Behalte ihn im Auge und versuche, das Fluchen zu unterlassen, oder Gino wird dich dazu bringen, eine seiner Mixturen zu trinken, ich bin sicher, dass er das heilen kann.";
			link.l1.go = "Avendel_Room_1";
		break;
		
		case "Avendel_Room_1":
			dialog.text = "Machen Sie sich keine Sorgen, Kapitän! Ich werde unser Geld auf die aufmerksamste Weise bewachen, es wird nicht weglaufen, selbst wenn es gesund wäre! Und ich bitte Sie, bitte, keine Mischungen mehr!";
			link.l1 = "Siehst du, du kannst nett sein, wenn du willst. Sei auf der Hut, ich muss gehen.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
		break;
		
		case "Avendel_Room_2":
			dialog.text = "Schon gehen, Kapitän? Schön! Es ist Zeit! Ich habe ein paar verf... verdächtige Kerle auf der Straße gesehen. Sie sehen nicht aus wie die Portugiesen, obwohl sie nach etwas suchten, wir müssen vorsichtig sein, Kapitän!";
			link.l1 = "Gut, danke für deine Warnung, Hugo. Lass uns zum Schiff gehen.";
			link.l1.go = "Avendel_Room_3";
		break;
		
		case "Avendel_Room_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			//ставим Португальца
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Portugal_hunter":
			dialog.text = "Kapitän, wir haben viel zu lange auf dieses Treffen gewartet! Und wer ist das bei dir? Bartolomeo der Portugiese selbst, ha, es scheint, dass der Kühne Pierre recht hatte - es ist er! Halt dich fern, Kapitän, wir werden ihn mitnehmen und niemand wird verletzt.";
			link.l1 = "Es tut mir leid, Herr, aber wer zum Teufel sind Sie? Geh aus meinem Weg oder keiner von euch wird morgen sehen!";
			link.l1.go = "Portugal_hunter_1";
		break;
		
		case "Portugal_hunter_1":
			dialog.text = "Oh, was für ein bedrohlicher Kerl, schaut ihn euch nur an, Jungs! Ha-ha-ha! Hör zu, Welpe, stell dich nicht zwischen Leo Cord und sein Geld! Wir haben den Portugiesen fast ein halbes Jahr lang verfolgt und haben ihn endlich erwischt. Also leg deinen Zahnstocher ab und verschwinde, solange du noch atmest! Wir sind nicht so gierig, ein toter Mann reicht uns völlig, ha-ha!";
			link.l1 = "Genug. Lasst uns tanzen, Herren!";
			link.l1.go = "Portugal_hunter_2";
		break;
		
		case "Portugal_hunter_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
		DialogExit();
		sld = characterFromId("Portugal");
		LAi_group_Register("Bart_Portugal");
		LAi_group_SetRelation("Bart_Portugal", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(sld, "Bart_Portugal");
		for (i=1; i<=5; i++)
		{
		sld = characterFromId("PortugalHunter_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PortugalHunterDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_street":
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Ich wusste, dass hier etwas nicht stimmt! Gut gemacht, Kapitän! Aber es ist Zeit zu gehen, dieser verfluchte Leo Cord hat hier viele Banditen und ein feines Schiff! Wir müssen von dieser Insel wegkommen!";
				link.l1 = "Guter Punkt, Hugo, und ich bin sehr froh, dass keine Kugel auf das Loch geschossen wurde, in dem du dich versteckt hast.";
				link.l1.go = "Avendel_street_1";
			}
			else
			{
				dialog.text = "Wie schade, Kapitän. Wir haben verloren und wir werden das verdammte Gold nicht sehen. Lebewohl.";
				link.l1 = "Auf Wiedersehen, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				sld = characterFromId("PortugalDoctor");
				RemovePassenger(Pchar, sld);
				sld.lifeday = 0;
				RemovePassenger(Pchar, npchar);
				AddQuestRecord("Portugal", "35");
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_street_1":
			dialog.text = "Ich... Ich sicherte unseren Rücken, Kapitän! Du hast es ohne mich gut gemacht, aber was wäre, wenn uns jemand von der anderen Straßenseite angegriffen hätte? Du hättest keine Zeit gehabt, zum Schiff zu laufen.";
			link.l1 = "Vielleicht ist das der Grund, warum du in deinem Beruf nicht erfolgreich warst? Wie auch immer, genug geredet, wir müssen zum Schiff! Die Zeit läuft uns davon!";
			link.l1.go = "Avendel_street_2";
		break;
		
		case "Avendel_street_2":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			AddQuestRecord("Portugal", "8");
			pchar.quest.Portugal_seahunter.win_condition.l1 = "location";
			pchar.quest.Portugal_seahunter.win_condition.l1.location = "Antigua";
			pchar.quest.Portugal_seahunter.function = "PortugalSeaHunter";
			pchar.quest.Portugal_martinique.win_condition.l1 = "location";
			pchar.quest.Portugal_martinique.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_martinique.function = "PortugalOnMartinique";
		break;
		
		case "Portugal_doctor_12":
			dialog.text = "Kapitän, dem Portugiesen geht es wirklich schlecht, wir müssen anhalten!";
			link.l1 = "Darum sind wir hier, mein Herr van Stal, unsere Reise ist fast vorbei. Ich werde ein Zimmer in der Taverne mieten und unser Gefangener wird dort ein paar Tage bleiben.";
			link.l1.go = "Portugal_doctor_13";
		break;
		
		case "Portugal_doctor_13":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5);
		break;
		
		case "Portugal_doctor_14":
			dialog.text = "Herr Kapitän, ich werde mich um den Portugiesen kümmern, er braucht volle Ruhe.";
			link.l1 = "Ich hab's kapiert, Doc, es ist in Ordnung. Verdammt, wie lange soll ich mich um diesen Piraten kümmern? Das ist schlecht für ihn, das ist nicht das, was er braucht! Es scheint, dass ich als Babysitter eingestellt wurde und... agh, entschuldigen Sie mir, Doktor, es ist einfach zu viel... Wir sehen uns später.";
			link.l1.go = "Portugal_doctor_15";
		break;
		
		case "Portugal_doctor_15":
			DialogExit();
			AddQuestRecord("Portugal", "15");
			pchar.quest.Portugal_patrol.win_condition.l1 = "location";
			pchar.quest.Portugal_patrol.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_patrol.function = "CreateFrancePatrol";
		break;
		
		case "Portugal_patrol":
			dialog.text = "Herr, sind Sie Kapitän "+GetFullName(pchar)+", dessen Schiff heute in unserem Hafen angekommen ist?";
			link.l1 = "Sie haben recht, wie kann ich Ihnen helfen?";
			link.l1.go = "Portugal_patrol_1";
		break;
		
		case "Portugal_patrol_1":
			dialog.text = "Seine Exzellenz Jacques Dille du Parquet, der Gouverneur unserer Kolonie, erwartet Sie. Die Angelegenheit ist dringend!";
			link.l1 = "Gut, Monsieur, ich werde Seine Exzellenz heute besuchen.";
			link.l1.go = "Portugal_patrol_2";
		break;
		
		case "Portugal_patrol_2":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Portugal = "MartiniqueGovernor";
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			AddQuestRecord("Portugal", "9");
		break;
		
		case "Avendel_seapatrol":
			dialog.text = "Wir haben Martinique erreicht, Kapitän! Unser Geld ist jetzt nicht mehr weit entfernt...";
			link.l1 = "Nur wenn der Portugiese bis zu unserer Ankunft in Willemstad lebt. Hugo, ich muss zum Schiff gehen, also musst du auf den Arzt und seinen Patienten aufpassen.";
			link.l1.go = "Avendel_seapatrol_1";
		break;
		
		case "Avendel_seapatrol_1":
			dialog.text = "Zum Schiff gehen? Warum? Würden Sie mir einige Ihrer Männer leihen, um mir zu helfen? Was ist, wenn etwas passiert, während Sie weg sind?";
			link.l1 = "Es tut mir leid, aber nein. Ich bezweifle, dass hier irgendetwas Ihnen drohen könnte. Die Garnison ist alarmiert und es sind mehr Soldaten auf den Straßen als gewöhnlich, also rufen Sie sie, wenn etwas schief geht. Sie haben ein großes Schiff nicht weit von dieser Insel gesehen, vielleicht ein Piratenschiff. Und Seine Exzellenz der Gouverneur hat mich gebeten, die Insel durch Patrouillieren mit meinem Schiff zu befestigen.";
			link.l1.go = "Avendel_seapatrol_2";
		break;
		
		case "Avendel_seapatrol_2":
			dialog.text = "Ein Schiff? Ein Piratenschiff? Es könnte der Albatros sein! Oder ein Kollege unseres alten Freundes Leo Cord!";
			link.l1 = "Oder vielleicht ist es nur ein gewöhnliches Piratenschiff. Nichtsdestotrotz, Hugo, wenn dieses Schiff hier ist, um unsere Köpfe zu holen, dann stelle ich mich ihr lieber mit der örtlichen Patrouille an meiner Seite und für das Gold des Gouverneurs. Das ist viel besser, als den Rest der Reise über unsere Rückseite zu wachen. Wenn dieser Alarm jedoch falsch ist, dann wird es mich einfach davon abhalten, meinen Arsch ein paar Tage in der Taverne zu parken.";
			link.l1.go = "Avendel_seapatrol_3";
		break;
		
		case "Avendel_seapatrol_3":
			dialog.text = "Denken Sie mal nach, Kapitän, ist es klug, den Damm... die Portugiesen ungeschützt zu lassen, während seine Fregatte herumschleichen könnte? Sie riskieren unsere Belohnung, indem Sie die Gebühr des Gouverneurs akzeptieren!";
			link.l1 = "Genug geredet, Hugo Avendell! Ich bin der Kapitän hier und die endgültige Entscheidung liegt bei mir! Also tu, wie ich dir befehle. Geh zur Taverne und behalte den Arzt und den Portugiesen im Auge, bis ich zurück bin.";
			link.l1.go = "Avendel_seapatrol_4";
		break;
		
		case "Avendel_seapatrol_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);//закрыть таверну
		break;
		
		case "Avendel_seapatrol_5":
			dialog.text = "Sie sind endlich zurück, Kapitän! Ich fürchte, ich habe schlechte Nachrichten für Sie - der Portugiese ist fort und der Doktor ebenfalls!";
			link.l1 = "Wie?! Und was hast du dann gemacht, Dummkopf?!";
			link.l1.go = "Avendel_seapatrol_6";
		break;
		
		case "Avendel_seapatrol_6":
			dialog.text = "Ich wette, dass das Schiff die 'Albatros' war. Ich habe die Portugiesen gesehen, sie sind in die Kneipe gegangen und ich... ich bin weggelaufen. Es tut mir leid, aber der Einäugige Hund zu treffen war selbst für so viel Geld zu viel!";
			link.l1 = "Verdammt! Sag mir wenigstens, was in der Taverne passiert ist?";
			link.l1.go = "Avendel_seapatrol_7";
		break;
		
		case "Avendel_seapatrol_7":
			dialog.text = "Ich habe dir gesagt, dass ich nichts gesehen habe. Ich bin durch die Küche geflohen, sobald ich Franz Garcke und seine Männer gesehen habe... Es war zu knapp! Es passierte gestern Abend und ich wusste nicht, wie ich dich informieren sollte...";
			link.l1 = "Ja, du bist ein sehr tapferer und einfallsreicher Mann... Gut, lass uns dir noch eine Chance geben, wir werden sie finden. Ich habe diesen Schurken schon zu lange geschützt und jetzt betrachte ich ihn als mein Eigentum. Wir haben noch etwas Zeit, um sie zu erwischen, also lasst uns in der Taverne anfangen, vielleicht hat jemand mehr gesehen als deine fliehenden Fersen. Geh, mach dich bereit!";
			link.l1.go = "Avendel_seapatrol_8";
		break;
		
		case "Avendel_seapatrol_8":
			DialogExit();
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetFunctionTimerCondition("MartiniquePortugalOver", 0, 0, 2, false); //таймер
			sld = characterFromId("PortugalDoctor");
			sld.lifeday = 0;//убираем доктора
			RemovePassenger(Pchar, sld);	
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "none", "", "");//Португальца спрячем
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", true);//комнату закроем
			AddQuestRecord("Portugal", "12");
		break;
		
		case "Avendel_seapatrol_9":
			dialog.text = "Haben Sie ihn gehört, Kapitän, er hat vom einäugigen Hund gesprochen, ich habe Ihnen kürzlich von ihm erzählt. Und der lispelnde Kastilier ist Hernando Vasquez, der blutige Don - der Schlächter von Vera Cruz, ich habe ihn nicht gesehen!";
			link.l1 = "Entspann dich, Hugo. Ich bin mir sicher, dass Bartholomeo noch auf der Insel ist, er könnte sich verbessert haben, aber er ist immer noch zu schwach. Und ich glaube, ich weiß, wo ich ihn finden kann! Wir werden sie bekommen, ich werde nicht von meiner Belohnung zurücktreten. Wenn du kein Feigling bist, dann folge mir, es ist noch nicht vorbei.";
			link.l1.go = "Avendel_seapatrol_10";
		break;
		
		case "Avendel_seapatrol_10":
			DialogExit();
			bDisableFastReload = false;//открыть быстрый переход
			pchar.questTemp.Portugal = "PortugalLeFransua";//в Ле Франсуа
			AddQuestRecord("Portugal", "13");
			LAi_LocationDisableOfficersGen("LeFransua_tavern", true);//офицеров не пускать
		break;
		
		case "LeFransua_pirate":
			dialog.text = "Sie stellen zu viele Fragen, Kapitän... Moment, sind Sie nicht dieser hinterhältige Kerl aus Philipsburg? Sie laufen uns schon zu lange davon und jetzt schauen Sie - hier sind Sie...";
			link.l1 = "Schade für dich, Abschaum!";
			link.l1.go = "LeFransua_pirate_1";
		break;
		
		case "LeFransua_pirate_1":
			DialogExit();
			pchar.quest.MartiniquePortugalOver.over = "yes"; //снять таймер
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("LeFransuaPirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransuaAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "FranzGarke":
			dialog.text = "... du, elendes Krabbenkacke, du wirst uns alles erzählen, darauf kannst du dich verlassen, du verfluchte Ratte! Dann wirst du an einem Mars statt an einer Topsegel aufgehängt... Und wer zum Teufel bist du? Verdammt, diesen Affen kann man nicht trauen! Muss immer alles selbst machen...";
			link.l1 = "Störe ich Sie, meine Herren?";
			link.l1.go = "FranzGarke_1";
		break;
		
		case "FranzGarke_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("FranzGarke");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransua_PortugalTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_LFTalk":
			dialog.text = "Ich mag dein Timing... Ich nehme an, ich muss dir dafür danken, dass du mich bis heute am Leben erhalten hast?";
			link.l1 = "Du hast recht. Mein Name ist "+GetFullName(pchar)+" und du, Portugiese, bist immer noch mein Gefangener. Also stell mir keine Fragen, wir müssen los.";
			link.l1.go = "Portugal_LFTalk_1";
		break;
		
		case "Portugal_LFTalk_1":
			dialog.text = "Warte, Kapitän... es gibt viele von Vasquez's Männern in der Stadt, sie werden uns nicht einfach so gehen lassen. Gib mir ein Schwert und wir haben viel bessere Chancen.";
			link.l1 = "Du stehst also nicht auf gutem Fuß mit deinen Partnern, hm? Gut, eine zusätzliche Klinge ist immer willkommen, nimm die Waffe des Toten und bleib mir nahe!";
			link.l1.go = "Portugal_LFTalk_2";
			link.l2 = "Denk nicht mal daran, dass ich dir eine Waffe gebe, damit du mich schlagen kannst, sobald ich dir den Rücken zukehre! Bleib einfach in meiner Nähe.";
			link.l2.go = "Portugal_LFTalk_4";
			pchar.quest.Portugal_LeFransua.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Portugal_LeFransua.function = "CreateVaskezsPirates";
			bDisableFastReload = true;//закрыть переход
		break;
		
		case "Portugal_LFTalk_2":
			dialog.text = "Mach dir keine Sorgen, Kapitän, ich würde lieber sterben, als wieder in Vasquez' Hände zu fallen.";
			link.l1 = "Nun, Tatsache ist, ich will dich noch nicht tot sehen. Los geht's, die Zeit läuft ab!";
			link.l1.go = "Portugal_LFTalk_3";
		break;
		
		case "Portugal_LFTalk_3":
			DialogExit();
			GiveItem2Character(npchar, "blade_17");
			EquipCharacterbyItem(npchar, "blade_17");
			GiveItem2Character(npchar, "pistol6");
			EquipCharacterbyItem(npchar, "pistol6");
			TakeNItems(npchar, "bullet", 50);
			AddItems(npchar, "gunpowder", 50);
			TakeNItems(npchar, "potion2", 3);
			LAi_SetCharacterUseBullet(npchar, GUN_ITEM_TYPE, "bullet");
			pchar.questTemp.Portugal.Condition1 = "true";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Portugal_LFTalk_4":
			dialog.text = "Schade, ich hätte dem Einauge geholfen, wenn ich dich tot gewollt hätte...";
			link.l1 = "Aber du hast mir auch nicht geholfen, also halt die Klappe und mach dich fort!";
			link.l1.go = "Portugal_LFTalk_5";
		break;
		
		case "Portugal_LFTalk_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Vaskezs_pirate":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Verdammt! Das sind sie! Tötet sie alle!";
			link.l1 = "Hier gehen wir wieder... Kommt dann ihr Tölpel!";
			link.l1.go = "Vaskezs_pirate_1";
		break;
		
		case "Vaskezs_pirate_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1"))
			{
				sld = characterFromId("Portugal");
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=9; i++)
			{
				sld = characterFromId("VaskezsPirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "VaskezsPiratesDied");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_LeFransua":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;//открыть переход
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Herrlich! Du hast den Einaugigen Hund getötet, das nenne ich ein Meisterwerk! Wie viele seiner Männer hast du in die Hölle geschickt?";
				link.l1 = "Ich habe gekämpft, nicht gezählt. Und wo warst du, Hugo?";
				link.l1.go = "Avendel_LeFransua_1";
			}
			else
			{
				dialog.text = "Wie schade, Kapitän. Wir haben verloren und wir werden dieses verdammte Gold nicht sehen. Lebewohl.";
				link.l1 = "Auf Wiedersehen, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				RemovePassenger(Pchar, npchar);
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_LeFransua_1":
			dialog.text = "Ich... sicherte den sicheren Rückzug... beschützte sozusagen unseren Rücken.";
			link.l1 = "Nun, das war's Hugo Avendell, deine Feigheit hat all meine Erwartungen übertroffen, hast du eine Ahnung, wie hart dieser Kampf für uns war? Wir haben es gerade noch geschafft!";
			link.l1.go = "Avendel_LeFransua_2";
		break;
		
		case "Avendel_LeFransua_2":
			dialog.text = "Beruhige dich, Kapitän... Ich gebe zu, ich habe mich versteckt. Aber ich habe diese Gelegenheit für dich gefunden! Erinnere dich, ich war es, der dich zu den Portugiesen geführt hat! Nun... in Anbetracht deiner fairen Empörung, stimme ich nur einem Drittel der Belohnung zu.";
			link.l1 = "Das ist einfach herrlich! Verhandelst du jetzt? Nein, mein Freund, dein Part in diesem Geschäft ist vorbei! Du hast dein Geld in der Taverne von Saint-Pierre verloren. Du hast es dort gelassen und bist weggerannt, also ist es jetzt vorbei für dich.";
			link.l1.go = "Avendel_LeFransua_3";
		break;
		
		case "Avendel_LeFransua_3":
			dialog.text = "Kapitän, Sie übertreiben eindeutig... Gut, ich stimme zu einem Viertel zu... zu einem Fünftel! Zehn Prozent!";
			link.l1 = "Fordere meine Geduld nicht heraus! Verschwinde! Ich brauche keine Feiglinge in meiner Mannschaft, besonders jetzt, wo die Uhr tickt!";
			link.l1.go = "Avendel_LeFransua_4";
		break;
		
		case "Avendel_LeFransua_4":
			dialog.text = ""+pchar.name+", findest du nicht, dass es ein bisschen ungerecht ist?";
			link.l1 = "Ursache und Wirkung, Hugo... Du hast deine Wahl getroffen, also leb wohl. Zieh eine Schlussfolgerung und stürz dich nicht in solche Abenteuer, das ist offensichtlich nichts für dich.";
			link.l1.go = "Avendel_LeFransua_5";
		break;
		
		case "Avendel_LeFransua_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_LeFransua";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.Portugal.GG2 = "true"; // Jason Дороже золота
		break;
		
		case "Portugal_LeFransua":
			dialog.text = "Den Ballast abwerfen, Kapitän? So wahr, ha... Vasquez ist immer noch frei und es gibt viele Männer und Kanonen auf der Albatros, ich wette meine feine Hose gegen ein altes Taschentuch, dass Hernando uns nicht entkommen lässt.";
			link.l1 = "Nun, es scheint, dass wir ihn selbst begrüßen müssen. Geh, Monsieur Portugiese, und versuch, dein Mund zu halten. Wir werden den Anker so schnell wie möglich lichten.";
			link.l1.go = "Portugal_LeFransua_1";
		break;
		
		case "Portugal_LeFransua_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Portugal_LeFransua1.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua1.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_LeFransua1.function = "CreateVaskezsFrigate";
		break;
		
		case "VaskezsHelper_abordage":
			dialog.text = "Worauf wartest du verdammt noch mal?!";
			link.l1 = "Wo ist Hernando Vasquez? Sprich und ich werde dein Leben verschonen.";
			link.l1.go = "VaskezsHelper_abordage_1";
		break;
		
		case "VaskezsHelper_abordage_1":
			dialog.text = "Geh zur Hölle mit deinen verdammten Fragen!";
			link.l1 = "Nach Ihnen...";
			link.l1.go = "VaskezsHelper_abordage_2";
		break;
		
		case "VaskezsHelper_abordage_2":
			DialogExit();
			QuestAboardCabinDialogExitWithBattle(""); 	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_treasure":
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1") && CheckAttribute(pchar, "questTemp.Portugal.Condition2"))
			{
				dialog.text = "Und da bist du ja, mein tapferer Freund, endlich können wir ein anständiges Gespräch führen! Gratulation, Kapitän - den einäugigen Hund zu töten und die 'Albatros' zu zerstören, war keine leichte Aufgabe! Tatsächlich hast du so viel getan, um mein Leben zu retten... Vielleicht sollte ich dir sogar danken?";
				link.l1 = "Du wirst mir danken, wenn du auf dem Galgen tanzt oder was auch immer sie für dich in Willemstad vorbereitet haben.";
				link.l1.go = "Portugal_treasure_6";
			}
			else
			{
				dialog.text = "Und da bist du ja, mein tapferer Freund, endlich können wir uns unterhalten! Glückwunsch, Kapitän - der Mord an dem Einaugigen Hund ist einer ehrenvollen Ballade würdig! Tatsächlich hast du so viel für meine Rettung getan... Vielleicht sollte ich dir sogar danken?";
				link.l1 = "Du wirst mir danken, wenn du auf dem Galgen tanzt oder was auch immer sie in Willemstad für dich vorbereitet haben.";
				link.l1.go = "Portugal_treasure_1";
			}
		break;
		
		case "Portugal_treasure_1":
			dialog.text = "Unglaublich! Du hast mein Leben in den letzten zwei Wochen gerettet, hast mich zu dir nach Hause gebracht und mich in Kämpfen beschützt... und jetzt willst du mich in den Tod schicken? Kaum zu glauben... Tatsächlich betrachte ich dich fast als meinen Freund, ha-ha.";
			link.l1 = "Ein Pirat, der um Ehre bittet? Portugiese, nimmst du mich auf den Arm? Ich habe dich nur aus einem Grund gerettet - um den Mörder und Schurken vor das Gericht der Gerechtigkeit zu bringen!";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Freund von mir... klingt wie ein Hohn. Aber dennoch hast du recht. Es wäre seltsam von mir, das zu tun, Portugiese...";
			link.l2.go = "Portugal_treasure_2_2";
		break;
		
		case "Portugal_treasure_2_1":
			dialog.text = "Oh, genug, Kapitän. Ich wette, Sie haben all das nur gemacht, um das Geld zu bekommen, das die Gesellschaft für das Vergnügen versprochen hat, mich lebend zu sehen! Versuchen Sie nicht, ehrlicher zu sein, als Sie es tatsächlich sind, Herr, es steht Ihnen nicht.";
			link.l1 = "Nur ich kann mich selbst beurteilen. Also beenden wir dieses Gespräch. Es ist Zeit, nach Willemstad zu segeln.";
			link.l1.go = "Portugal_treasure_3";
		break;
		
		case "Portugal_treasure_2_2":
			dialog.text = "Es scheint, dass heutzutage noch etwas Ehrlichkeit in den Menschen zu finden ist... Schade nur, dass Geld immer dazwischenfunkt - nicht wahr, Kapitän?";
			link.l1 = "Seltsam, das von dem Galgen-Vogel Pirat, dem Portugiesen, zu hören. Ich werde dich gehen lassen... frag mich nicht warum, hau einfach im ersten Hafen ab. Und denk dran, ich werde nicht so nett sein, wenn wir uns jemals wieder treffen.";
			link.l1.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.questTemp.Portugal.Villemstad = "true";//сдать губернатору
			AddQuestRecord("Portugal", "21");
		break;
		
		case "Portugal_treasure_4":
			dialog.text = "Wirklich? Das würde mir gefallen, Kapitän! Würden Sie nicht befehlen, etwas Rum hierher zu bringen? Sie wissen, nur um Ihre ritterlichen Qualitäten, unsere Beziehung und die Aufschiebung meines Urteils zu feiern?";
			link.l1 = "Lass die bösen Scherze sein, du bist noch bis zum ersten Ufer mein Gefangener. Leb wohl.";
			link.l1.go = "Portugal_treasure_5";
		break;
		
		case "Portugal_treasure_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.quest.Remove_Portugal.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Portugal.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Portugal.function = "RemovePortugal";
			AddQuestRecord("Portugal", "20");
		break;
		
		case "Portugal_treasure_6":
			dialog.text = "Ich sehe... also ist es der Galgen dann. Das war zu erwarten. Dann hör zu, was ich dir sagen werde, Kapitän. Du warst so darauf erpicht, mich am Leben zu halten, um mich später ordentlich hinrichten zu können und das schätze ich. Ich nehme an, es wäre dumm von mir, dich einfach so zu bitten, deine Meinung zu ändern, oder? Und was würdest du sagen, wenn ich dir etwas im Austausch anbiete? Ein Handel sozusagen, hm?";
			link.l1 = "Ich werde nichts sagen, Portugiese. Du bist ein Pirat und ein Bastard. Du wirst für deine Verbrechen in Willemstad bezahlen.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Ein Handel? Was kannst du anbieten?";
			link.l2.go = "Portugal_treasure_7";
			link.l3 = "Ich brauche deinen Deal nicht, verschwinde einfach im allerersten Hafen. Es ist dein Glückstag.";
			link.l3.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_7":
			dialog.text = "Weißt du, trotz der unangenehmen Gründe hinter meiner ständigen Rettung verdient es immer noch etwas Dankbarkeit. Und Bartolomeo der Portugiese weiß etwas über Dankbarkeit. Jetzt hör zu, einen Monat bevor du und ich uns trafen, haben wir ein Schiff der Gesellschaft erobert. Sie kämpften wie Teufel bis zum letzten Mann. Aber in ihren Laderäumen waren nur Kanonenkugeln und Ratten\nMeine Crew mochte es nicht, doch ich habe eine sehr interessante Truhe und Papiere in der Kapitänskabine gefunden. Sie war ein Kurierschiff, das Proben von Minen irgendwo in Amazonien lieferte. Reine Diamanten und Rubine, ein wahres Vermögen!";
			link.l1 = "Ein interessanter Preis... Jetzt verstehe ich, warum die Kompanie so an dir interessiert ist, aber was ist der Sinn deiner Geschichte?";
			link.l1.go = "Portugal_treasure_8";
		break;
		
		case "Portugal_treasure_8":
			dialog.text = "Meine ersten Offiziere Vazquez und Franz Garcke hatten die Mannschaft im Griff, also beschloss ich, mein Glück zu versuchen. Ich versteckte die Steine vor ihnen und verbrannte die Papiere. Die Holländer hatten unser Takelage während des Enterings schwer beschädigt und wir mussten die 'Albatros' in einer kleinen Bucht einer kleinen Insel im Norden unterbringen. Ich ging alleine tiefer in die Dschungel, während die ganze Mannschaft die Fregatte reparierte\nIch vergrub die Steine, sie an Bord zu behalten war zu riskant angesichts der Umstände. Mein Plan war, bei der ersten Gelegenheit von meiner geliebten Mannschaft zu fliehen, in einem Hafen ein kleines Boot zu kaufen oder zu stehlen und zur Insel zu segeln, meinen Preis zu holen und dann... Adieu zu meinem alten Leben! Europa, ein anständiges Herrenhaus, eine heiße Frau, ihr kennt den Rest...";
			link.l1 = "Lass mich raten, etwas ist schief gelaufen.";
			link.l1.go = "Portugal_treasure_9";
		break;
		
		case "Portugal_treasure_9":
			dialog.text = "Alles ging schief! Die verdammte Insel stellte sich als Heimat einer Horde von einheimischen Kannibalen heraus. Sie griffen uns an, sobald ich an die Küste zurückkehrte. Wir mussten so schnell wie möglich segeln, da wurde ich getroffen. Ich dachte, es sei nur ein Kratzer.\nEin paar Tage später lag ich halbtot im Fieber und sagte anscheinend etwas über die Steine. Franz und Vazquez merkten, dass ich etwas auf der Insel versteckt hatte, aber sie kannten den genauen Ort nicht. Ihnen gefiel die Idee nicht, dort herumzuwandern und ständig von den Indianern erschossen zu werden. Also schleiften die Bastarde mich zum nächsten Hafen, da unser Arzt während unseres Kampfes mit den Holländern getötet wurde, brauchten sie einen neuen.\nSo landete ich bei diesem Arzt, sie wollten mich für eine Zeit lang quälen und den Ort der Steine herausfinden. Ich glaube, später würden sie mich zerschneiden und die Krabben mit meinem saftigen Fleisch füttern.";
			link.l1 = "Ich kann nicht sagen, dass ich sie verurteile - du hast versucht, deine Männer zu hintergehen. Also frage ich noch einmal, warum erzählst du mir davon?";
			link.l1.go = "Portugal_treasure_10";
		break;
		
		case "Portugal_treasure_10":
			dialog.text = "Diese Hunde waren keine Menschen, glaub mir, sie sind jetzt alle an ihrem verdienten Ort - der Hölle, ha-ha! Als Bezahlung für meine Freiheit und mein Leben kann ich den genauen Standort der holländischen Schätze verraten.";
			link.l1 = "Nein, Bart, dein Verrat hat mich völlig von deiner Gemeinheit überzeugt. Willemstad und eine rechtmäßige Vergeltung warten auf dich. Kein Deal.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Und soll ich glauben, dass diese Edelsteine wirklich existieren? Was auch immer, ich werde sowieso nichts verlieren... Der Handel war der Anfang dieser Geschichte und der Handel wird ihr Ende sein. Ich akzeptiere Ihre Bedingungen, Portugiese.";
			link.l2.go = "Portugal_treasure_11";
		break;
		
		case "Portugal_treasure_11":
			dialog.text = "Betrachten Sie dies als meine bescheidene Dankbarkeit. Eh, ich wünschte, ich wüsste, wie viel die Haut von Bartolomeo dem Portugiesen in glänzenden Pesos kostet, ha! Ich weiß, dass Ihre Ziele rein praktischer Natur waren, aber trotzdem, danke, Kapitän, für alles, ha-ha\nEs sind die Türken, die Dschungel nicht weit von ihren Ufern. Suchen Sie einen trockenen, krummen Baum, es gibt nur einen solchen Baum dort. Ich habe die Truhe in der Nähe davon vergraben. Also vergessen Sie nicht, eine Schaufel mitzunehmen. Frohe Jagd...";
			link.l1 = "Gut, ich werde das berücksichtigen und du kannst jetzt sofort ein Beiboot nehmen und von meinem Schiff verschwinden. Lebewohl.";
			link.l1.go = "Portugal_treasure_12";
		break;
		
		case "Portugal_treasure_12":
			dialog.text = "Eine letzte Sache, Kapitän. Ich vermute, es gibt immer noch viele Wilden, aber sie sind nicht die Einzigen, um die du dich sorgen solltest. Vasquez war nicht auf der 'Albatros', oder? Der blutige Don ist zu schlau... pass auf deinen Rücken auf, bis du ihn gehängt siehst oder mit einer Kugel im Kopf.";
			link.l1 = "Danke für deine Warnung, Portugiese. Würdest du jetzt bitte mein Schiff verlassen... teste meine Geduld nicht.";
			link.l1.go = "Portugal_treasure_13";
		break;
		
		case "Portugal_treasure_13":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			AddQuestRecord("Portugal", "23");
			pchar.quest.Portugal_Terks.win_condition.l1 = "location";
			pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks_Jungle_01";
			pchar.quest.Portugal_Terks.function = "CreateHollIndBattle";
		break;
		
		case "Avendel_Marigo":
			pchar.quest.SetAvendelMarigoOver.over = "yes"; //снять таймер
			dialog.text = "Oh, und wer ist das! Kapitän "+pchar.name+" selbst! Lust auf einen Trunk?";
			link.l1 = "Du weißt, ich bin eigentlich froh, dich wieder zu sehen. Aber vielleicht war ich auf Martinique zu grob mit dir.";
			link.l1.go = "Avendel_Marigo_1";
		break;
		
		case "Avendel_Marigo_1":
			dialog.text = "Egal, Kapitän! Was passiert ist, ist passiert... Aber um ehrlich zu sein, habe ich dir wirklich einen Grund gegeben, mich wegzuschicken... Aber hey, du wirst nicht glauben, wer heute zu Gast in Phillipsburg ist!";
			link.l1 = "Sag mir nicht, dass es ist...";
			link.l1.go = "Avendel_Marigo_2";
		break;
		
		case "Avendel_Marigo_2":
			dialog.text = "Nein-nein, Kapitän, es sind nicht die Portugiesen. Und es ist auch nicht schon wieder irgendein verwundeter Bastard. Es ist viel besser! Es ist Hernando Vasquez... Der blutige Don selbst! Er ist seit einigen Tagen Gast des örtlichen Gouverneurs.";
			link.l1 = "Vasquez? Der Gast des Gouverneurs? Ich verstehe jetzt. Hugo, erzähl mir mehr darüber, was zum Teufel geht hier vor?";
			link.l1.go = "Avendel_Marigo_3";
		break;
		
		case "Avendel_Marigo_3":
			pchar.questTemp.Portugal.AvMoney = 10000;
			dialog.text = "Nun, ich weiß viel ... aber dank unserer Reise bin ich wieder bankrott. Vielleicht ist dein Bedarf an dieser Information ein paar Pesos wert?";
			link.l1 = "Hugo, du bist immer noch ein Erpresser und ein Schuft! Sag was du hast, nimm 5000 Pesos nur um unserer alten Freundschaft willen.";
			link.l1.go = "Avendel_Marigo_4_1";
			if (sti(pchar.money) >= 10000)
			{
			link.l2 = "Irgendwie bin ich nicht überrascht. Hier, nimm 10000 Pesos und du hoffst besser, dass deine Informationen so viel Geld kosten!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
			link.l3 = "Ich habe einen besseren Vorschlag für dich. Wie wäre es, wenn du meiner Besatzung beitrittst? Ich nehme an, dass du ein Talent dafür hast, profitable Geschäfte zu machen und zu finden, also, wenn du es leid bist, dich als tapferen Kämpfer auszugeben - du bist mehr als willkommen, die Position meines Zahlmeisters einzunehmen.";
			link.l3.go = "Avendel_Marigo_4_3";
		break;
		
		case "Avendel_Marigo_4_1":
			pchar.questTemp.Portugal.AvMoney = 15000;
			dialog.text = "Nein, Kapitän, so wird das nicht funktionieren! Du hast mit diesem verfluchten Portugiesen eine große Summe geschnappt, da bin ich sicher. Betrachte das also als meinen Anteil, sei nicht so gierig. 15000 Münzen und keinen einzigen Peso weniger!";
			if (sti(pchar.money) >= 15000)
			{
			link.l1 = "Ach verdammt mit dir, nimm sie!";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Nun, und sie sagen, dass Gier gut ist... Ist das nicht zu viel für dich, huh?";
			link.l2.go = "Avendel_Marigo_wait";
		break;
		
		case "Avendel_Marigo_4_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Portugal.AvMoney));
			dialog.text = "Jetzt ist das der Preis für mich! ... Hör zu, Vasquez segelte auf demselben Schiff mit mir, aber während ich das Deck als Bezahlung für die Reise schrubbte, ruhte er sich in einer Kabine aus, also dank Gott haben wir uns selten gesehen und er hat mich nicht erkannt. Aber ich habe angefangen, diesem Teufel sofort zu folgen... Eine interessante Geschichte ist mit ihm passiert.";
			link.l1 = "Mach weiter! Was macht er im Gouverneurspalast?";
			link.l1.go = "Avendel_Marigo_5";
		break;
		
		case "Avendel_Marigo_5":
			dialog.text = "Ich weiß nicht viel, aber die Garnison wurde einige Tage nach seiner Ankunft alarmiert und das riesige Kriegsschiff hatte plötzlich Anker gelichtet und war in großer Eile abgesegelt, ich glaube, es segelte Nordwest. Die ganze Stadt war in Vermutungen und Klatsch verloren...";
			link.l1 = "Also war das das Schiff, das ich getroffen habe! Faszinierend... Schweife nicht vom Thema ab, Hugo, bitte fahre mit deiner Geschichte fort.";
			link.l1.go = "Avendel_Marigo_6";
		break;
		
		case "Avendel_Marigo_6":
			dialog.text = "Nun, wie ich sagte, das Schiff war weg und Vasquez war irgendwie ein Gast unseres Gouverneurs Martin Thomas geworden. Ich sehe ihn manchmal in der Stadt, er ist immer in Begleitung einiger Soldaten. Ich weiß nicht, ob es seine Eskorte oder ein Konvoi ist, ha-ha. Aber nur die Leute in der Residenz könnten Ihnen mehr über den Don erzählen.";
			if (CheckAttribute(pchar, "questTemp.Portugal.AvOfficer"))
			{
				link.l1 = "Vielleicht hast du recht. Aber wir hatten eine Abmachung, erinnerst du dich? Spiel nicht den Helden, geh zu meinem Schiff und warte auf meine Rückkehr. Ich werde versuchen, mit unserem gastfreundlichen Gouverneur zu sprechen.";
				link.l1.go = "Avendel_hire";
			}
			else
			{
				link.l1 = "Nun, das war interessant. Du hast mir wirklich geholfen, Hugo. Trink deinen Rum, der Rest geht dich nichts an.";
				link.l1.go = "Avendel_Marigo_del";
			}
			AddDialogExitQuestFunction("InMarigoResidence");
		break;
		
		case "Avendel_Marigo_4_3":
			dialog.text = "Sind Sie ernst, Kapitän? Was stimmt nicht mit Ihnen? Sie haben mich vertrieben, indem Sie mir eine Pistole ins Gesicht gehalten haben und kommen jetzt mit solchen Vorschlägen?";
			if (sti(pchar.money) >= 10000)
			{
			link.l1 = "Vergiss das, ich war nicht ich selbst und es tut mir leid, ich schätze, die Gier hat mich verzehrt. Hier, nimm 10000 Pesos und sag mir, was du über Vasquez weißt, ich habe es eilig.";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Vielleicht sollte ich mich für diese Angelegenheit entschuldigen. Du bist ein erbärmlicher Kämpfer, aber mit Münzen kommst du gut zurecht. Ich wiederhole meinen Vorschlag, was sagst du dazu?";
			link.l2.go = "Avendel_Marigo_7";
		break;
		
		case "Avendel_Marigo_7":
			pchar.questTemp.Portugal.AvMoney = 20000;
			pchar.questTemp.Portugal.AvOfficer = "true";
			dialog.text = "Was soll ich sagen... Ich werde zustimmen, aber nur nachdem ich meinen Anteil bekomme, Kapitän. Zehn Prozent, erinnerst du dich? Du hast zwei Tausend für diesen Schurken bekommen, also wenn du mich bittest, deiner Crew beizutreten, solltest du besser damit anfangen, deine Schulden zu begleichen. Zehn Prozent und kein Streit!";
			link.l1 = "Du bist so ein Schwindler, Hugo. Ich habe jetzt nicht so viel bei mir, aber ich komme bald wieder. Bleib hier.";
			link.l1.go = "Avendel_Marigo_wait";
			if (sti(pchar.money) >= 20000)
			{
			link.l2 = "Ich hoffe, dass Sie mit Ihrem Geschäftssinn meine Erwartungen erfüllen werden, ha! Nehmen Sie Ihren Anteil!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
		break;
		
		case "Avendel_Marigo_wait":
			dialog.text = "Es ist Ihre Entscheidung, Kapitän. Ich bleibe hier für eine Weile. Kommen Sie zurück, wenn Sie Ihre Meinung ändern.";
			link.l1 = "Gut, Hugo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_repeat":
			dialog.text = "Haben Sie Ihre Meinung geändert, Kapitän? Ich warte dann auf mein Geld.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Portugal.AvMoney))
			{
				link.l1 = "Nimm deine Münzen, du Schurke ha-ha!";
				link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Ich habe noch nicht so viel Geld.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_del":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Avendel_hire":
			DialogExit();
			LAi_SetImmortal(npchar, false); // patch-8
			SetCharacterRemovable(npchar, true);
			npchar.quest.OfficerPrice = sti(pchar.rank)*1000;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "Servant":
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			dialog.text = "Guten Tag, Kapitän. Wünschen Sie etwas?";
			link.l1 = "Nein-nein, ich warte nur, wann wird mein Herr Thomas frei sein? Ich warte auf eine Audienz... ja. Sag mal, betrachtet seine Exzellenz wirklich den berühmten Piraten Hernando Vasquez als seinen Freund?";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Machen Sie sich keine Sorgen, mein Herr, er sollte jeden Moment frei sein, und natürlich nicht, mein Herr! Dieser Bandit hat sich den Behörden ergeben, wurde aber irgendwie nicht gehängt. Vielleicht hat er sein Leben durch Verrat an seinen alten Verbrecherpartnern gekauft... Ich bin mir nicht sicher. Er wurde hier mehrere Tage lang eingesperrt... Das war ein Alptraum, mein Herr! Dieses Biest in menschlicher Form lebte in unserem Herrenhaus!";
			link.l1 = "Ein Alptraum ist es! Was könnte dieses Biest zu meinem Herrn Thomas sagen, um dem Galgen zu entkommen? Ich kann es mir nicht einmal vorstellen!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			dialog.text = "Ich weiß es auch nicht, aber ich kann Ihnen heimlich sagen, dass alle Diener froh waren, als Seine Exzellenz solch einen Gast losgeworden ist...";
			link.l1 = "Hast du ihn losgeworden? Hat er endlich bekommen, was er verdient hat?";
			link.l1.go = "Servant_3";
		break;
		
		case "Servant_3":
			dialog.text = "Noch nicht ganz. Doch. Vor einigen Tagen wurde er in eine Militärbrigade gebracht, die nach Willemstad segelte. Siehst du, mein Herr Thomas hatte das Interesse an dem Schurken verloren, es scheint, dass er versucht hat, ihn zu täuschen\nAußerdem sagen sie, dass sein ehemaliger Kapitän gefangen wurde - Bartolomeo der Portugiese! Stell dir das vor! Es sieht so aus, als ob die Kompanie sie zusammen hängen will. Die Vögel sagen, dass der Prozess in einem Monat sein wird, aber warum so lange warten?";
			link.l1 = "Die Portugiesen?! Hm... danke, dass du mir Gesellschaft geleistet hast, Freund... es scheint, dass mein Herr Thomas jetzt frei ist, ich werde mich verabschieden.";
			link.l1.go = "Servant_4";
		break;
		
		case "Servant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Portugal", "31");
			pchar.questTemp.Portugal = "SeekPortVillemstad";
			//SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 30, false);
			colonies[FindColony("Villemstad")].jail = 0;
			sld = characterFromId("Portugal");
			sld.model = "Port_A"; //меняем модель
			sld.dialog.currentnode = "Portugal_free";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
			sld = GetCharacter(NPC_GenerateCharacter("PortHolOfficer", "off_hol_4", "man", "man", 35, HOLLAND, 30, true, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_19", "pistol3", "grapeshot", 100);
		
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto23");
			LAi_LocationDisableOfficersGen("Villemstad_prison", true);//офицеров не пускать
		break;
		
		case "Vaskez":
			dialog.text = "Jetzt seid ihr tot... beide!";
			link.l1 = "...";
			link.l1.go = "Vaskez_1";
		break;
		
		case "Vaskez_1":
			DialogExit();
			LAi_ActorAnimation(npchar, "shot", "VaskezFight", 2.0);
		break;
		
		case "Portugal_free":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "Nun, das ist jemand, den ich nicht erwartet hatte zu sehen, Kapitän! Aber es sieht nicht nach einem freundlichen Besuch aus, all dieses Blut, Lärm und eine Schießerei, oder ist es eine Art Feier mit Feuerwerk, hm?";
				link.l1 = "Hör auf, deine verdammten Witze zu reißen, Portugiese. Mir gefällt einfach nicht, wie du deine Freiheit genutzt hast, die du von mir gekauft hast. Ich habe zu viel Mühe darauf verwendet, deinen erbärmlichen Hintern zu retten, um dich so dumm fangen zu lassen gleich nach unserer Trennung!";
				link.l1.go = "Portugal_free_1";
				// belamour legendary edition -->
				link.l2 = "Nun, ich war gelangweilt! Also kam ich hierher, um dich zu besuchen. Fühlst du dich hier wohl, Freund!";
				link.l2.go = "Portugal_free_1a";
				// <-- legendary edition
			}
			else
			{
				dialog.text = "Sei vorsichtig, Freund! Eh, zu schade, dass ich dir nicht helfen kann!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Portugal_free";
			}
		break;
		// belamour legendary edition -->
		case "Portugal_free_1a":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Also wird der Adel manchmal nicht von Münzen beeinflusst, hm? Hah... ACHTUNG, GLEICH HINTER DIR!";
			link.l1 = "Ach, nicht schon wieder dieser Scheiß!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		// <-- legendary edition
			dialog.text = "So ist Adel also manchmal nicht von Münzen beeinflusst, was? Hah... PASS AUF, DIREKT HINTER DIR!";
			link.l1 = "Ach, nicht schon wieder dieser Mist!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_2":
			dialog.text = "Und ich habe dich gewarnt, dass dieser Kerl Ärger bedeutet!";
			link.l1 = "Er hätte mich beinahe hinterrücks erschossen! Wie ist er durchgekommen?";
			link.l1.go = "Portugal_free_3";
		break;
		
		case "Portugal_free_3":
			dialog.text = "Ich habe gesehen, dass er einen Dietrich hatte, es scheint, dass ihm jemand diesen gegeben hat... er hatte immer Verbindungen in den unteren Schichten. Nun, Kapitän, ich glaube, wir sollten diesen Ort verlassen, finden Sie nicht?";
			link.l1 = "Das sagst du nicht! Gut, lass uns beeilen, bevor die ganze Garnison hier eingetroffen ist. Ich werde dein Schloss in einer Sekunde knacken...";
			link.l1.go = "Portugal_free_4";
		break;
		
		case "Portugal_free_4":
			DialogExit();
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Villemstad_Exittown", "rld", "loc17", "PortugalFree");
		break;
		
		case "Portugal_free_5":
			dialog.text = "Sie wissen, Kapitän, diese frische Luft... man beginnt sie erst zu schätzen, nachdem man ein paar Wochen in einem Verlies verbracht hat, gleich nachdem das Boot Ihres Schiffes von der örtlichen Patrouille gefunden wurde. Ich nehme an, dass ich Ihnen immer noch für meine Rettung schulde.";
			link.l1 = "Keine Notwendigkeit, Portugiese. Ich bin kein ehrenhafter Ritter, ich ... ich tue, was ich für richtig halte und was getan werden muss.";
			link.l1.go = "Portugal_free_6";
		break;
		
		case "Portugal_free_6":
			dialog.text = "Ha, und das ist eine hervorragende Qualität! Aber ich bestehe darauf, hier, nimm es... das ist das einzige, was ich im Gefängnis verstecken konnte... Ja, du hast es richtig verstanden. Das ist mein Talisman. Er hat mir immer Glück auf See gebracht. Du bist ein guter Seemann und du oder dein Navigator werdet ihn sicherlich nutzen können, da bin ich mir sicher.";
			link.l1 = "Ja, und du hattest das Glück, mit diesem Talisman direkt in die Hände der Holländer zu geraten.";
			link.l1.go = "Portugal_free_7";
		break;
		
		case "Portugal_free_7":
			dialog.text = "He! Ich lebe noch, oder? Und nur damit du es weißt, ich bin nicht mehr im Gefängnis. Nimm es, Kapitän, es ist Zeit, dass der Talisman dir dient. Und ich danke dir noch einmal!";
			link.l1 = "Auf Wiedersehen dann, Portugiese. Und bitte, versuche dich von dem Galgen fernzuhalten! Nur um meiner harten Arbeit willen, ha-ha!";
			link.l1.go = "Portugal_free_8";
		break;
		
		case "Portugal_free_8":
			TakeNItems(pchar, "talisman2", 1);
			Log_Info("You have received the talisman");
			PlaySound("interface\important_item.wav");
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("Villemstad_prison", false);//офицеров пускать
			AddQuestRecord("Portugal", "34");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
			pchar.questTemp.Portugal.GG1 = "true"; // Jason Дороже золота
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
