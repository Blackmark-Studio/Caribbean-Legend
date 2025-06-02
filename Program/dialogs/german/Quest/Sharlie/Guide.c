// гид
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Brauchst du etwas?";
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guide_0":
			SetAchievement("Test_Ach");
			PlaySound("Voice\English\LE\Greguar\Greguar_01.wav");
			dialog.text = "Freut mich, Sie in den Kolonien willkommen zu heißen, mein Herr! Gestatten Sie mir, mich vorzustellen: "+GetFullName(pchar)+". Kommen Sie aus dem guten alten Europa? Sind Sie zum ersten Mal bei uns?";
			link.l1 = "Guten Tag, Monsieur. Mein Name ist "+GetFullName(pchar)+". Ja, ich bin gerade erst vom Schiff gestiegen.";
			link.l1.go = "guide_1";
		break;
		
		case "guide_1":
			DelLandQuestMark(npchar);
			dialog.text = "Als ich einen Edelmann erblickte, hielt ich es für meine Pflicht, Hilfe anzubieten. Hier in der Neuen Welt gibt es eigene Regeln — und sie nicht zu kennen kann teuer werden. Vornehme Leute wie wir sollten einander helfen. Sie würden nicht glauben, wieviel Gesindel sich hier versammelt hat, bereit den Nächsten für eine Handvoll Münzen zu verraten\n"+
			"Darf ich Sie durch die Stadt führen und Sie kurz einweisen?";
			link.l1 = "Das ist sehr edel von Ihnen, Monsieur! Ich nehme Ihr Angebot gerne an.";
			link.l1.go = "guide_2";
			link.l2 = "Danke für die Fürsorge, mein Herr, ich bin Ihnen wirklich dankbar, aber ich denke, ich werde ohne Mühe alles selbst herausfinden.";
			link.l2.go = "guide_exit";
		break;
		
		case "guide_exit":
			dialog.text = "Wie Sie wünschen, Monsieur. Jedenfalls war ich erfreut über unsere Bekanntschaft. Edle Menschen sind so selten in dieser Wildnis. Alles Gute und viel Glück!";
			link.l1 = "Und Ihnen ebenfalls, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_2":
			dialog.text = "Ausgezeichnet! Das Leben in der Karibik ist unkompliziert, und jede Siedlung ist nach denselben Regeln aufgebaut. Wenn Sie sich in Saint-Pierre zurechtfinden — finden Sie sich auch in jeder anderen Stadt zurecht.";
			link.l1 = "";
			link.l1.go = "guide_tavern";			
		break;
		
		case "guide_tavern":
			dialog.text = "Taverne — das Herz des Hafens. Hier finden Sie Unterkunft, Rum, Gerüchte und können Matrosen und Offiziere anheuern. Außerdem — Karten spielen, Arbeit finden oder die Dienste von Schmugglern und Schatzkartenhändlern nutzen.";
			link.l1 = "";
			link.l1.go = "guide_market";
			locCameraFromToPos(-2.08, 5.32, 68.88, true, -15.00, 0.90, 55.00);
		break;
		
		case "guide_market":
			dialog.text = "Markt. Waren für den persönlichen Gebrauch kann man immer auf dem Markt kaufen. Beim Waffenschmied — Waffen, Rüstungen und Munition, bei der Kräuterfrau — Heiltränke. Zigeunerinnen und Mönche handeln mit Amuletten, und der Trödler verkauft allerlei Plunder, nützlich für die, die nicht davor zurückschrecken, selbst zu basteln.";
			link.l1 = "";
			link.l1.go = "guide_brothel";
			locCameraFromToPos(-13.58, 4.11, 69.06, true, -45.00, -6.00, 52.00);
		break;
		
		case "guide_brothel":
			dialog.text = "Bordell. Es gibt keine bessere Medizin für den Körper als Liebesfreuden in den Armen einer geschickten Frau. Wenn die Gesundheit angeschlagen ist — schauen Sie hier vorbei, zerstreuen Sie sich, bekommen Sie eine Portion Zärtlichkeit und fühlen Sie sich wie ein neuer Mensch.";
			link.l1 = "";
			link.l1.go = "guide_bank";
			locCameraFromToPos(-2.75, 7.07, 61.10, true, 60.00, -6.60, 42.65);
		break;
		
		case "guide_bank":
			dialog.text = "Bank. Haus des Wucherers. Man kann Geld leihen oder anlegen, Pesos in Dublonen tauschen. Und außerdem — ist es der beste Ort, um Edelsteine zu verkaufen.";
			link.l1 = "";
			link.l1.go = "guide_prison";
			locCameraFromToPos(3.07, 7.64, 51.99, true, 45.00, -8.30, 4.50);
		break;
		
		case "guide_prison":
			dialog.text = "Gefängnis. Echte Verbrecher gibt es hier wenige — hauptsächlich allerlei Gesindel. Wenn Sie Arbeit unter dem Abschaum der Gesellschaft finden wollen — sprechen Sie mit dem Kommandanten. Für eine kleine Bestechung lässt er Sie zu den Zellen.";
			link.l1 = "";
			link.l1.go = "guide_townhall";
			locCameraFromToPos(-50.52, 5.79, 38.60, true, -47.65, 3.95, 33.52);
		break;
		
		case "guide_townhall":
			dialog.text = "Palast. Der Palast der wichtigsten Person in der Kolonie — des Gouverneurs. Geschäftsleute und Kapitäne kommen hierher für ernsthafte Arbeit. In guten Beziehungen zum Gouverneur zu stehen — ist eine große Sache, denn von ihm hängt vieles ab, wie sich seine ganze Nation zu Ihnen verhalten wird.";
			link.l1 = "";
			link.l1.go = "guide_12";
			locCameraFromToPos(3.14, 7.39, 37.55, true, 1.06, 8.45, 14.14);
		break;
		
		case "guide_12":
			dialog.text = "Sie haben es irgendwohin eilig, und ich halte Sie auf?";
			link.l1 = "Nun... wahrscheinlich so. Monsieur, ich bin hierher gekommen, um meinen Bruder zu finden. Man sagt, er sei irgendwo in Saint-Pierre. Er ist eine wichtige Persönlichkeit und dem Gouverneur sicherlich bekannt...";
			link.l1.go = "guide_13";
			SetCameraDialogMode(npchar);
		break;
		
		case "guide_13":
			dialog.text = "Ah, ich verstehe. Unser Gouverneur heißt Jacques Dyel du Parquet. Ich bin sicher, er wird Sie ohne Verzögerung empfangen.";
			link.l1 = "Wen könnte ich noch nach meinem Bruder fragen? Vielleicht sollte ich Seine Exzellenz nicht sofort belästigen?";
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = "Wenn Ihr Bruder auf Martinique tatsächlich bekannt ist — fragen Sie die Passanten. Vielleicht kann jemand helfen. Übrigens, wie heißt er?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = "Dieser Name ist mir begegnet, aber leider hatte ich nicht die Ehre, persönlich vorgestellt zu werden. Versuchen Sie, in der Stadt zu fragen — oder gehen Sie direkt zum Gouverneur. Viel Glück, Monsieur. Wir werden uns bestimmt wiedersehen und plaudern!";
			link.l1 = "Danke, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_21":
			dialog.text = "Oh, Sie sind es wieder, mein Freund! Ich sehe, Sie wurden im Allerheiligsten von Saint-Pierre zugelassen — in der Hochburg der Malteserritter. Man sieht gleich — Sie sind ein hochrangiger Vogel. Haben Sie Ihren Bruder gefunden?";
			link.l1 = "Tja, gefunden...";
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = "Verzeihen Sie meine Aufdringlichkeit, Monsieur, aber mir scheint, ich höre keine Freude in Ihrer Stimme...";
			link.l1 = "Das stimmt, mein Herr. Ich hatte gehofft, von hier zurück nach Frankreich mit dem nächsten Schiff zu verschwinden, aber das Schicksal scheint sich über mich lustig zu machen: Ich bleibe hier für lange Zeit... nein, verdammt — für unbestimmte Zeit! Und, stellen Sie sich vor, obendrein muss ich Seemann werden, pah!";
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = "Irgendwie bin ich nicht überrascht. Ich habe bereits von Ihrem Abenteuer auf der Pinasse 'Ulysse' gehört. Lassen Sie den Kopf nicht hängen — Eigentümer eines eigenen Schiffes und Kapitän zu sein ist sehr ehrenvoll. Sie haben vor, ein Schiff zu kaufen, nicht wahr?";
			link.l1 = "Ja, verdammt, genau das muss ich tun... Ich muss nur noch eine Werft finden und irgendwie Geld sammeln. Aber ich weiß weder, wo die Werft ist, noch wie man ein Schiff steuert, noch woher ich Geld nehmen soll — nichts!";
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = "Mit Geld kann ich leider nicht helfen — ich bin selbst gerade knapp bei Kasse. Aber in allen anderen Fragen — stehe ich Ihnen zu Diensten. Sind Sie bereit, die Tour fortzusetzen?";
			link.l1 = "Ja, vermutlich, denn nicht umsonst sagt man: Wissen ist Macht.";
			link.l1.go = "guide_25";
			link.l2 = "Danke von ganzem Herzen, Monsieur, aber ich werde allein zurechtkommen.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_exit_11":
			dialog.text = "Es war mir eine Freude, Sie kennenzulernen. Und wegen des Geldes für das Schiff – sprechen Sie mit den einflussreichen Leuten der Stadt, zum Beispiel mit dem Kaufmann im Laden.\n"+
			"Viel Glück, "+pchar.name+" — seien Sie mutig, und alles wird Ihnen gelingen.";
			link.l1 = "";
			link.l1.go = "guide_exit_12";			
		break;
		
		case "guide_exit_12":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_25":
			dialog.text = "Dann folgen Sie mir! Beginnen wir mit dem Grundlegendsten — mit den Schiffen.";
			link.l1 = "";
			link.l1.go = "guide_shipyard";
		break;
		
		case "guide_shipyard":
			dialog.text = "Werft. Hier kauft und repariert man Schiffe. Die Auswahl ist nicht groß — hauptsächlich Kleinigkeiten, aber manchmal gibt es ernsthafte Schiffe. Hier kann man auch Kanonen kaufen und Segel verzieren.";
			link.l1 = "";
			link.l1.go = "guide_port";
			locCameraFromToPos(-23.25, 7.74, 77.79, true, -27.85, 5.36, 73.65);
		break;
		
		case "guide_port":
			dialog.text = "Pier — das Tor zum Meer. Sobald Sie ein Schiff haben — wird hier ein Beiboot auf Sie warten. Bis dahin empfehle ich, einen Steuermann, einen Zahlmeister und einen Kanonier anzuheuern — mit ihnen werden Sie sich auf See sicherer fühlen.";
			link.l1 = "";
			link.l1.go = "guide_portoffice";
			locCameraFromToPos(-8.55, 4.06, 91.31, true, 40.00, -8.00, 0.00);
		break;
		
		case "guide_portoffice":
			dialog.text = "Hafenamt. Hier können Sie Ihr Schiff parken oder ehrliche Arbeit für Kapitäne finden: Fracht, Eskorte, Postzustellung. Je больше Aufträge Sie erledigen, desto besser die Belohnung.";
			link.l1 = "";
			link.l1.go = "guide_store";
			locCameraFromToPos(48.38, 9.48, 43.95, true, 43.69, 5.47, 48.13);
		break;
		
		case "guide_store":
			dialog.text = "Laden. Kapitäne kommen meist hierher: für Proviant, Rum, Medizin, Pulver und Munition. Fehlt etwas, suchen Sie Schmuggler in der Taverne. Aber ohne guten Zahlmeister ist Handel reine Zeit- und Geldverschwendung.";
			link.l1 = "";
			link.l1.go = "guide_gate";
			locCameraFromToPos(-21.10, 6.60, 45.21, true, -30.00, 3.70, 45.00);
		break;
		
		case "guide_gate":
			dialog.text = "Stadttor. Wenn der Pier das Tor zum Meer ist, dann ist dies das Tor ins wilde Land. Gefährlich, aber nötig, wenn Sie zur Festung, auf Schatzsuche oder zu Fuß in eine andere Siedlung wollen.";
			link.l1 = "";
			link.l1.go = "guide_45";
			locCameraFromToPos(50.58, 5.74, 23.21, true, 100.00, 0.00, 20.00);
			//AddQuestRecordInfo("Guide_OnLand", "1");
		break;
		
		case "guide_45":
			dialog.text = "Nicht jede Kolonie heißt Fremde willkommen. Wenn Sie nicht bis zur Nacht warten wollen, hissen Sie auf See eine andere Flagge und setzen Sie auf Heimlichkeit – oder kaufen Sie eine Handelslizenz.";
			link.l1 = "";
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = "Sie hören gut zu, mein Freund. Wie wäre es mit etwas Spaß? Ein Übungskampf hinter dem Tor.";
			link.l1 = "Natürlich! Das kommt wie gerufen.";
			link.l1.go = "guide_47";
			link.l2 = "Danke von ganzem Herzen, Monsieur, aber ab hier komme ich allein zurecht.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_47": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = "Mein Freund, ich nehme an, Sie sind kein Neuling im Fechten?";
			link.l1 = "Ha! Einen Entern habe ich schon hinter mir und sogar...";
			link.l1.go = "guide_50";
			if (FindCharacterItemByGroupWithout_knife_03(pchar, BLADE_ITEM_TYPE) == "")
			{
				GiveItem2Character(pchar, "blade_05");
				EquipCharacterByItem(Pchar, "blade_05");
			}
		break;
		
		case "guide_50":
			dialog.text = "Ausgezeichnet. Fangen wir an?";
			link.l1 = "Tanzen wir!";
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetPlayerType(pchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			if (MOD_SKILL_ENEMY_RATE <= 6)	// На первых трёх сложностях Валинье будет ослаблен
			{
				LAi_SetHP(npchar, LAi_GetCharacterMaxHP(npchar) * 0.7, LAi_GetCharacterMaxHP(npchar) * 0.7);
				npchar.rank = 1;
				SetSelfSkill(npchar, 1, 1, 1, 1, 1);
			}
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			//DoQuestCheckDelay("GuideFight_tutorial", 1.0);
		break;
		
		case "guide_57": // побил гида с первого раза
			dialog.text = "Du... du bist ein Mann, der weiß, wie man sein Schwert hält. Gut gemacht, Monsieur. Du benötigst mehr Übung, aber du hast das Potential, ein wahrer Schwertmeister zu werden.";
			link.l1 = "Vielen Dank. Was jetzt?";
			link.l1.go = "guide_62"; // нода на выход
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				link.l2 = "Mehr Übung sagst du? Bist du ernst? Ich bin dieses herablassende Ton seit ich Fuß in diesen elenden Ort gesetzt habe, leid!";				//Пасхалка Корсары 2 для сложности СФ и выше
				link.l2.go = "guide_64";
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;
		
		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = "Viel besser! Siehst du, du musst dich nur konzentrieren. Du brauchst mehr Übung, eines Tages wirst du ein anständiger Fechter werden.";
			link.l1 = "Vielen Dank. Was jetzt?";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;
		
		case "guide_59": // побили первый раз
			dialog.text = "Ich habe gewonnen, Monsieur. Beweg dich schneller, pariere meine Stiche, spring zurück. Eine Revanche?";
			link.l1 = "Ja! Keine Gnade, Monsieur!";
			link.l1.go = "guide_56";
			link.l2 = "Nein, ich habe genug. Lass uns die Lektion beenden. Was jetzt?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_60": // побили второй раз
			dialog.text = "Ich habe wieder gewonnen, "+pchar.name+"! Verliere nicht deine Initiative. Fang meine Schläge ab, täusche sie vor. Wenn du siehst, dass ich hart zuschlage - spring weg oder pariere, verteidige dich nicht nur. Wieder!";
			link.l1 = "Komm, Monsieur, diesmal werde ich dich verprügeln!";
			link.l1.go = "guide_56";
			link.l2 = "Nein, ich habe genug. Lassen wir die Lektion beenden. Was jetzt?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_61": // побили третий раз
			dialog.text = "Du hast viel zu lernen, "+pchar.name+". Mach dir keine Sorgen, du hast noch viel Zeit, um dein Fechten zu meistern. Aber sei vorsichtig, nimm keine Risiken auf dich, bis du weißt, wie man eine Waffe hält.";
			link.l1 = "Ich werde es in Betracht ziehen, Monsieur, aber ich muss sagen, dass Sie einfach zu viel Glück hatten! Diese verdammte Hitze... der einzige Grund, warum ich Sie nicht verprügelt habe. Merde, lass uns unsere Fechtstunde beenden. Was jetzt?";
			link.l1.go = "guide_62"; // нода на выход
		break;
		
		case "guide_62":
			dialog.text = "Nun ist es Zeit, Lebewohl zu sagen, Monsieur. Es war mir ein Vergnügen. Ich hoffe, dass meine Präsentation und Ausbildung Ihnen etwas Gutes getan haben und sich in der Zukunft als nützlich erweisen werden. Vielleicht treffen wir uns eines Tages wieder.\nUnd was das Geld betrifft, das Sie brauchen - sprechen Sie mit den wichtigen Leuten unserer Stadt. Besuchen Sie alle Orte, die ich Ihnen heute gezeigt habe und sprechen Sie mit ihren Besitzern. Fragen Sie herum. Machen Sie einen Spaziergang zum Dschungel und zum Fort. Finden Sie einen Job oder... nun, ich bin kein Priester oder Richter, schauen Sie in die Häuser der Leute und sehen Sie, welche Kostbarkeiten Sie in ihren unverschlossenen Kisten finden können. Machen Sie es nur, wenn sie nicht hinschauen oder die Wachen werden Sie erwischen.\nViel Glück, "+pchar.name+", Ich habe das starke Gefühl, dass in dir der Funke wahrer Größe steckt. Gib dein Bestes, um ihn zu einem lodernden Feuer zu entfachen!";
			link.l1 = "Danke, Monsieur. Das Vergnügen war meinerseits. Gott mit dir!";
			link.l1.go = "guide_63";
		break;
		
		case "guide_63":
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;
		
		case "guide_64": // решили убить Валинье
			dialog.text = "Halten Sie Ihr Maul, Monsieur! Ich werde solche Unverschämtheit nicht weiter dulden. Allerdings verstehe ich Ihre Reaktion auf eine neue Umgebung, daher vergebe ich Ihren Ausbruch dieses Mal. Aber achten Sie von nun an auf Ihre Worte. Auf Wiedersehen, Monsieur de Maure.";
			link.l1 = "Keine Beleidigung, Monsieur Valinnie. Wären wir in diesem Moment im Louvre, würden Sie Ihren Ton mäßigen! Es ist Zeit, einer Provinz eine endgültige Lektion zu erteilen. Verteidige dich!";
			link.l1.go = "guide_65";
		break;
		
		case "guide_65":
			DialogExit();
			
			npchar.rank = 25;
			int iHp = MOD_SKILL_ENEMY_RATE*10+300;
			LAi_SetHP(npchar, iHp, iHp);
			SetSelfSkill(npchar, 80, 80, 80, 80, 50);
			SetShipSkill(npchar, 50, 80, 35, 30, 50, 20, 30, 20, 80);
			SetSPECIAL(npchar, 9, 5, 8, 6, 5, 10, 8);
			SetCharacterPerk(npchar, "Energaiser");
			SetCharacterPerk(npchar, "BasicDefense");
			SetCharacterPerk(npchar, "AdvancedDefense");
			SetCharacterPerk(npchar, "CriticalHit");
			SetCharacterPerk(npchar, "Tireless");
			SetCharacterPerk(npchar, "HardHitter");
			SetCharacterPerk(npchar, "Sliding");
			SetCharacterPerk(npchar, "BladeDancer");
			SetCharacterPerk(npchar, "SwordplayProfessional");
			SetCharacterPerk(npchar, "Gunman");
			SetCharacterPerk(npchar, "GunProfessional");
			GiveItem2Character(npchar, "blade_30");
			EquipCharacterbyItem(npchar, "blade_30");
			GiveItem2Character(npchar, "cirass7");
			GiveItem2Character(npchar, "obereg_7");
			GiveItem2Character(npchar, "talisman11");
			AddMoneyToCharacter(npchar, 10000);
			AddItems(npchar, "gold_dublon", 25);
			AddItems(npchar, "bullet", 5);
			AddItems(npchar, "grapeshot", 5);
			AddItems(npchar, "GunPowder", 10);
			TakeItemFromCharacter(npchar, "blade_12");
			npchar.cirassId = Items_FindItemIdx("cirass4");
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Guide_HeroKill");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string FindCharacterItemByGroupWithout_knife_03(ref chref, string groupID)
{
	ref refItm;
    string resultItemId;

	resultItemId  = "";
	for(i=TOTAL_ITEMS-1; i>=0; i--)
	{
		refItm = &Items[i];
		if( !CheckAttribute(refItm,"groupID") ) continue;
		if(refItm.groupID!=groupID) continue;
		if( !CheckAttribute(chref,"items."+refItm.id) ) continue;
		if(refItm.id == "knife_03") continue;
		if (groupID == BLADE_ITEM_TYPE)
		{
			resultItemId  = refItm.id;
		}
	}
	
	if (resultItemId != "")
	{
        return resultItemId;
	}

	return "";
}