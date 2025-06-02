// диалог прочих НПС по квесту Саги
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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Möchtest du etwas?";
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//---------------------------------------------Джимми в доме в Марун-Тауне------------------------------------
		case "Jimmy":
			dialog.text = "Was willst du? Siehst du nicht, dass ich in Trauer bin! Verschwinde, bevor ich dich die Treppe runter trete!";
			link.l1 = "Nun, kauf dir ein größeres Haus mit Treppen dafür. Dann sprechen wir über das Treten von Menschen die Treppe hinunter, Held...";
			link.l1.go = "Jimmy_1_1";
			link.l2 = "Warum bist du so verärgert, Jimmy? Kein Rum mehr für mich für den Rest meines verdammten Lebens, wenn es nichts mit einer schönen Frau zu tun hat! Nur eine Frau könnte einen alten Seewolf wie dich dazu bringen, deine alten Freunde zu bedrohen...";
			link.l2.go = "Jimmy_1_2";
		break;
		
		case "Jimmy_1_1":
			dialog.text = "Ich hasse pingelige Leute wie dich! Ihr bekommt immer die besseren Stücke vom Kuchen. Sie haben mir nicht erlaubt, einen Emporkömmling zu töten, also werde ich meinen Ärger an dir auslassen!";
			link.l1 = "...";
			link.l1.go = "Jimmy_fight";
		break;
		
		case "Jimmy_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_KillJimmy");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Jimmy_1_2":
			dialog.text = "Ja?! Kenn ich dich? Ich erinnere mich nicht an dich, verdammt noch mal...";
			link.l1 = "Es bin ich, "+pchar.name+"! Wir hatten eine schöne Zeit in Blueweld, nachdem du fast diesen unverschämten Kerl im Mantel aufgeschlitzt hast. Wie war sein Name nochmal? Ich habe es vergessen... Wie auch immer, ich werde einen Dreck um die Kanonen seiner Korvette geben, wenn ich ihn jemals auf See treffe!";
			link.l1.go = "Jimmy_2";
		break;
		
		case "Jimmy_2":
			dialog.text = "Sein Name war Arthur! Arthur Donovan, Kapitän der Korvette 'Arbutus'! Dreckiger Bastard! Also stimmst du zu, dass ich kurz davor war, ihn zum Teufel zu schicken?";
			link.l1 = "Natürlich! Er hatte absolut keine Chance, aber deine Kameraden haben sich eingemischt. Verzeihe ihnen, sie wollten nicht, dass du wegen Mordes an einem Marineoffizier gehängt wirst.";
			link.l1.go = "Jimmy_3";
		break;
		
		case "Jimmy_3":
			dialog.text = "Argh! Wenn ich nur ein Schiff hätte! Dieser Bastard kann leicht bei Antigua aufgespürt werden... ha! Ich schulde dir einen Gefallen, wenn du ihn auf den Grund schickst!";
			link.l1 = "Abmachung, ha-ha! Übrigens, ist Rumba wirklich deine Leiden wert?";
			link.l1.go = "Jimmy_4";
		break;
		
		case "Jimmy_4":
			dialog.text = "Aber natürlich! Ich habe noch nie jemanden getroffen, der besser ist als sie. Aber sie lacht nur über mich. Jeder will diese Meerjungfrau. Einige Matrosen haben mir heimlich gesagt, dass unser Jakob ein Mädchen sucht, das genauso aussieht wie meine Rumba. Er will sie auch! Wie kann ich jetzt seinen Befehlen folgen?";
			link.l1 = "Halt den Mund, Kumpel! Wände haben Ohren ... Und warum glaubst du, dass Jackman nach Rumba sucht?";
			link.l1.go = "Jimmy_5";
		break;
		
		case "Jimmy_5":
			dialog.text = "Das ist er, ganz sicher! Er sucht nach einem gewissen Henry Hangman, und einem zwanzigjährigen Mädchen mit blonden Haaren und blauen Augen. Eine gewisse Gladys Chandler aus Belize muss ihre Pflegerin sein.";
			link.l1 = "Warte! Gladys hat einen anderen Nachnamen. Und sie ist ihre Mutter!";
			link.l1.go = "Jimmy_6";
		break;
		
		case "Jimmy_6":
			dialog.text = "Jackman ist gerissen! Du kannst ihn nicht unvorbereitet erwischen! Ich habe Rumba eine Weile umworben und herausgefunden, dass Gladys vor genau zwanzig Jahren Sean McArthur geheiratet hat. Und davor lebte sie in Belize. Ihr erster Ehemann hieß Pete Chandler.\nDer arme Pete wurde in einem betrunkenen Streit getötet. Man sagt, dass McArthur selbst verantwortlich war, da er damals Gefühle für die mollige Gladys hatte. Sie wurde eine Witwe mit einem Baby in den Händen. Das Kind überlebte seinen Vater nicht lange und starb bald darauf an einem Fieber.\nUnd nur ein paar Monate nachdem Gladys und Sean mit einem Mädchen in Blueweld auftauchten, das angeblich McArthurs Tochter ist. Wie konnte Gladys so schnell ein weiteres Baby zur Welt bringen? Verstehst du?";
			link.l1 = "Hast du sonst noch jemandem davon erzählt?";
			link.l1.go = "Jimmy_7";
		break;
		
		case "Jimmy_7":
			dialog.text = "Noch nicht. Halte dein Maul oder.... nun, du kennst mich!";
			link.l1 = "Ja, das tue ich. Du hast eine faule Zunge, die jedem ihre Geheimnisse erzählt. Rumba hatte recht, dich fortzuschicken, Schwätzer...";
			link.l1.go = "Jimmy_8_1";
			link.l2 = "Sicher! Ich werde schweigsam sein! Und jetzt muss ich gehen. Lebewohl, Jimmy.";
			link.l2.go = "Jimmy_8_2";
		break;
		
		case "Jimmy_8_1":
			dialog.text = "Was... was hast du gesagt?!";
			link.l1 = "Du wirst es niemandem sonst erzählen können...";
			link.l1.go = "Jimmy_fight";
			pchar.questTemp.Saga.Jimmysecret = "true";
		break;
		
		case "Jimmy_8_2":
			DialogExit();
			pchar.questTemp.Saga = "jackman";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "4_1");
		break;
// <-- Джимми 
		
//-------------------------------------------корвет Донована, абордаж-----------------------------------------
		//Донован
		case "Donovan_abordage":
			PlaySound("Voice\English\saga\Artur Donovan.wav");
			dialog.text = "Argh, du Ungeheuer!";
			link.l1 = "Redest du mit dir selbst, Mister?! Wo ist Rumba?";
			link.l1.go = "Donovan_abordage_1";
		break;
		
		case "Donovan_abordage_1":
			dialog.text = "Was für eine Rumba? Ich habe kein Gesindel mit Spitznamen auf meinem Schiff. Das ist ein englisches Kriegsschiff!";
			link.l1 = "Spiel nicht den Dummen mit mir, Donovan. Du weißt genau, wen ich meine. Wo ist das Mädchen? Wo ist Helen? Antworte mir, du dreckiges Schwein...";
			link.l1.go = "Donovan_abordage_2";
		break;
		
		case "Donovan_abordage_2":
			dialog.text = "Helen? Es gibt keine Landhuren auf meinem Schiff, du Stück Scheiße!";
			link.l1 = "Keine Landhuren? Schwer zu glauben, da eine von ihnen gerade vor mir steht... Ich nehme an, es hat keinen Sinn, unser Gespräch fortzusetzen. Stirb, du jämmerlicher Wurm!";
			link.l1.go = "Donovan_abordage_3";
		break;
		
		case "Donovan_abordage_3":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Takehelen = "true";//признак, что абордировали судно
		break;
		
		//наш матрос
		case "Tempsailor":
			dialog.text = "Kapitän, wir haben alle Kabinen und den Frachtraum durchsucht, wie Sie es uns befohlen haben. Wir haben ein angekettetes Mädchen im Frachtraum gefunden...";
			link.l1 = "Was für ein Schuft! Genau wie ich dachte... Habt ihr das Mädchen losgekettet?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Sicher, Kapitän. Sie wurde sicher auf Ihr Schiff gebracht.";
			link.l1 = "Gut gemacht! Bring sie in meine Kabine, ich möchte mit ihr sprechen, sobald wir hier fertig sind.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Aye-aye, Kapitän!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//<-- абордаж корвета Донована
		
//----------------------------------------поиск Энрике Гонсалеса, Картахена----------------------------------
		//фальшивый Гонсалес №1, дом
		case "GonsalesA":
			dialog.text = "Brauchst du etwas?";
			link.l1 = "Hallo, Hangman! Kapitän Butcher lässt grüßen.";
			link.l1.go = "GonsalesA_1_1";
			link.l2 = "Mein Name ist Charles de Maure. Ich suche Enrique, den Sohn der Senora Gonzales im Auftrag ihres alten Freundes. Ich denke, dass du er bist...";
			link.l2.go = "GonsalesA_2_1";
		break;
		
		case "GonsalesA_1_1":
			dialog.text = "Was zur Hölle! Ich kenne keinen Butcher!";
			link.l1 = "Komm schon, Henry. Sag mir, warum Jackmans Piraten dich suchen und ich werde dir nicht wehtun.";
			link.l1.go = "GonsalesA_1_2";
		break;
		
		case "GonsalesA_1_2":
			dialog.text = "Hilfe! Piraten! Mord!";
			link.l1 = "Halt die Klappe, Idiot! Die halbe Stadt wird hierher rennen wegen deines Geschreis. Ah, ist das das, was du will?!";
			link.l1.go = "GonsalesA_1_fight";
		break;
		
		case "GonsalesA_1_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesA_2_1":
			dialog.text = "Hm... Mister, Sie müssen sich irren. Ich bin in einer fremden Familie aufgewachsen, ich erinnere mich nicht an meine leibliche Mutter. Ich habe den Nachnamen meines Pflegevaters angenommen. Ich kenne den Namen meiner Mutter nicht, aber ich bezweifle, dass er Gonzales war. Sie können sich über mich erkundigen und jeder alte Bewohner wird meine Worte bestätigen. Mein Stiefvater war ein berühmter Mann, er hatte keine eigenen Kinder, also habe ich dieses Haus geerbt und...";
			link.l1 = "Es tut mir leid. Es scheint, dass ich mich geirrt habe. Lebewohl.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesA_3_1";
			else link.l1.go = "GonsalesA_2_2";
		break;
		
		case "GonsalesA_2_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "17");
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesA_3_1":
			dialog.text = "Ich denke nicht so.";
			link.l1 = "Entschuldigung?";
			link.l1.go = "GonsalesA_3_2";
		break;
		
		case "GonsalesA_3_2":
			dialog.text = "Wissen Sie, vor kurzem wurde unsere Kolonie heftig von Piraten angegriffen. Sie haben davon gehört, nicht wahr? Als Ergebnis dieses Angriffs haben unzählige Menschen gelitten. Ich blieb unverletzt, doch mein ererbtes Geschäft durchlebt jetzt schwere Zeiten. Und der Schuldige an all diesem Unglück ist der Anführer dieser Piraten, ein Schurke namens Charlie Prince.";
			link.l1 = "Es tut mir sehr leid, aber was hat das mit mir zu tun?";
			link.l1.go = "GonsalesA_3_3";
		break;
		
		case "GonsalesA_3_3":
			dialog.text = "Ha-ha, schau dir nur dieses unschuldige Lamm an! Ich schlage vor, du deckst meine Verluste, da du der Schuldige dafür bist. Ich werde mit einer Summe von fünfzehntausend Pesos zufrieden sein. Und ich werde so tun, als wärst du nie in meinem Haus gewesen.";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "Wie nachtragend ihr alle seid... Hier ist euer Geld. Und denkt daran, wenn jemand herausfindet, dass ich in dieser Stadt war, komme ich zurück für euch.";
				link.l1.go = "GonsalesA_3_4";
			}
			link.l2 = "Fünfzehntausend? Hm... Ich glaube nicht, dass dein Leben so viel wert ist. Also, ich denke, es ist billiger, dich einfach niederzuschneiden, um dich vom Plappern abzuhalten.";
			link.l2.go = "GonsalesA_3_5";
		break;
		
		case "GonsalesA_3_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "171");
		break;
		
		case "GonsalesA_3_5":
			dialog.text = "Wachen! Piraten! Mord!";
			link.l1 = "Halt die Klappe, Idiot!";
			link.l1.go = "GonsalesA_3_6";
		break;
		
		case "GonsalesA_3_6":
			DialogExit();
			iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SpSold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, iTemp, true);         
				LAi_SetWarriorType(sld); 
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			sld = GetCharacter(NPC_GenerateCharacter("SpOfficer", "off_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol6", "bullet", 150);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesAK");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		// <-- участвовал в событиях Картахены
		
		// фальшивый Гонсалес №2, улицы
		case "GonsalesB":
			PlaySound("Voice\English\citizen\Pirati v Gorode-08.wav");
			dialog.text = "Ich sehe, dass dir mein Entermesser gefällt. Ich kann es dir verkaufen, wenn du willst. Ich werde nicht viel verlangen, ich sterbe vor Verlangen nach etwas Rum und meine Taschen sind leer.";
			link.l1 = "Und warum zum Teufel sollte ich es brauchen? Der Forest Devil hat mich gebeten, dir seine besten Grüße zu übermitteln.";
			link.l1.go = "GonsalesB_1_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "Nun, ja. Du hast wirklich einen feinen Säbel. Wie viel?";
				link.l2.go = "GonsalesB_2_1";
			}
		break;
		
		case "GonsalesB_1_1":
			dialog.text = "Er hätte mir besser ein paar hundert Pesos gegeben!";
			link.l1 = "Also kennst du Svenson?";
			link.l1.go = "GonsalesB_1_2";
		break;
		
		case "GonsalesB_1_2":
			dialog.text = "Fick dich und deinen Svenson, schick ihn zum Teufel. Zum Forest Devil oder zum Seeteufel, das ist mir scheißegal. Wenn du nicht bereit bist, einem kranken Mann zu helfen, indem du seinen Säbel kaufst, dann stecke ich ihn dir kostenlos direkt in den Arsch.";
			link.l1 = "Wirklich? Lass sehen, wie du das machen wirst, du Arschgesicht!";
			link.l1.go = "GonsalesB_1_fight";
		break;
		
		case "GonsalesB_1_fight":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesB_2_1":
			dialog.text = "Ich sehe, Sie sind ein Mann mit Erfahrung! Tausend Pesos und es gehört Ihnen.";
			link.l1 = "Abgemacht!";
			link.l1.go = "GonsalesB_2_2";
		break;
		
		case "GonsalesB_2_2":
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(pchar, "blade_10");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "Es gibt nur zwei solche Säbel in Cartagena - meiner und der alte Alvares' vom Leuchtturm. Aber er wird seinen nicht verkaufen. Er ist ein Heuchler, ich kann einen ehemaligen Piraten aus einer Meile Entfernung riechen. Die Klinge ist eine Art Talisman für ihn.\nEs scheint, dass die arme Seele Dinge beweint, die sie vergessen will. Das muss der Grund sein, warum er jeden Monat in die Kirche geht, wegen Sünden, die ihm den Schlaf nicht lassen.";
			link.l1 = "Und ich sehe, dass du auch eine Geschichte hast. Du musst derjenige sein, von dem Svenson gesprochen hat. Er sagte, ich solle dir seine besten Grüße überbringen, falls ich dich in Cartagena treffen würde.";
			link.l1.go = "GonsalesB_2_3";
		break;
		
		case "GonsalesB_2_3":
			dialog.text = "Svenson? Noch nie von ihm gehört. Mein Name ist Enrique Gallardo. Aber wenn dein Svenson eine Flasche Rum für mich hat, bin ich bereit, für ihn Henry zu sein. Nennen Sie mich, wie Sie wollen, nennen Sie mich einfach nicht zu spät zum Abendessen. Also, gehen wir?";
			link.l1 = "Nicht heute. Svenson ist weit weg, aber die Kneipe ist in der Nähe. Deine Taschen sind nicht mehr leer, also pass auf, Enrique.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesB_3_1";
			else link.l1.go = "GonsalesB_2_4";
		break;
		
		case "GonsalesB_2_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "19");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesB_3_1":
			dialog.text = "Sie sind jedoch nicht ganz voll. Ich will mehr. Und du wirst mich bezahlen.";
			link.l1 = "Ich bin verwirrt... Schätzt du dein Leben nicht? Du planst, mich mitten in der Stadt auszurauben? Und das, nachdem du mir gerade selbst deine Waffe verkauft hast?";
			link.l1.go = "GonsalesB_3_2";
		break;
		
		case "GonsalesB_3_2":
			dialog.text = "Nein, du wirst mich aus eigener Tasche bezahlen. Und du weißt warum?";
			link.l1 = "Neugierig zu hören.";
			link.l1.go = "GonsalesB_3_3";
		break;
		
		case "GonsalesB_3_3":
			dialog.text = "Ich habe dich erkannt. Ich war wegen einer betrunkenen Schlägerei in der Taverne in den Kerkern, als deine Leute ins Gefängnis stürmten und alle Wachen niedermetzelten. Ich schaffte es, die Leiche des Wächters mit den Schlüsseln zu erreichen und auf die Straßen zu gelangen. Die Stadt stand in Flammen, überall Leichen, Blut und Pulverrauch... Genau wie bei einer Entermannschaft! Und durch diesen Rauch sah ich dich aus der Residenz des Gouverneurs kommen. Poetisch, nicht wahr? Yo-ho-ho, hallo, Charlie Prinz!";
			link.l1 = "Hör auf so zu schreien! Bei dem, was du weißt, solltest du besonders nicht versuchen, Geld aus mir herauszupressen. Hast du überhaupt eine Ahnung, was ich dir antun kann?";
			link.l1.go = "GonsalesB_3_4";
		break;
		
		case "GonsalesB_3_4":
			dialog.text = "In der Mitte der Stadt, die du einst ausgeraubt hast? Du kannst nichts tun. Also, um es abzuschließen... werden wir es so machen: du gibst mir... sagen wir, zehntausend Pesos jetzt sofort. Ich denke, das wird für einen Monat ausreichen. Und du gehst deinen Weg! Ob zu deinem geliebten Henry, zu Svenson oder zu jedem anderen Teufel deiner Wahl... Und wenn du es nicht tust, muss ich nur schreien, und sie werden dich in eine speziell vorbereitete persönliche Kammer voller Folterwerkzeuge schleifen.";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Verdammt noch mal, nimm deine zehntausend und verschwinde aus meinen Augen! Und Gott bewahre, ich sehe dich noch einmal.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Das ist es, ich habe genug davon. Deine Waffe gehört mir, also hast du keine Chance, Abschaum.";
			link.l2.go = "GonsalesB_3_7";
			link.l3 = "Haha, du bist gut! Weißt du was? Bei jedem anderen hätte ich schon längst vom Bauch bis zum Hals aufgeschnitten. Aber Leute wie dich brauche ich. Wie wäre es damit: Ich gebe dir zehntausend Pesos, gebe dir deinen 'Gehenkten Mann' zurück und lege jeden Monat noch dreitausend drauf - Sollte genug für Schnaps sein - Und du wirst ein Bewohner auf meinem Schiff.";
			link.l3.go = "GonsalesB_3_9";
		break;
		
		case "GonsalesB_3_5":
			dialog.text = "Also gut, also gut, ich bin schon weg! Viel Glück bei deiner Suche, Charlie Prinz!";
			link.l1 = "...";
			link.l1.go = "GonsalesB_3_6";
		break;
		
		case "GonsalesB_3_6":
			AddMoneyToCharacter(pchar, -10000);
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "191");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		case "GonsalesB_3_7":
			dialog.text = "Wachen! Wachen!!! Es ist Charlie Prince!!!";
			link.l1 = "Du verdammter Schuft!";
			link.l1.go = "GonsalesB_3_8";
		break;
		
		case "GonsalesB_3_8":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			LAi_group_AttackGroup("Spain_citizens", LAI_GROUP_PLAYER);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "192");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
		break;
		
		case "GonsalesB_3_9":
			dialog.text = "Suggerieren Sie, dass ich Ihrer Crew beitreten soll?";
			link.l1 = "Genau. Aber das ist ein einmaliges Angebot. Also, was sagst du? Zustimmen, oder ich werde deine Eingeweide ausschütten. Du glaubst doch nicht wirklich, dass du Charlie Prince so leicht erpressen kannst, oder?";
			link.l1.go = "GonsalesB_3_10";
		break;
		
		case "GonsalesB_3_10":
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 && makeint(pchar.reputation.nobility) < 48)
			{
				dialog.text = "Teufel! Charlie Prince bietet mir selbst an, seiner Crew beizutreten! Verdammt, ich stimme zu! Gib mir meine Klinge zurück und zehntausend Pesos. Hätte nie gedacht, dass es so kommen würde!";
				link.l1 = "Hier. Und halt den Mund: Niemand in dieser Stadt muss wissen, wer ich bin, verstanden?";
				link.l1.go = "GonsalesB_3_11";
				break;
			}
			if(makeint(pchar.reputation.nobility) > 47)
			{
				dialog.text = "Nein. Du magst ein anständiger Kapitän sein, aber mir scheint, du bist ein bisschen zu steif. Ja, du hast den Spaniern einmal Angst eingejagt, indem du einen waghalsigen Überfall auf Cartagena durchgeführt hast - aber all das war nur mit der Hilfe von Marcus Tyrex. Du hast nicht den Mumm, ehrliches Plündern alleine zu machen. Also, her mit der Knete!";
			}
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
			{
				dialog.text = "Nein. Du bist sicherlich ein berüchtigter Pirat, aber als Kapitän scheinst du nicht sehr beeindruckend zu sein. Du hast es nur mit Hilfe von Marcus Tyrex geschafft, die Kolonie zu plündern - du würdest dich nicht einmal trauen, alleine eine heruntergekommene Schaluppe zu entern. Also, rück das Geld heraus!";
			}
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Verdammt, nimm deine zehntausend und verschwinde aus meinen Augen! Und Gott bewahre, ich sehe dich wieder.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Das ist es, ich habe genug davon. Deine Waffe ist mein, also hast du keine Chance, Abschaum.";
			link.l2.go = "GonsalesB_3_7";
		break;
		
		case "GonsalesB_3_11":
			dialog.text = "Verstanden, ich bin kein Narr.";
			link.l1 = "Gut.";
			link.l1.go = "GonsalesB_3_12";
		break;
		
		case "GonsalesB_3_12":
			DialogExit();
			AddMoneyToCharacter(pchar, -10000);
			LAi_RemoveLoginTime(npchar);
			npchar.quest.OfficerPrice = 3000;
			npchar.reputation.nobility = 30;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			npchar.loyality = MAX_LOYALITY;
			GiveItem2Character(npchar, "blade_10");
			EquipCharacterByItem(npchar, "blade_10");
			TakeItemFromCharacter(pchar, "blade_10");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			AddQuestRecord("Saga", "193");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
		break;
		// <-- участвовал в событиях Картахены
		
		//настоящий Гонсалес - Ортега, маяк
		case "Ortega":
			dialog.text = "Ich erwarte keine Gäste, weder heute noch an einem anderen Tag. Was wollen Sie?";
			link.l1 = "Hallo, Hangman. Der Forest Devil hat mich geschickt. Es ist gut, dass ich dich gefunden habe, bevor Jackmans Burschen es taten. Seine Männer suchen dich überall in der Karibik. Zum Glück für dich, Henry, weiß nur Svenson, wo du geboren wurdest. Er hat mich gebeten, dich zu warnen.";
			link.l1.go = "Ortega_1";
		break;
		
		case "Ortega_1":
			dialog.text = "Ich sehe jetzt... Also, es scheint, dass Svenson noch lebt und seinen alten Freund nicht vergessen hat. Viel Blut ist geflossen, seit ich ihn zum ersten Mal als einen Neuling an Bord einer beschädigten Brigantine sah... Das Leben ist zu schnell vergangen und mir bleibt nicht viel Zeit\nIch wollte auf dieser Ödnis eines natürlichen Todes sterben, fernab der Menschheit und nahe am Meer. Aber wenn Jackman zurück in der Karibik ist, wird er mich nicht in Ruhe lassen. Es war nicht meine Schuld, aber ich schulde seinem Meister. Wie auch immer, wer wird mir jetzt glauben.\nIch fürchte nicht den Tod, sondern den Schmerz. Und Jackman weiß viel über Schmerz. Der Gedanke daran allein lässt mein Herz stehen und alles wird dunkel.";
			link.l1 = "Bucther wurde vor zwanzig Jahren gehängt, also musst du niemandem Schulden zurückzahlen. Du kannst mir deine Schulden geben, wenn du vor Jackman Angst hast. Ich denke, du wirst ihm sowieso begegnen.";
			link.l1.go = "Ortega_2";
		break;
		
		case "Ortega_2":
			dialog.text = "Es ist nicht einfach, Leute wie den Butcher aufzuhängen. Der ehemalige Henker von St. John könnte dir viele interessante Geschichten über die Toten erzählen, die aus der Hölle zurückgekehrt sind. Und Jakob wurde gut von seinem Kapitän unterrichtet, also bin ich mir nicht sicher, wen ich am meisten fürchte.";
			link.l1 = "Warum braucht Jackman dich?";
			link.l1.go = "Ortega_3";
		break;
		
		case "Ortega_3":
			dialog.text = "Ich musste Gold an eine Witwe liefern als Bezahlung dafür, dass sie die Tochter von Butcher sicher hielt. Warum schaust du mich so an? Ja, sie wurde nicht lange vor dem Untergang der 'Neptune' geboren. Er konnte nicht rechtzeitig für sie zurück sein, also schickte er mich, um mich um das Baby und ihre Pflegerin zu kümmern.";
			link.l1 = "War Gladys Chandler der Name der Betreuerin?";
			link.l1.go = "Ortega_4";
		break;
		
		case "Ortega_4":
			dialog.text = "Spiel nicht den Idioten. Wenn Jackman mich sucht, dann braucht er die Tochter von Butcher. Du musst schon wissen, dass er nach einer Frau aus Belize namens Gladys und ihrem Pflegekind sucht. Sei ehrlich zu mir und ich könnte dir vielleicht vertrauen.";
			link.l1 = "Was solltest du Gladys sagen?";
			link.l1.go = "Ortega_5";
		break;
		
		case "Ortega_5":
			dialog.text = "Nichts. Ich sollte ihr den Ring von Butcher zeigen, so würde sie wissen, dass ich ein Kurier war, der vom Kapitän geschickt wurde. Ich musste ihr auch eine Truhe voller Dublonen für die Bedürfnisse des Babys geben. Ich musste einen Bastard töten, um den Ring wegzunehmen. Dadurch musste ich meinen Aufenthalt auf Antigua um einen weiteren Monat verlängern.\nUnd als ich endlich Belize erreicht hatte, war Gladys bereits verschwunden und die Stadt wurde von den Spaniern verbrannt und geplündert. Sie schaffte es, ihr Haus zu verkaufen und mit ihrem neuen Freund und Baby Helen wegzulaufen. Ich hoffe, dass sie sich um sie gekümmert hat und das Mädchen nicht an die Zigeuner oder in das Bordell verkauft hat.";
			link.l1 = "Der Name der Tochter von Butcher war Helen, richtig?";
			link.l1.go = "Ortega_6";
		break;
		
		case "Ortega_6":
			dialog.text = "Genau. Zu Ehren der Mutter von Butcher. Wenn du keine Angst vor den Lebenden Toten und Piraten hast, die dich mit toten Augen ansehen, dann kann ich dir den Ring und Gold geben. Ich habe es nie angefasst. Ich bin vor Hunger gestorben, aber ich habe es nicht berührt. Tu damit, was du willst. Und im Gegenzug bitte ich dich...";
			link.l1 = "Was passiert, Henry?!";
			link.l1.go = "Ortega_7";
		break;
		
		case "Ortega_7":
			dialog.text = "Du...u... Ich fr...a...ge.... oh!";
			link.l1 = "Nein!";
			link.l1.go = "Ortega_8";
		break;
		
		case "Ortega_8":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			AddQuestRecord("Saga", "20");
			pchar.questTemp.Saga = "svenson1";
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "bucher_ring"); //перстень Бучера
			//таймер на возврат смотрителя
			SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
			//ставим прерывания, если ГГ наследил в городе
			if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
			{
				pchar.quest.Saga_Trap.win_condition.l1 = "location";
				pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
				pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
				CoolTraderHunterOnMap();
			}
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs");
			//pchar.questTemp.HelenDrinking = "end_henry";
		break;
		
		//бандиты в поисках Гонсалеса, маяк
		case "saga_trap":
			dialog.text = "A-ah, da ist unser neugieriger Freund! Hast du endlich Gonzales gefunden? Gut gemacht, du hast uns zu ihm gebracht... wir brauchen dich nicht mehr. Jungs, tötet diesen Narren!";
			link.l1 = "Zeit zu sterben, Krabben-Futter!";
			link.l1.go = "saga_trap_1";
		break;
		
		case "saga_trap_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			int n = makeint(MOD_SKILL_ENEMY_RATE/3);
			for (i=1; i<=3+n; i++)
			{	
				sld = characterFromId("sagatrap_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//<-- поиск Гонсалеса, Картахена
		
//--------------------------------------------НПС по квесту Возвращение барона---------------------------------
		
		// доминиканский вождь
		case "DominicaHead":
			dialog.text = "U-ah! U-ah! Der große Kukulcan fordert ein neues Opfer! O-eh! Der Geist des mächtigen Kriegers der Vergangenheit kam in unser Dorf, um dem großen Kukulcan geopfert zu werden! O-eh! Alle verneigen sich vor dem mächtigen Kriegergeist!";
			link.l1 = "(leise) Was zum Teufel, wo bin ich?";
			link.l1.go = "DominicaHead_1";
			NextDiag.TempNode = "DominicaHead";
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "DominicaHead_1":
			dialog.text = "O-eh! Großer Krieger will vom großen Kukulcan gefressen werden! Sonne steigt, Schatten verkürzen sich! Großer Kukulcan wird bald lebendig sein! Wir bringen dich zu ihm, oh mächtiger Krieger, und du setzt deine Reise durch das Land der Ahnen fort!";
			link.l1 = "(leise) Unsinn... Kukulcan schon wieder? Hey, Chef, ich komme in Frieden! Ich bin hier um...";
			link.l1.go = "DominicaHead_2";
		break;
		
		case "DominicaHead_2":
			dialog.text = "O-eh! Großer Krieger sagt, er will sofort Kukulcan geopfert werden. Oh, großer Krieger! Wir gehen jetzt zu Kukulcan und warten auf seinen Besuch! Krieger! Wir haben die große Ehre, den Geist des Ahnen zu Kukulcan zu bringen!";
			link.l1 = "(leise) Idiot... Gut, ich muss mit ihnen gehen. Es ist gut, dass sie mich noch nicht angegriffen haben, ich könnte mich in diesem Ding nicht verteidigen...";
			link.l1.go = "DominicaHead_3";
		break;
		
		case "DominicaHead_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;
		
		case "DominicaHead_4":
			dialog.text = "Wir kommen zu Kukulcan, großem Ahnengeist. Bald geht die Sonne unter, die Schatten wachsen und Kukulcan wird uns besuchen. Warte, großer Krieger...";
			link.l1 = "(leise) Jetzt sehe ich, indianischer Kriegshäuptling...";
			link.l1.go = "DominicaHead_5";
		break;
		
		case "DominicaHead_5":
			DialogExit();
			bDisableCharacterMenu = true;//лочим Ф2
			AddQuestRecord("BaronReturn", "7");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
			pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;
		
		case "DominicaHead_6":
			dialog.text = "Kukulcan lebt! Kukulcan ist bei uns! Großer Krieger kann Kukulcan geopfert werden! Krieger, verbeugt euch vor dem großen Ahnengeist!";
			link.l1 = "(leise) Bleib weg, Chef. Ich mache es selbst. Es ist nicht mein erstes Mal...";
			link.l1.go = "DominicaHead_7";
		break;
		
		case "DominicaHead_7":
			DialogExit();
			bDisableCharacterMenu = false;//разлочим Ф2
			AddQuestRecord("BaronReturn", "8");
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
			}
		break;
		
//----------------------------------------НПС по квесту Искушение Барбазона----------------------------------
		// капитан рыболовного баркаса, стыривший шелк, море
		case "BarbCapBarkas":
			dialog.text = "Wie kann ich Ihnen helfen, Mynheer?";
			link.l1 = "Nun, nun.. erzähl mir, Kumpel, was machst du hier?";
			link.l1.go = "BarbCapBarkas_1";
		break;
		
		case "BarbCapBarkas_1":
			dialog.text = "Was mache ich hier? Ich bin ein Fischer und ich fische hier. Und warum zum Teufel verhörst du mich in solch einem Tonfall?";
			link.l1 = "Lüg mich nicht an, Kumpel. Vielleicht bist du wirklich ein Fischer, aber du hast hier keine Fische gefischt. Wertvolle Schiffsseide wurde hier an diesem Ort ins Meer geworfen. Und deine bloße Anwesenheit sieht für mich ziemlich verdächtig aus.";
			link.l1.go = "BarbCapBarkas_2";
		break;
		
		case "BarbCapBarkas_2":
			dialog.text = "Was für ein Unsinn? Von welcher Seide sprichst du überhaupt?";
			link.l1 = "Was für Seide? Chinesische... Spiel nicht den Idioten! Hör mir jetzt zu: Entweder du holst sofort die Seide aus deinem Frachtraum und gibst sie mir oder ich hole sie mir selbst. Aber zuerst wird meine Entertruppe sich um dich und deine Leute kümmern. Also? Soll ich meine Männer rufen?";
			link.l1.go = "BarbCapBarkas_3";
		break;
		
		case "BarbCapBarkas_3":
			dialog.text = "Nein! Mynheer, ich wusste nicht... Diese Ballen trieben einfach herum, also habe ich entschieden...";
			link.l1 = "Bring die Seide zu meinem Schiff. Mach schnell!";
			link.l1.go = "BarbCapBarkas_4";
		break;
		
		case "BarbCapBarkas_4":
			dialog.text = "Ja, ja, sicher. Wir werden das sofort tun, nur nehmen Sie mein Boot nicht!";
			link.l1 = "Beweg deinen Arsch! Ich habe nicht viel Zeit...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;
		
		case "BarbCapBarkas_5":
			dialog.text = "Hier, wir haben alles gebracht, was wir gefunden haben - alle neun Ballen. Das ist alles, ich schwöre...";
			link.l1 = "Gut. Du kannst weiterfischen, aber leg in Zukunft dein Auge nicht auf die Habseligkeiten anderer Leute!";
			link.l1.go = "BarbCapBarkas_6";
		break;
		
		case "BarbCapBarkas_6":
			DialogExit();
			npchar.DontDeskTalk = true;
			npchar.lifeday = 0;
			LAi_SetStayType(npchar);
			pchar.quest.BarbBarkas_Sink.over = "yes"; //снять прерывание
			pchar.quest.BarbBarkas_Abordage.over = "yes"; //снять прерывание
			NextDiag.CurrentNode = "BarbCapBarkas_7";
			AddQuestRecord("BarbTemptation", "6");
			pchar.questTemp.Saga.BarbTemptation = "give_silk";
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "BarbCapBarkas_7":
			dialog.text = "Du hast schon bekommen, was du wolltest. Ich habe nichts mehr übrig! Was brauchst du noch?";
			link.l1 = "Entspann dich, Kumpel. Ich gehe jetzt.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BarbCapBarkas_7";
		break;
		
		// Моррель, капитан потопленного судна, тюрьма
		case "Morelle":
			dialog.text = "Wenn du von Barbazon geschickt wurdest, dann sag ihm, dass ich das Gefängnis nicht selbst verlassen möchte. Ich warte lieber auf den Prozess. Selbst niederländischer Hanf an meinem Hals ist besser als seine Freundlichkeit.";
			link.l1 = "Sei noch nicht erleichtert. Dein Navigator hat Jacques erzählt, dass du tot bist. Er hat mich geschickt, um die Seide zu finden, die du ins Meer geworfen hast. Wie viel davon war auf deiner Brigantine?";
			link.l1.go = "Morelle_1";
		break;
		
		case "Morelle_1":
			dialog.text = "Es war mein Fehler, verdammt. Der Kurier brachte neun Ballen Seide für Barbazon. Ich befahl ihm zu folgen. Er wurde laut, also mussten wir ihm die Kehle durchschneiden. Er hatte drei zusätzliche Ballen in seinem Versteck, die ich für mich genommen und in meinem eigenen Versteck versteckt habe. Aber es scheint, dass wir unerwünschte Aufmerksamkeit erregt haben.\nSie fanden uns schnell und eine holländische Patrouille wartete auf den 'Salzhund' in der offenen See. Wir konnten nicht entkommen. Du kannst die Seide für dich behalten, wenn du Barbazon nichts von mir erzählst. Das Versteck befindet sich am Grand Case Beach zwischen den Steinen in der Sackgasse. Es ist unwahrscheinlich, dass ich es noch einmal brauchen werde.";
			link.l1 = "Gut. Ich werde Barbazon nicht sagen, dass du noch lebst. Wenn das, was sie über ihn sagen, wahr ist, dann ist es besser für dich, von den Holländern gehängt zu werden. Oder vielleicht hast du Glück und sie verurteilen dich zu Zwangsarbeit.";
			link.l1.go = "Morelle_2";
		break;
		
		case "Morelle_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			// тайник - модель
			//int m = Findlocation("Shore40");
			//locations[m].models.always.Roll = "Roll_of_rolls";
			//Locations[m].models.always.Roll.locator.group = "quest";
			//Locations[m].models.always.Roll.locator.name = "quest1";
			pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
			pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
			pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
		
		// Валет, брат Джекмана в Капстервиле
		case "valet":
			dialog.text = "Ich warte auf den Mann, der weiß, wann die Jagd auf den weißen Hai beginnen wird.";
			link.l1 = "Die Jagd hat begonnen.";
			link.l1.go = "valet_1";
		break;
		
		case "valet_1":
			dialog.text = "Endlich! Jetzt hören Sie gut zu. Sie müssen Marcus Tyrex in La Vega besuchen und ihm sagen, dass die Brigantine 'Separator' in der Nähe der Turks-Insel angegriffen wurde und sich jetzt in der Southern Bay versteckt. Ihr Kapitän ist schwer verletzt und die Besatzung wartet auf Hilfe. Sie haben einen Seemann des 'Separator' aufgesammelt und er hat Ihnen alles erzählt. Er ist jetzt tot. Das ist alles, was Sie wissen. Verstanden?";
			link.l1 = "Und warum brauchen Sie mich dafür? Ich habe zu lange nur dafür gewartet...";
			link.l1.go = "valet_2";
		break;
		
		case "valet_2":
			dialog.text = "Sie werden bezahlt, um Ihre Arbeit zu tun und nicht um Fragen zu stellen. Sie haben allerdings recht. Ich muss Sie warnen, dass Tyrex Sie nicht gehen lässt, bis er sicher ist, dass Sie die Wahrheit sagen. Aber sobald er alles herausfindet, wird er Sie gut bezahlen. Wenn er dazu in der Lage sein wird...";
			link.l1 = "Sie ziehen mir die Wolle über die Augen, Mister... Warum wollen Sie seinen Dank nicht selbst entgegennehmen?";
			link.l1.go = "valet_3";
		break;
		
		case "valet_3":
			dialog.text = "Carramba! Mir gefällt deine Neugier nicht! Dein Geschwätz wird dich eines Tages direkt ins Grab führen.";
			link.l1 = "Ja, manchmal bin ich unerträglich. Besonders, wenn ich sehe, dass jemand versucht, mich zu übers Ohr hauen. Nein, Kumpel, jetzt spielen wir nach meinen Regeln. Wer ist dein Meister, verdammt noch mal? Antworte oder ich werde dich leiden lassen!";
			link.l1.go = "valet_4";
		break;
		
		case "valet_4":
			dialog.text = "Du... Bastard! Barbazon wird dafür bezahlen und dein Leben wird enden, Scheißfresser!";
			link.l1 = "Ha! Das habe ich erwartet. Mach dich bereit, Schurke!";
			link.l1.go = "valet_5";
		break;
		
		case "valet_5":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "vensan":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				dialog.text = "Charlie Prince? Was machst du hier? A-argh, verdammt, es warst du! Das ist alles deine Schuld!";
				link.l1 = "Beruhige dich, Bernie. Ich bin auf deiner Seite. Der Hinterhalt ist beseitigt, du und dein Schiff sind sicher.";
				link.l1.go = "vensan_8";
			}
			else
			{
				dialog.text = "Wer bist du, verdammt? Wie bist du hierher gekommen? Geh jetzt, mein Schiff ist vermint und die Bastarde am Ufer können es mit einem Schuss in die Luft jagen.";
				link.l1 = "Machen Sie sich keine Sorgen, Mister. Der Hinterhalt am Ufer wurde beseitigt. Ihr Schiff ist jetzt sicher, solange Sie natürlich nicht vorhaben, an Deck eine Pfeife anzuzünden. Wie ist Ihr Name?";
				link.l1.go = "vensan_1";
			}
		break;
		
		case "vensan_1":
			dialog.text = "Vincent. Bernard Vincent. Und wie ist dein Name?";
			link.l1 = "Kapitän "+GetFullName(pchar)+". Ich werde diese Seile durchschneiden und dich befreien...";
			link.l1.go = "vensan_2";
		break;
		
		case "vensan_2":
			LAi_SetStayType(npchar);
			dialog.text = "Oh... Danke sehr. Wie kann ich dir danken?";
			link.l1 = "Es ist noch nicht vorbei, Mister. Ist noch jemand von Ihrer Crew am Leben?";
			link.l1.go = "vensan_3";
		break;
		
		case "vensan_3":
			dialog.text = "Drei Dutzend meiner Männer sind im Laderaum eingesperrt...";
			link.l1 = "Lasst sie los und verschwindet sofort von hier. ";
			link.l1.go = "vensan_4";
		break;
		
		case "vensan_4":
			dialog.text = "Aber...";
			link.l1 = "Verschwende keine Zeit, Bernard. Du kannst mir später in La Vega danken... Tyrex könnte mir auch danken.";
			link.l1.go = "vensan_5";
		break;
		
		case "vensan_5":
			dialog.text = "Also, du bist nicht zufällig hier? Du wusstest über alles Bescheid?";
			link.l1 = "Ja, ich wusste es. Ich habe es geschafft, Jackmans Machenschaften und seine Pläne, Marcus zu töten, aufzudecken. Oh, bitte Tyrex, still zu sitzen, seine Einmischung könnte Jackman abschrecken.";
			link.l1.go = "vensan_6";
		break;
		
		case "vensan_6":
			dialog.text = "Ich werde es ihm sicher sagen! Gehst du jetzt?";
			link.l1 = "Ja. Und du solltest dich auch beeilen.";
			link.l1.go = "vensan_7";
		break;
		
		case "vensan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
			Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
			pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
			if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
				else sld = characterFromId("Helena");
				sld.dialog.currentnode = "sea_bomb"; 
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			sld = characterFromId("Cap_Vensan");
			sld.lifeday = 1;
			sld.DontDeskTalk = true;
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "vensan_8":
			dialog.text = "Wirklich? Sieh mal, es tut mir leid, Bruder...";
			link.l1 = "Vergiss es. Lass mich einfach die Seile durchschneiden und dich befreien.";
			link.l1.go = "vensan_9";
		break;
		
		case "vensan_9":
			LAi_SetStayType(npchar);
			dialog.text = "Verdammt... Ich fühle meine Hände nicht...";
			link.l1 = "Bernie, gibt es noch mehr Überlebende auf dem Schiff?";
			link.l1.go = "vensan_10";
		break;
		
		case "vensan_10":
			dialog.text = "Dreißig Männer sind im Laderaum eingesperrt...";
			link.l1 = "Lasst sie frei und verschwindet zur Hölle hieraus. Jetzt!";
			link.l1.go = "vensan_11";
		break;
		
		case "vensan_11":
			dialog.text = "Aber...";
			link.l1 = "Segle sofort nach La Vega. Erzähle Marcus alles über dieses Durcheinander in allen Einzelheiten.";
			link.l1.go = "vensan_12";
		break;
		
		case "vensan_12":
			dialog.text = "Hat Marcus dich geschickt?";
			link.l1 = "Er hat es nicht getan. Ich habe es geschafft, die Intrige eines Schurken aufzudecken. Er plante, Marcus durch diese Intrige auszuschalten. Bitte ihn, still zu bleiben und sich vorerst nicht einzumischen... Ich werde ihm später alles selbst erklären. Und bitte sag ihm, er soll nicht mehr sauer auf mich sein.";
			link.l1.go = "vensan_7";
		break;
		
 //--------------------------------------НПС по Завещанию Шарпа--------------------------------------------------
		// Устрица, Поль Моллиган
		case "molligan":
			dialog.text = "Was wollen Sie auf meinem Schiff, Mister?";
			link.l1 = "Guten Tag, Paul. Ihr Name ist Paul Molligan, nicht wahr?";
			link.l1.go = "molligan_0";
		break;
		
		case "molligan_0":
			dialog.text = "Ja, das bin ich. Wie kann ich Ihnen helfen?";
			link.l1 = "Mein Name ist "+GetFullName(pchar)+" und Jan Svenson hat mich geschickt.";
			link.l1.go = "molligan_1";
		break;
		
		case "molligan_1":
			dialog.text = "Jan? A-ah, ich erinnere mich an dich. Natürlich! Du hast sein Haus in letzter Zeit ständig besucht. Was also will Jan von mir?";
			link.l1 = "Sie waren in solch einer Eile, von Blueweld weg zu segeln. Jan wollte Ihr Schiff mit zusätzlichen zweihundert Zentnern Mahagoni beladen, um sie an Lord Willoughby in Bridgetown zu liefern. Machen Sie Ihr Schiff bereit, meine Männer werden das Mahagoni in Ihren Laderaum legen.";
			link.l1.go = "molligan_2";
		break;
		
		case "molligan_2":
			dialog.text = "Mahagoni? Hat Jan das gesagt? Hm. Und warum lieferst du es nicht selbst nach Barbados? Warum ich?";
			link.l1 = "Weil du dorthin segelst und ich nicht. Ich habe eine sofortige Aufgabe von Svenson, also kann ich meine Zeit nicht verschwenden, um auch nach Bridgetown zu segeln. Außerdem vertraut Jan mir nicht, Geschäfte mit Lord Willoughby zu machen, und er möchte, dass du das tust. Es tut mir leid. Jetzt lasst uns die Verladung machen, ich muss gehen.";
			link.l1.go = "molligan_3";
		break;
		
		case "molligan_3":
			dialog.text = "Hör zu, ich habe keinen freien Platz in meinem Frachtraum. Ich werde nicht in der Lage sein, das zu tun, was Jan von mir verlangt, obwohl ich es gerne würde.";
			link.l1 = "Kein Platz? Seltsam... Jan hat mir gesagt, dass ihr noch freien Platz hattet.";
			link.l1.go = "molligan_4";
		break;
		
		case "molligan_4":
			dialog.text = "Es ist wahr, aber Jan wusste nicht, dass ich die 'Auster' mit schwereren Kanonen ausgerüstet habe. Ich kann nicht mehr Fracht laden, als ich bereits habe. Also liefer das Holz selbst nach Barbados, hey Kumpel? Sag Jan, dass ich es nicht schaffen konnte. Mit Willoughby zu handeln ist einfach: sieh ihn einfach an, gib ihm die Fracht und nimm deinen Beleg. Einfach genug.";
			link.l1 = "Hm. Das war nicht mein Plan... Lassen wir mal in deinem Laderaum nachsehen, ja? Mein Quartiermeister ist sehr geschickt im Verpacken von Sachen, er wird in der Lage sein, die Waren in deinem Hold zu verstauen und dir sogar noch etwas freien Raum zu lassen...";
			link.l1.go = "molligan_5";
		break;
		
		case "molligan_5":
			dialog.text = "Kumpel, ich kann keine anderen Waren aufnehmen. Willst du, dass ich meine Kanonen wegwerfe und die 'Auster' ungeschützt lasse?";
			link.l1 = "Nun, wenn du dir so sicher bist... Aber Jan wird es nicht mögen, bedenke das!";
			link.l1.go = "molligan_6";
		break;
		
		case "molligan_6":
			dialog.text = "Ich werde es Svenson erklären, mach dir keine Sorgen. Schließlich ist es seine Schuld, er hat mich nicht nach der Tonnage meines Schiffes gefragt.";
			link.l1 = "Eh, und jetzt muss ich mit diesen Baumstämmen den ganzen Weg bis nach Barbados segeln, verdammt ... Lebewohl, Kumpel.";
			link.l1.go = "molligan_7";
		break;
		
		case "molligan_7":
			DialogExit();
			// ставим проверку скрытности
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10+hrand(50)))
			{
				pchar.questTemp.Saga.Molligan.friend = "true"; // будет шанс критического залпа картечью
				sTemp = "Der Schurke schöpft immer noch keinen Verdacht. Ich sollte näher herankommen und mit Kartätschenkugel auf ihn schießen. Ein plötzlicher Schlag wird immer in einem Kampf gewinnen. ";
				log_Testinfo("Friends");
				AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
				AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			}
			else
			{
				pchar.questTemp.Saga.Molligan.enemy = "true"; // нападет
				sTemp = "";
				log_Testinfo("Enemies");
				AddCharacterExpToSkill(pchar, "Sneak", 150);//скрытность
			}
			AddQuestRecord("Testament", "7");
			AddQuestUserData("Saga", "sText", sTemp);
			NextDiag.CurrentNode = "molligan_8";
			npchar.DontDeskTalk = true; // patch-5
		break;
		
		case "molligan_8":
			dialog.text = "Wir sind uns einig, oder?";
			link.l1 = "Ja, ja. Ich gehe zu meinem Schiff.";
			link.l1.go = "exit";
			NextDiag.TempNode = "molligan_8";
		break;
		
	//-----------------------------------------НПС по Теням прошлого--------------------------------------------
		// Джим Бенсон, плешивая мэгги
		case "benson":
			dialog.text = "Was willst du von mir? Ich mag keinen Klatsch und kein Glücksspiel. Und meinen Rum trinke ich alleine. Außerdem bin ich schlecht gelaunt nach meiner letzten Kreuzfahrt.";
			link.l1 = "Und was Besonderes ist während eurer letzten Kreuzfahrt passiert?";
			link.l1.go = "benson_1";
		break;
		
		case "benson_1":
			dialog.text = "Einer guter Mann vertraute mir und ich warf ihn über Bord, weil meine Mannschaft es verlangte.";
			link.l1 = "Und was war sein Fehler?";
			link.l1.go = "benson_2";
		break;
		
		case "benson_2":
			dialog.text = "Ich bin ein Neuling und kenne hier nicht viele Leute. Deswegen habe ich diesen gutmütigen dicken Mann als Chirurg eingestellt, ohne von seiner Vergangenheit zu wissen. Piraten haben uns verfolgt, seit wir Barbados verlassen haben. Warum sollten sie meine Eierschale brauchen?\nWir haben es gerade noch geschafft zu entkommen, dank eines starken Sturms. Hatten einen Schluck auf so einen Anlass. Und der dicke Narr dachte sich nichts Besseres aus, als allen zu erzählen, dass die Piraten wahrscheinlich ihn verfolgten, weil er der ehemalige Henker ist und Dinge weiß, die er nicht wissen sollte.\nNatürlich wurden meine Leute richtig wütend. Wie bitte?! Ein Henker an Bord, der als Chirurg dient! Und niemand wollte sich auch mit den Piraten anlegen... Also musste ich die arme Seele aus dem Schiff jagen. Es ist alles seine Schuld, er musste einfach seinen Mund aufmachen. Aber ich fühle mich schlecht für den Tölpel, er war ein ausgezeichneter Arzt. Es dauerte nur eine Minute, um meinen Kater zu heilen.";
			link.l1 = "Verdammt! Der Name deines Arztes war Raymond Baker, nicht wahr?";
			link.l1.go = "benson_3";
		break;
		
		case "benson_3":
			dialog.text = "Ja. Genau. Und wie wissen Sie das? Haben Sie mich verfolgt?";
			link.l1 = "Nein, das war nicht ich. Ich brauche nur diesen Mann, er ist ein großartiger Arzt. Wo habt ihr ihn gelandet?";
			link.l1.go = "benson_4";
		break;
		
		case "benson_4":
			dialog.text = "Breitengrad 15 Grad 28' Nord, Längengrad 63 Grad 28' West. Beeil dich, Mister! Er muss noch am Leben sein und du wirst die Schuld von mir nehmen, wenn du ihn rettest!";
			link.l1 = "Ich lichte bereits meine Anker!";
			link.l1.go = "benson_5";
		break;
		
		case "benson_5":
			DialogExit();
			NextDiag.CurrentNode = "benson_6";
			AddQuestRecord("Shadows", "3");
			npchar.lifeday = 0;
			bQuestDisableMapEnter = false;
			pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
			pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
			pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
			DeleteAttribute(pchar, "Cheats.SeaTeleport");
		break;
		
		case "benson_6":
			dialog.text = "Kapitän, beeilen Sie sich! Er muss noch am Leben sein!";
			link.l1 = "Ja, ja, ich bin auf dem Weg...";
			link.l1.go = "exit";
			NextDiag.TempNode = "benson_6";
		break;
		
	//---------------------------------------бандиты у джекмановского рудника-------------------------------
		case "mine_bandit":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "He! Bleib genau da! Beweg dich nicht. Dieses Gebiet ist gesichert!";
				link.l1 = "Sei nicht zu streng, Kumpel! Freunde! Jackman hat uns geschickt. Wir müssen zur Mine. Befehl des Meisters...";
				link.l1.go = "mine_attack";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "He! Bleib genau da! Beweg dich nicht. Dieses Gebiet ist gesichert!";
				link.l1 = "Hm. Aber ich will durch... Warum zum Teufel hältst du mich auf?";
				link.l1.go = "mine_bandit_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-ah, du schon wieder? Ich sehe, du verstehst es nicht... Jungs, Feuer!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_bandit_0":
			dialog.text = "Komm schon, beweg dich!";
			link.l1 = "Gut...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_bandit_0";
		break;
		
		case "mine_bandit_1":
			dialog.text = "Weil die Mine hinter mir Privatbesitz ist und ich hier bin, um jeden Fremden wie dich am Durchkommen zu hindern. Du solltest besser umkehren und diesen Ort verlassen, Fremder. Unsere Kanonen sind mit Kartätschenkugel geladen, nur noch ein Schritt und du wirst zu einer nassen Pfütze.";
			link.l1 = "Heh, ich sehe. Eure Mine hat eine ernsthafte Wache. Gut, ich gehe.";
			link.l1.go = "mine_bandit_exit";
			link.l2 = "Du, Schuft! Nun, wir werden sehen, wer zur Pfütze wird!";
			link.l2.go = "mine_bandit_2";
		break;
		
		case "mine_bandit_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;
		
		case "mine_bandit_2":
			dialog.text = "Ich gab dir eine Chance ... Jungs, Feuer!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_bandit_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;
		
		case "mine_banditx":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "He! Geh weg! Dieses Gebiet ist gesichert!";
				link.l1 = "He, beruhige dich, Kumpel! Jackman hat uns geschickt. Wir müssen zur Mine. Befehl des Meisters...";
				link.l1.go = "mine_attackx";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "He! Geh weg! Dieses Territorium ist gesichert!";
				link.l1 = "Hm. Und was ist dort?";
				link.l1.go = "mine_banditx_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-ah, du schon wieder? Ich sehe, dass du es nicht verstehst... Jungs, Feuer!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_banditx_1":
			dialog.text = "Das geht dich nichts an. Verschwinde, oder wir schießen, das schwöre ich!";
			link.l1 = "Beruhige dich. Ich gehe jetzt.";
			link.l1.go = "mine_banditx_exit";
			link.l2 = "Du, Schuft! Nun, wir werden sehen, wer wen erschießt!";
			link.l2.go = "mine_banditx_2";
		break;
		
		case "mine_banditx_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;
		
		case "mine_banditx_2":
			dialog.text = "Ich habe dir eine Chance gegeben... Musketen bereit! Feuer!!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_banditx_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;
		
		case "mine_attackx":
			dialog.text = "Wirklich? Dann müssen Sie das Passwort kennen. Sprich es aus, aber du wirst es bereuen, wenn du lügst...";
			link.l1.edit = 5;
			link.l1 = "";
			link.l1.go = "mine_attackx_1";
		break;
		
		case "mine_attackx_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[5]);
			if (sTemp == "neptune")
			{
				dialog.text = "Richtig. Aber du, Kumpel, bist von der falschen Seite hergekommen. Haben sie dich nicht gewarnt? Geh zurück und nimm den linken Pfad vom trockenen Brunnen. Dann umrunde den Hügel und dort wirst du das Haupttor sehen.";
				link.l1 = "Kann ich hier nicht eintreten?";
				link.l1.go = "mine_attackx_2";
			}
			else
			{
				dialog.text = "Jungs, wir haben einen Spion! Muskete bereit! Feuer!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_attackx_2":
			dialog.text = "Nein. Nur durch den zentralen Eingang.";
			link.l1 = "In Ordnung, Kumpel... Hey! Schau mal! Was zum Teufel ist das da oben auf der Palisade?";
			link.l1.go = "mine_attackx_3";
		break;
		
		case "mine_attackx_3":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;
		
		case "mine_attack":
			dialog.text = "Wirklich? Du solltest dann das Passwort wissen. Sprich es aus, damit ich es hören kann. Und wenn du versuchst, mich zu täuschen, wird das der letzte Scherz sein, den du in deinem Leben auf jemanden spielst.";
			link.l1.edit = 5;
			link.l1 = "";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[5]);
			if (sTemp == "neptune")
			{
				dialog.text = "Richtig. Geh weiter. Der Lagerleiter ist im Haus links vom Eingang der Mine. Geh und besuche ihn.";
				link.l1 = "Gut, Kumpel...";
				link.l1.go = "mine_attack_2";
			}
			else
			{
				dialog.text = "Jungs, wir haben einen Schnüffler! Kanonen, Feuer frei!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_attack_2":
			DialogExit();
			NextDiag.CurrentNode = "mine_attack_3";
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;
		
		case "mine_attack_3":
			dialog.text = "Was noch? Hast du etwas vergessen?";
			link.l1 = "Ja. Man bat mich, Ihnen die besten Grüße zu übermitteln.";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "Zu mir? Ha-ha! Von wem?";
			link.l1 = "Jan Svenson, du Bastard!";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			DialogExit();
			LAi_SetPlayerType(pchar);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Mine_bandit_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			if (pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetActorType(sld);
				LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
				LAi_ActorAnimation(sld, "shot", "Saga_MineBanditDie", 1.0);
			}
			else
			{
				for (i=1; i<=6; i++)
				{
					sld = characterFromId("Mine_bandit_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "Saga_BanditsDestroyed");
				AddDialogExitQuest("MainHeroFightModeOn");	
			}
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "NPC_Death";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.character = "Mine_bandit_1";
			pchar.quest.Saga_MineAttack_07.win_condition.l2 = "NPC_Death";
			pchar.quest.Saga_MineAttack_07.win_condition.l2.character = "Mine_bandit_2";
			pchar.quest.Saga_MineAttack_07.function = "Saga_SvensonMineexitAttack";
		break;
		
	// ----------------------------- диалоги НПС при штурме бандитского рудника -------------------------------
		case "Svensons_off":
			dialog.text = LinkRandPhrase("Wir werden diese Bastarde auseinanderreißen!","Ich freue mich darauf, diesen Abschaum zu besiegen!","Die Schergen von Jackman haben kein Recht, in der Westlichen Hauptstraße zu sein! Wir werden sie von hier vertreiben!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_off";
		break;
		
		case "Svensons_sold":
			dialog.text = LinkRandPhrase("Wir sind bereit zu kämpfen!","Wir werden es ihnen zeigen!","Sie wissen nicht einmal, mit wem sie sich anlegen!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_sold";
		break;
		
		case "gunner":
			PlaySound("Voice\English\evilpirates01.wav");
			dialog.text = "Kommandant, die Kanone ist bereit. Sie wurde mit einer Bombe geladen, genau wie Sie es befohlen haben.";
			link.l1 = "Ich nehme an, dass niemand uns hier erwartet... Zeit, uns vorzustellen. Jan hat mir gesagt, dass ihr Lager hinter diesem Hügel ist. Wirst du es erreichen können?";
			link.l1.go = "gunner_0_1";
		break;
		
		case "gunner_0_1":
			dialog.text = "Leicht genug, Kommandant. Lassen Sie uns das Fass ein wenig anheben, das sollte es tun... erledigt.\nMach dich bereit!.. Feuer!!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "1";
		break;
		
		case "gunner_0_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_1":
			dialog.text = "";
			link.l1 = "Hm. Randolf, denkst du, wir haben etwas getroffen? Ich würde gerne deine Meinung hören.";
			link.l1.go = "gunner_1_1";
		break;
		
		case "gunner_1_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Befehlshaber, wir haben etwas oder jemanden getroffen, aber ich kann nicht genauer sein... dieser verfluchte Hügel blockiert die Sicht. Ich werde den Winkel ändern.\nBereit! Feuer!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			dialog.text = "Ha! Schau, Kommandant! Dort ist Rauch! Verdammt, wir müssen den Stall eines Banditen getroffen haben! Hurra-ah!";
			link.l1 = "Ja, ich sehe den Rauch... Zweifellos schon ein epischer Sieg. Lade das Gewehr nach und richte es auf den Weg, es sieht so aus, als ob unsere Gäste kommen. Wir werden sie angemessen begrüßen!";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Aye-aye, Kommandant! Ladet eine Bombe! Geschützbesatzung bereit! Zündschnur bereit! Feuert auf mein Kommando!";
			link.l1 = "...";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			PlaySound("Voice\English\evilpirates05.wav");
			dialog.text = "Ha-ha, das muss weh tun!";
			link.l1 = "Entspannt euch noch nicht! Ladet die Kanone! Ich glaube nicht, dass sie genug hatten. Es kommen noch mehr!";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");//
			dialog.text = "Aye-aye, Kommandant! Ladet eine Bombe! Bereit! Feuert auf mein Kommando!";
			link.l1 = "...";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("types\warrior04.wav");
			PlaySound("Voice\English\evilpirates06.wav");
			dialog.text = "Ha-ha-ha, die Bastarde haben uns den Rücken gezeigt! Hundsfleisch! Kartätschenkugel zerschmettert sie auf solche Entfernung! Es scheint, sie haben nicht genug Mut, uns erneut anzugreifen!";
			link.l1 = "Nun ist es an uns. Randolph, du bleibst hier in der Nähe der Kanone. Schieß ein paar Mal auf den Pfad und dann ziele auf den Rauch - brenne ihr Versteck nieder! Schieß uns nur nicht.";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Aye-aye, Kommandant! Macht die Kanone bereit! Ladet eine Bombe!";
			link.l1 = "Männer! Zu den Waffen! Folgt mir, greift an! Hurra!!";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					if (i == 1) sld.MusketerDistance = 10; 
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// запускаем автобабахалку на 10 выстрелов
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;//разлочим интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = LinkRandPhrase("Tut mir nicht weh, ich bin nicht einer von ihnen! Tötet die Banditen!","Befreie uns, Kumpel! Und töte sie alle!","Schnetzle sie, Freund, schnetzle sie! Mach sie tot!");
				link.l1 = "Ha! Mach dir keine Sorgen, genau das tun wir gerade.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Ist unsere Sklaverei vorbei? Wirst du uns befreien?","Heh, habe ich es wirklich geschafft, diesen Tag zu erleben?","Diese Bastarde haben uns all unser Blut abgezapft....");
				link.l1 = "Ich denke, dass du deine Freiheit bald genießen kannst, Kumpel...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// жена Яна Свенсона
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Sie sollten diesen Ort besser verlassen, Mister. Wir decken keine Verbrecher und wir brauchen keine Konflikte mit den Autoritäten der Kolonie.";
				link.l1 = "Gut, ich gehe jetzt...";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				// Первый диалог с Элен
				if(startHeroType == 4)
				{
					dialog.text = "Ach, Helen. Du hättest dich ein bisschen anständiger kleiden können, bevor du zu Jan gekommen bist, anstatt ihm zu zeigen, wie du wirklich bist. Schade, dass er mir nicht glaubt.";
					link.l1 = "Und wie genau bin ich? Er hat mir seit meiner Kindheit geholfen und kennt mich besser als jeder andere. Ich habe keine Geheimnisse vor ihm. Ich leide seit meiner Kindheit unter dieser Hitze, also musste ich es auf meine Weise bewältigen, das ist alles.";
					link.l1.go = "js_helen_ft";
					NextDiag.TempNode = "js_girl";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.text = TimeGreeting()+", Mister. Möchten Sie Jan sehen?";
				link.l1 = "Guten Tag. Es war schön, Sie kennenzulernen, Fräulein?..";
				link.l1.go = "js_girl_1";
			}
			else
			{
				// заглушка элен
				if(startHeroType == 4)
				{
					dialog.text = "Jan ist drinnen. Geh schon, hier gibt es nichts zu sehen, und du gehst mir auf die Nerven.";
					link.l1 = "Hatte sowieso keine große Lust.";
					link.l1.go = "exit";
					NextDiag.TempNode = "js_girl";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Joan")) {
					dialog.text = "Grr!";
					link.l1 = "Und Ihnen auch gute Gesundheit, Miss Svensson.";
					link.l1.go = "exit";
					break;
				}
				
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
				{
					dialog.text = TimeGreeting()+", Kapitän "+GetFullName(pchar)+". Wenn Sie wegen Jan hier sind, muss ich Sie enttäuschen - er ist nicht hier. Er führt gerade einige wichtige Geschäfte durch.";
					link.l1 = "Verdammt! Und ich brauche ihn! Sagen Sie mir, Miss Svenson, hat er Ihnen gesagt, wann er zurück sein wird?";
					link.l1.go = "js_girl_3";
					break;
				}
				dialog.text = "A-ah, du schon wieder, Kapitän "+GetFullName(pchar)+"... geh weiter, Jan ist wie gewohnt oben.";
				link.l1 = "Danke, Miss Svenson...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "Miss, Miss Johanna Svenson.";
			link.l1 = "Kapitän "+GetFullName(pchar)+".";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = "Kapitän? Nun, ich freue mich, Sie in meinem Haus willkommen zu heißen. Aber wenn Sie wegen Jan hier sind, muss ich Sie enttäuschen - er ist nicht hier. Er ist unterwegs, um wichtige Geschäfte zu erledigen.";
				link.l1 = "Verdammt! Und ich brauche ihn! Sagen Sie mir, Miss Svenson, hat er Ihnen gesagt, wann er zurückkommt?";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "Kapitän? Nun, ich freue mich, Sie in meinem Haus willkommen zu heißen. Mein Mann ist im zweiten Stock in seinem Büro. Geh nach oben.";
			link.l1 = "Ich habe es verstanden, Miss Svenson...";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "Nein. Er hat mir nicht einmal das genaue Datum seiner Rückkehr gesagt, weil er selbst nicht weiß, wie lange die Suche dauern wird.";
			link.l1 = "Es tut mir leid, dass ich störe, aber ich brauche ihn wirklich... Welche Suche führt er durch?";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "Ich werde es Ihnen sagen. Die liebliche Helen, auch bekannt als Rumba, Tochter seines verstorbenen Freundes Sean McArthur, ist verschwunden. Jan behandelt die junge Teufelin als wäre sie seine eigene Tochter. Sie erinnert ihn an seine alte Liebe, die denselben rücksichtslosen Charakter hatte. Das ist zumindest der Grund für die Anziehung, denke ich.\nWie auch immer, das Mädchen verschwand vor einer Woche zusammen mit ihrer Schoner 'Regenbogen' und seiner gesamten Besatzung. Sean McArthur lehrte sie Seemannschaft und der 'Regenbogen' wurde ihr durch sein Testament übergeben. Und jetzt spielt sie Kapitänin...";
			link.l1 = "Was könnte ihr passiert sein?";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "Wer weiß... Eine Woche ist nicht so lang, aber die Witwe McArthur ist überzeugt, dass ihrer Tochter etwas passiert ist und sie hat es geschafft, Jan davon zu überzeugen. Er hat seine Männer zusammengerufen und hat selbst angefangen, nach ihr zu suchen, bisher ohne Erfolg. Persönlich glaube ich, dass Helen in Ordnung ist und Jan sich grundlos quält.\nEr hat zu sehr auf den Unsinn dieser alten, fetten Frau gehört und ist in Panik geraten. Wahrscheinlich amüsiert sich das Mädchen gerade mit einem anderen Freund, weit weg von den Augen der Leute an einem sicheren Ort. Sie wird zurückkommen, sobald ihr Hunger gestillt ist.";
			link.l1 = "Johanna, wo kann ich Gladys finden? Ich möchte mit ihr sprechen...";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "Ihr Haus ist in der Nähe des Piers, auf der linken Seite. Aber sie ist wahrscheinlich nicht dort. Sie vergeudet jeden Tag damit, auf den Mauern des Forts zu stehen und nach ihrer wertvollen Tochter zu suchen.";
			link.l1 = "Ich verstehe. Vielen Dank für Ihre Informationen!";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); //устанавливаем Глэдис на форт
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "js_girl_8":
			dialog.text = "Jan ist noch nicht da, Kapitän, also komm später zurück.";
			link.l1 = "Ich sehe...";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		case "js_helen_ft":
			dialog.text = "Du bist immer brünstig, Ich würde sagen. Du solltest in die Kirche gehen, ich habe dich kaum je dort gesehen.";
			link.l1 = "Mein Gewissen ist rein - ich habe nichts um Vergebung zu bitten. Noch immer bitter, dass er geholfen hat, mein Schiff zu versorgen, anstatt ein weiteres Kleid für dich, Joanna, zu kaufen?";
			link.l1.go = "js_helen_ft_1";
		break;
		
		case "js_helen_ft_1":
			dialog.text = "Ich? Verbittert? Du bist es nicht wert. Es ist nur so, dass dir alles zu leicht kommt und du es nicht verdienst.";
			link.l1 = "Aber sobald ich dieses Schiff hatte, begann ich, mein eigenes Geld zu verdienen. Und seitdem er dich wie eine streunende Katze aufgelesen hat, hast du keinen Tag gearbeitet. Also, wer lebt wirklich auf seine Kosten?";
			link.l1.go = "js_helen_ft_2";
		break;
		
		case "js_helen_ft_2":
			dialog.text = "Rede weiter so, und eines Tages wird dir das zustoßen, was du verdienst. Jan und Gladys hätten dir Manieren beibringen sollen. Nun gut, sprich aus, was du zu sagen hast - und verschwinde aus meinen Augen, Helen. Er ist drinnen.";
			link.l1 = "Dumme Henne. Klar, wird gemacht.";
			link.l1.go = "exit";
		break;
		
		// хронометр Алекса
		case "Alexs_bandos":
			dialog.text = "He! Was machst du hier?";
			link.l1 = "Ich würde euch dasselbe fragen - was macht ihr und eure Kameraden hier, in meinem Kerker?";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "Ha! Dein Kerker? Und wann wurde er deins, du Tunte?";
			link.l1 = "Der Tag, an dem dein Vater den Fehler machte, deine Mutter zu ficken.";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "Suchst du Ärger?";
			link.l1 = "Hör zu, Kumpel, ich gebe dir eine letzte Chance, diesen Ort zu verlassen. Das ist mein Verlies und ich lasse niemanden frei hier herein tanzen, hast du das verstanden? Ich muss nur einmal pfeifen, und die Hälfte der Piraten von Isla Tesoro wird innerhalb einer Minute hier sein.";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "Nun, wir werden versuchen, dein Maul zu stopfen!";
			link.l1 = "Ha-ha! Du bist erbärmlich, Abschaum!";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Alexs_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "helendrinking_gypsy":
			dialog.text = "Halt einen Moment, Falke!";
			link.l1 = "Nicht die beste Zeit, Liebling.";
			link.l1.go = "helendrinking_gypsy_1";
		break;
		
		case "helendrinking_gypsy_1":
			dialog.text = "Oh, du irrst dich, Hübscher. Dieses Mädchen mag dich und das Gefühl ist gegenseitig, ich kann es sehen.";
			link.l1 = "Nicht die beste Empfehlung... Also, was willst du? Eine milde Gabe?";
			link.l1.go = "helendrinking_gypsy_2";
		break;
		
		case "helendrinking_gypsy_2":
			dialog.text = "Ich möchte Ihnen Unterstützung in Ihrem herausfordernden Unterfangen anbieten. Schau hier! Ein magischer Becher und eine verbotene Salbe. Der Becher wird Ihnen in Trinksachen helfen, und die Salbe - in Liebesangelegenheiten. Was werden Sie wählen? Nur zweitausend!";
			link.l1 = "Ich brauche nichts - Ich habe deiner Sorte schon einen Haufen Silber gegeben.";
			link.l1.go = "helendrinking_gypsy_refuse";
			if (sti(pchar.money) >= 2000) {
				link.l2 = "Verbotene Salbe, sagst du? Nun, ich bin kein Heiliger, das gebe ich zu. Gib sie her.";
				link.l2.go = "helendrinking_gypsy_fuck";
				link.l3 = "Einen Krug? Sehe ich aus wie ein Säufer? Nun, wer will ich hier täuschen... Ich nehme ihn!";
				link.l3.go = "helendrinking_gypsy_drink";
			}
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_refuse":
			dialog.text = "Schön, aber dumm. Flieg dann weg, Falke.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_drink":
			dialog.text = "Oh, versteck es nicht in deinen bodenlosen Taschen! Fliege weg, Falke, und sündige nicht!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_01");
			Log_Info("Talisman 'Throat of cast iron' acquired!");
			PlaySound("interface\important_item.wav");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_fuck":
			dialog.text = "Oh, versteck es nicht in deinen bodenlosen Taschen! Flieg weg, Falke, und sündige nicht!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_03");
			Log_Info("Talisman 'Cupid's Balm' acquired!");
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Helen disapproves", "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_joan":
			dialog.text = "Ach! Verschwinde hier, du Schuft! Wie oft habe ich dir gesagt, dass du nicht in mein Haus klettern sollst! Und wer ist das?";
			link.l1 = "Miss, wir kennen uns bereits.";
			link.l1.go = "helendrinking_joan_1";
		break;
		
		case "helendrinking_joan_1":
			dialog.text = "Monseigneur de Maure? Nun, das ist ja herrlich! Ist das Ihre Art, Geschäfte mit meinem Mann zu führen?! Ich wusste es! Ich habe Jan gewarnt: Eines Tages wird diese Dirne anfangen, ihre Männer in die Irre zu führen! Und was haben Sie in Ihren Händen?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog1");
		break;
		
		case "helendrinking_joan_2":
			dialog.text = "Was?! Wie kannst du es wagen, Schuft?! Du gehst nirgendwo hin; mein Mann wird jeden Moment hier sein und dir beibringen, wie man mit den Ältesten spricht!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog3");
		break;
		
		case "helendrinking_fort_officer":
			dialog.text = "Was passiert hier? Fräulein MacArthur! Ich hatte großen Respekt vor Ihrem Vater, und Mister Svensson ist unser Freund... Aber erinnern Sie sich nicht, wie es das letzte Mal geendet hat?\nEs ist enttäuschend, Offizierswort, enttäuschend! Sie hätten uns einladen können!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog");
		break;
		
		case "helendrinking_fort_officer_1":
			dialog.text = "Vielen Dank für Ihre Gastfreundschaft, Miss MacArthur. Lassen Sie mich sagen, dass wir alle sehr froh sind, Sie zurück zu sehen. Was passiert ist, bleibt ein großes Rätsel, aber es ist nicht überraschend, dass das Dorf davon weiß. Dennoch kann ich Ihnen versprechen, dass niemand klatschen wird. Ich entschuldige mich aufrichtig für das jüngste Verhalten eines unserer Kapitäne. Und ich möchte Ihnen speziell, Mister de Maure, danken.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog3");
		break;
		
		case "helendrinking_fort_officer_2":
			dialog.text = "Alles wird gut, Fräulein. Mister de Maure, ich werde ehrlich sein - trotz Donovans Verhalten wie ein wahrer Schurke und Bandit, wird die Flotte ihn niemals offen verurteilen. Wahrscheinlicher ist, dass sie ihn sogar verteidigen werden. Ihre kleine Expedition hat es in die Berichte geschafft und die Beziehungen zwischen unseren Ländern erheblich kompliziert. Trotzdem, in Anbetracht des Einflusses von Mister Svensson und der bemerkenswerten Zugeständnisse, die Ihnen von Capsterville gemacht wurden, haben Sie nichts zu befürchten.";
			link.l1 = "Das ist prächtig. Ich sage, wir trinken darauf!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog1");
		break;
		
		case "helendrinking_poorman":
			dialog.text = "Entschuldigen Sie bitte, was ist mit der Arbeit?";
			link.l1 = "Bist du immer noch hier?";
			link.l1.go = "helendrinking_poorman_1";
		break;
		
		case "helendrinking_poorman_1":
			dialog.text = "Lieber Herr, wohin soll ich sonst gehen? Ich bin nur mal kurz verschwunden, um mich zu erleichtern, habe euer sentimentales Gespräch belauscht und bin etwas aufgewärmt. Emotional, meine ich!";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.BoughtRainbow")) {
				link.l1 = "Guter Herr! Nun, da ich Ihnen mein Wort gegeben habe, kann es nicht helfen. Geh, übernimm das Kommando.";
				link.l1.go = "helendrinking_poorman_bought";
			} else {
				link.l1 = "Ich habe keine Arbeit für Sie, Mister.";
				link.l1.go = "helendrinking_poorman_notbought";
			}
		break;
		
		case "helendrinking_poorman_bought":
			dialog.text = "Aye aye, Kapitän!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helendrinking_poorman_notbought":
			dialog.text = "Schade! Trotzdem, danke für den Leckerbissen, Kapitän!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helensleep_amelia_mary":
			dialog.text = "In nomine Patris et Filii et Spiritus Sancti... komm rein, mein Sohn.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Hallo, Mutter Amelia. Wirst du mich auch anschreien?";
				link.l1.go = "helensleep_amelia_mary_know";
			} else {
				link.l1 = "Verschwinde! Was für ein Albtraum ist das? Was passiert? Träume ich?";
				link.l1.go = "helensleep_amelia_mary_notknow";
			}
		break;
		
		case "helensleep_amelia_mary_know":
			dialog.text = "Nein, mein kleiner Falke. Und vergib Jan - der arme Mann hat sich aufgeregt. Aber ja, ich möchte dich tadeln. Warum bist du zur Kirche gekommen? Um deine Sünden zu bereuen? Oder war es die Rothaarige, die du gesucht hast?";
			link.l1 = "Das weiß ich selber nicht...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Hast du sie auch gesehen? Sie hat mein Auge gefangen.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_mary_notknow":
			dialog.text = "Verschwinde. Wir hätten uns schon längst treffen sollen, aber du zögerst alles hinaus. Warum bist du zur Kirche gekommen? Um dich für deine Sünden zu bereuen? Oder warst du hinter der Rothaarigen her?";
			link.l1 = "Das weiß ich selber nicht...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Hast du sie auch gesehen? Sie hat mein Auge gefangen.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen":
			dialog.text = "Guten Morgen, mein Falke. Der Empfang hat noch nicht begonnen, bitte warte in der Reihe.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Hallo, Eure Exzellenz. Werden Sie mich auch anschreien?";
				link.l1.go = "helensleep_amelia_helen_know";
			} else {
				link.l1 = "Verschwinde! Was für ein Albtraum ist das? Was passiert hier? Träume ich?";
				link.l1.go = "helensleep_amelia_helen_notknow";
			}
		break;
		
		case "helensleep_amelia_helen_know":
			dialog.text = "Nein, mein Falke. Und verzeih Jan, der arme Mann hat sich aufgeregt. Du brauchst nicht zu schimpfen, du hast alles richtig gemacht - du bist der Rothaarigen nicht bis zur Kirche gefolgt. Braver Junge!";
			link.l1 = "Es ist nett, gelobt zu werden. Besonders wenn klar ist, wofür.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Hast du sie auch gesehen? Sie hat mein Auge gefangen.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen_notknow":
			dialog.text = "Verschwinde. Wir hätten uns schon treffen sollen, aber du ziehst alles in die Länge. Komm her, ich werde dich loben - bist der rothaarigen nicht zur Kirche gefolgt. Braver Junge!";
			link.l1 = "Es ist schön gelobt zu werden. Besonders wenn klar ist, wofür.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Hast du sie auch gesehen? Sie hat mein Auge gefangen.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia":
			dialog.text = "Ich werde dich nicht mit Details belästigen, Dummkopf, aber das werde ich dir sagen: du bist dazu bestimmt, eine großartige Person zu sein. Du wirst viel Übel anrichten, doch noch viel mehr Gutes. Aber Glück ist dir nicht garantiert. Glück, mein Falke, wird nur denen gegeben, die ihren Weg gehen und nicht abweichen. Und eine treue Frau wird dir helfen, nicht abzuweichen.\nDu wirst zwei von ihnen haben, und beide werden Glück bringen, aber du musst die blondhaarige wählen.";
			link.l1 = "Wieso sollte das so sein? Ich entscheide selbst!";
			link.l1.go = "helensleep_amelia_1";
		break;
		
		case "helensleep_amelia_1":
			dialog.text = "Natürlich, wähle selbst, aber der Blonde ist besser. Wir haben es so entschieden.";
			link.l1 = "Wer ist 'wir'?";
			link.l1.go = "helensleep_amelia_2";
		break;
		
		case "helensleep_amelia_2":
			dialog.text = "Der Unglückliche kennt nicht einmal ihren wahren Namen. Rufe ihn, und sie wird dein sein. So sagt man.";
			link.l1 = "Ich verstehe überhaupt nichts mehr.";
			link.l1.go = "helensleep_amelia_3";
		break;
		
		case "helensleep_amelia_3":
			dialog.text = "Hörst du das Klopfen? Öffne, und mach keinen Fehler.";
			link.l1 = "Tatsächlich, jemand klopft... Herein!";
			link.l1.go = "exit";
			
			PlaySound("interface\knock.wav");
			
			AddDialogExitQuestFunction("HelenSleep_WakeUp");
		break;
		
		case "helendrinking_notifier":
			dialog.text = "Monsieur, Mister Svensson hat darum gebeten, dass Sie ihm ein wenig Ihrer Zeit schenken.";
			link.l1 = "Verdammt, das verheißt nichts Gutes. Ich werde es versuchen, aber ich mache keine Versprechungen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_End");
		break;
		
		case "islatesoro_pirate1":
			dialog.text = "Glücklicher Tag, Jungs! Hab ich euch gesagt, dass sie früher oder später hierher kommen würde, nicht wahr? Also, Schätzchen, übergib die Waffen und komm mit uns.";
			link.l1 = "Sie haben es falsch verstanden, Leute. Sie ist mit mir.";
			link.l1.go = "islatesoro_pirate1_1";
		break;
		
		case "islatesoro_pirate1_1":
			dialog.text = "Bleib da raus, oder ich schieße dich nieder wie einen Hund. Es gibt eine gute Summe für das Mädchen, und wir sind hungrige Kerle, ohne Prinzipien.";
			link.l1 = "Rede weiter so mit mir, und ich werde dein Hungerproblem dauerhaft lösen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroSpawnSecond");
		break;
		
		case "islatesoro_pirate1_2":
			dialog.text = "Hast du den Verstand komplett verloren, Lucky? Wir haben sie zuerst gefunden! Du hast besser einen guten Grund, dein dämliches Maul gegen mich aufzureißen!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog1");
		break;
		
		case "islatesoro_pirate1_3":
			dialog.text = "Du bist hier die Ratte! Wir haben gerade einen dicken, fetten Spanier in Stücke gerissen; wir können ein Jahr lang auf unseren Ärschen sitzen!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog3");
		break;
		
		case "islatesoro_pirate2":
			dialog.text = "Nun, schau mal wer wir hier haben. Also gut, alle anderen, macht Platz, und Sie, gnädige Frau, kommen Sie mit uns.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog");
		break;
		
		case "islatesoro_pirate2_1":
			dialog.text = "Wir sind in der Überzahl und wir sind härter, Däne. Welchen anderen Grund brauchst du noch, du Bilgenratte? Es sind sechs Monate vergangen, seit du einen anständigen Fang gesehen hast, und du hast Brotkrumen von Vuazies Tisch gegessen!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog2");
		break;
		
		case "islatesoro_pirate2_2":
			dialog.text = "";
			link.l1 = "Sieht so aus, als würde es hier keine friedliche Lösung geben.";
			link.l1.go = "islatesoro_pirate_a";
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB")) {
				link.l2 = "Was hast du gesagt? Glücklich? Ich habe ein Gerücht gehört, dass er und Vuazie sich verschworen haben, um dir zweifelhafte Tipps zu geben. Das erklärt deine Pechsträhne auf See.";
				link.l2.go = "islatesoro_pirate_b";
			}
			bOk = (!CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice")) || (pchar.questTemp.Mtraxx.Retribution.Choice == "bad");
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC") && CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold") && bOk) {
				link.l3 = "Ich bin es leid, dieses Farce. Isla Tesoro, hört mir zu! Wer war mit mir in Cartagena?! Wer hat Merida mit mir verbrannt?! Diese Ratten wagen es, sich an Charlie Prince selbst heranzumachen! Lasst uns ihnen zeigen, Jungs!";
				link.l3.go = "islatesoro_pirate_c";
			}
		break;
		
		case "islatesoro_pirate_a":
			dialog.text = "Du bist immer noch hier, Qualle? Gut, Jungs, los geht's: bindet den Kapitän fest, und wir kümmern uns später um das Mädchen, verstanden?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog4");
		break;
		
		case "islatesoro_pirate_a_1":
			dialog.text = "Sicher, lass uns zumindest etwas Blut vergießen. Hehe.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroA");
		break;
		
		case "islatesoro_pirate_b":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedB = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 60) {
				dialog.text = "Was?! Teufel, ich wusste, dass du mit diesem bebrillten Schurken unter einer Decke steckst! Zerschneidet sie alle, Jungs, und wir holen das Mädchen später ab!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroB");
			} else {
				dialog.text = "Was faselst du da, Kapitän? Verzieh dich, während die ehrbaren Leute Geschäfte besprechen.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "islatesoro_pirate_c":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedC = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 50) {
				DialogExit();
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroC");
			} else {
				dialog.text = "Wovon faselst du, Kapitän? Ich habe Charlie Prince gesehen, und du kommst ihm nicht gleich. Verzieh dich, während die anständigen Leute Geschäfte besprechen.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "francois":
			dialog.text = "Charles de Maure? Sohn von Henri de Monpe?";
			link.l1 = "Das ist korrekt, Monsieur. Und wer sind Sie?";
			link.l1.go = "francois_1";
		break;
		
		case "francois_1":
			dialog.text = "Colonel Francois de Tavanne. Betrachten Sie dies als eine direkte Herausforderung, Monsieur; der Fehdehandschuh für das Duell ist gelegt. Ich möchte mir nicht einmal die Hände mit Euch schmutzig machen, aber ich schwöre, meine Klinge wird Euer Blut kosten!";
			link.l1 = "Ein Duell? In diesem Fall müssen Sie sich viel mehr anstrengen, Oberst. Im Moment könnten Sie nur für einen Banditen gehalten werden, und in diesen Teilen ist das Gespräch mit ihrer Art kurz! Erklären Sie sich!";
			link.l1.go = "francois_2";
		break;
		
		case "francois_2":
			dialog.text = "Sie haben meine Frau verführt, Monsieur! Während ich Blut für König und Vaterland vergoss, haben Sie... Sie haben sich mit meiner Frau vergnügt!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog");
		break;
		
		case "francois_3":
			dialog.text = "Schweigen Sie, Madame. Ihre kühne Kleidung entehrt die Ehre jeder Frau, obwohl Sie neben diesem unwürdigen Verführer einer edlen Frau ganz passend scheinen!";
			link.l1 = "Noch immer kein ausreichender Grund für ein Duell, Oberst. Und darf ich darauf hinweisen, dass Sie sich hier genauso unwürdig verhalten.";
			link.l1.go = "francois_4";
		break;
		
		case "francois_4":
			dialog.text = "Ist das nicht genug? Ich habe nachgefragt - an meiner Stelle könnten jetzt ein Dutzend noble Ehemänner sein, Mister. Aber wenn Sie die Details wollen, dann gestehe ich zu meiner Schande, dass eine Ihrer Leidenschaften Lulu de Tavann war, die schönste und ehrlichste der Frauen!";
			link.l1 = "Lulu, sagst du... Und wie geht es ihr?";
			link.l1.go = "francois_5";
		break;
		
		case "francois_5":
			dialog.text = "Schweig! Meine Frau konnte die Qual, die du ihr zugefügt hast, nicht mehr ertragen und ist kürzlich gestorben! Fast ein Jahr und ein Vermögen habe ich damit verbracht, dich, Schurke, zu finden! Genug der Worte! Nimm die Herausforderung an, oder ich bringe dich um wie einen Hund. Richard! Sei mein Zeuge!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog2");
		break;
		
		case "francois_6":
			dialog.text = "Schweigen Sie, Mister! Nehmen Sie die Herausforderung an oder verlieren Sie jegliche Reste von Ehre, die Sie noch haben könnten!";
			if (pchar.HeroParam.HeroType == "HeroType_1") {
				link.l1 = "Ein Duell ist ein Duell. Ich werde nicht lügen, ich genieße diese. Kapitän, übermitteln Sie dem Oberst, dass es an der Zeit ist, einen passenden Sarg zu bestellen.";
			} else {
				link.l1 = "Möchtest du einen Kampf? Du wirst einen bekommen! Kapitän, teile dem Oberst mit, dass es Zeit für ihn ist, einen passenden Sarg zu bestellen.";
			}
			link.l1.go = "francois_duel";
			link.l2 = "Das ist nicht Europa, Oberst. Ehre in der Karibik ist schwerer zu verdienen, aber auch nicht so leicht zu verlieren. Ich lehne Ihr Duell ab, weil ich es einfach nicht will.";
			link.l2.go = "francois_refuse";
		break;
		
		case "francois_7":
			dialog.text = "Dein Vater ist bereits einen Schritt vom Grab entfernt, du Abschaum! Und ich werde dafür sorgen, dass er von deiner Feigheit erfährt!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog7");
		break;
		
		case "richard":
			dialog.text = "Oberst, ich bestätige Ihr Recht auf ein Duell, aber ich werde nicht einfach Banditentum erlauben! Monsieur de Maure, ich bin Kapitän Richard Small. Sind Sie bereit, Oberst de Tavann Genugtuung zu leisten?";
			link.l1 = "Einen Moment, Kapitän. Ich kannte Lulu gut... und sie... neigte dazu, ihre Verehrer häufig zu wechseln, und ihre Gesundheit war besser als meine... Wie ist sie gestorben, Oberst? Vor oder nach Ihrer Heimkehr?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog3");
		break;
		
		case "richard_1":
			dialog.text = "Bitte, Francois, erlaube mir. Monsieur de Maure, Sie wurden herausgefordert. Die Offiziersgesellschaft von Blueweld hat anerkannt, dass Colonel de Tavanns Forderung nach Genugtuung gerechtfertigt ist. Akzeptiere die Herausforderung oder verliere deine Ehre.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog5");
		break;
		
		case "richard_2":
			dialog.text = "Charles, bitte, wir sind hier Adlige. Es ist unangebracht. Der Oberst ist so weit gereist, um dich zu treffen! Es ist ein Skandal!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog8");
		break;
		
		case "richard_3":
			dialog.text = "J-ja, natürlich, Fräulein. Aber ich werde...";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "helen");
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath1");
		break;
		
		case "richard_4":
			dialog.text = "Kapitän de Maure, der Tag gehört Ihnen! Nicht der korrekteste Kampf, aber Sie haben heute Ihre Ehre verteidigt.";
			link.l1 = "Hast du etwas gesagt, Kapitän? Ich könnte vielleicht noch ein Duell in den heutigen Zeitplan einfügen.";
			link.l1.go = "richard_5";
		break;
		
		case "richard_5":
			dialog.text = "Entschuldigung, Kapitän. Es sind nur die Nerven!";
			link.l1 = "Ich denke, Ihre Anwesenheit hier ist nicht länger notwendig.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory");
		break;
		
		case "richard_duel":
			dialog.text = "Eine faire Entscheidung! Auch wenn sie nicht auf die würdevollste Art und Weise ausgedrückt wurde... Herren! Lassen Sie uns beginnen!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuel");
		break;
		
		case "alonso":
			dialog.text = "Kapitän, ich verstehe vielleicht nicht all die feinen Worte, die diese Würdenträger herumschleudern, aber sehen Sie, wenn jemand einen Feigling genannt wird, lässt man ihn normalerweise nicht vom Haken. Schlagen Sie den Kerl, Kapitän, sonst wird unsere Crew beunruhigt werden.";
			link.l1 = "Du willst Blut? Das Leben ist zu langweilig, keine Aufregung? Du wirst dein Blut bekommen, ihr Tiere!";
			link.l1.go = "francois_duel";
			link.l2 = "Boo-hoo, ich habe so Angst. Sind Sie hier fertig, meine Herren? Ich habe Orte zu besuchen.";
			link.l2.go = "alonso_refuse";
		break;
		
		case "alonso_1":
			dialog.text = "Es würde nicht gut aussehen, wenn unser Kapitän vor einer öffentlichen Herausforderung zurückschreckt. Verpass dem Adligen einen ordentlichen Hieb; wir wissen, dass du gut mit dem Schwert umgehen kannst!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog9");
		break;
		
		case "alonso_refuse":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog6");
		break;
		
		case "francois_refuse":
			dialog.text = "Feigling! Libertin! Ratte! Hast du Angst, Schurke? Habt ihr alle das gesehen?! Richard, ich werde ihn sowieso töten!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog4");
		break;
		
		case "francois_duel":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuelDialog");
		break;
		
		case "francois_sit":
			dialog.text = "Du Schuft! Das ist in Ordnung, ich bin Verletzungen gewöhnt. Ich werde mich erholen, und...";
			link.l1 = "Hört sich an wie eine Drohung, Oberst. Und ich nehme Drohungen nicht freundlich auf.";
			link.l1.go = "francois_sit_kill";
			link.l2 = "Sobald Sie sich erholt haben, vergessen Sie nicht, sich in der Offiziersgemeinschaft über die Umstände Ihrer Verletzung zu brüsten.";
			link.l2.go = "francois_sit_taunt";
		break;
		
		case "francois_sit_kill":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Helen disapproves", "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_FinishFrancois");
		break;
		
		case "francois_sit_taunt":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			notification("Helen approves", "Helena");
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 300);
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 300);
			
			AddDialogExitQuestFunction("HelenDrinking_SpareFrancois");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenSleep_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}
