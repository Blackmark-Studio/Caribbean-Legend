void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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
			dialog.text = "¿Qué quiere?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;

		case "OS_Matros_sluh":
			bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			if (bOk1 || bOk2)
			{
				dialog.text = "Dicen que anoche hubo una pelea en la taberna... Pero ¿quiénes peleaban? Ni idea. Mi cara está intacta. Creo.";
				link.l1 = "¿Parece que hubo una gran juerga aquí, no?";
				link.l1.go = "OS_Matros_sluh_2";
			}
			else
			{
				switch (rand(2))
				{
					case 0:
						dialog.text = "Oye, "+GetSexPhrase("amigo","amiga")+", ¿has visto mi bota por algún lado? Algún ladrón desgraciado se escapó con ella mientras estaba inconsciente debajo de la mesa de la taberna.";
						link.l1 = "Mantén los ojos bien abiertos, o el otro seguirá el mismo camino.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 1:
						dialog.text = "Dicen que hubo una pelea en la taberna ayer... Aunque quién peleaba es cosa de adivinanzas. Mi cara parece intacta. Eso creo.";
						link.l1 = "Quizás consideraron que tu cara ya había sufrido suficiente daño.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 2:
						dialog.text = "¡Por todos los diablos de las profundidades, ayer tenía una bolsa llena de oro! ¡¿Dónde demonios está ahora?!";
						link.l1 = "Para un verdadero pirata, el oro no es el premio que más importa. La libertad tiene un valor mucho mayor.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;
				}
			}
		break;
		
		case "OS_Matros_sluh_2":
			dialog.text = "¡Y tanto! El tabernero tuvo mucho trabajo... hip... Y además... ¡le robaron el ginebra! ¡No una botella, sino todo un barril! Y uno tan raro que no se encuentra en todo el Caribe. Dicen que vino directamente de Europa. No dice para quién lo tenía guardado, pero está claro: si no aparece pronto, una tormenta infernal caerá sobre él.";
			link.l1 = "Interesante. Bueno, cuídate, borrachín.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OS_Matros_sluh";
			
			SetQuestHeader("OS");
			AddQuestRecord("OS", "1");
			pchar.questTemp.OS_Start = true;
			pchar.questTemp.OS_Tavern_1 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_tavernkeeper"), "questmarkmain");
		break;

		case "OS_Matros_again":
			switch (rand(2))
			{
				case 0:
					dialog.text = "¿Qué más quieres? ¿No ves que mi cabeza está a punto de partirse? Lárgate.";
					link.l1 = "Quizás bebiendo menos podrías pasar por un hombre decente en lugar de un despojo empapado.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Déjame en paz... ¡Mi cabeza está a punto de explotar!";
					link.l1 = "Es sorprendente que aún siga unida a tus hombros.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 2:
					dialog.text = "Maldito seas... ¡Déjame en paz, ¿no ves que no estoy en condiciones de hablar contigo ahora?!";
					link.l1 = "...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
		break;
		
		case "OS_Matros":
			dialog.text = "¡Déjame en paz! ¿No ves que estoy al límite? Me pican los puños por conectar con la mandíbula de alguien.";
			link.l1 = "Cálmate, amigo. Solo quiero saber qué pasó anoche en la taberna.";
			link.l1.go = "OS_Matros_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Matros_2":
			dialog.text = "¡Caramba! ¿Eres otro de los amantes de esa camarera loca? ¿Qué quieres, que te arrastre una tormenta? ¿Me desafiarás a un duelo? ¿O sacarás la espada aquí mismo?";
			if (pchar.sex == "woman")
			{
				link.l1 = "¿Pariente? Lo dudo. Pero tú, amigo, no pareces tenerla en alta estima, ¿verdad?";
				link.l1.go = "OS_Matros_3_scrit";
			}
			else
			{
				link.l1 = "¿Amante? Difícilmente. La chica parece preferir la cantidad sobre la calidad, ¿no crees?";
				link.l1.go = "OS_Matros_3_scrit";
				link.l2 = "No me importan sus aventuras. Solo dime qué pasó, y me iré. ¿Fuiste tú quien la enfureció?";
				link.l2.go = "OS_Matros_3_fortuna";
			}
		break;

		case "OS_Matros_3_scrit":
			dialog.text = "¡Esa fiera es tan exigente como un marinero hambriento tras meses en el mar! Me lanzaba miraditas toda la noche, coqueteando como una gata de taberna. ¡Y justo cuando intenté echar ancla en su puerto, gritó tan fuerte que los peces de la bahía se sumergieron!";
			link.l1 = "¿Quizás habías bebido demasiado ron y fuiste excesivamente atrevido en tu acercamiento?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "OS_Matros_3_fortuna":
			dialog.text = "¡Esa fiera es tan exigente como un marinero hambriento tras meses en el mar! Me lanzaba miraditas toda la noche, coqueteando como una gata de taberna. ¡Y justo cuando intenté echar ancla en su puerto, gritó tan fuerte que los peces de la bahía se sumergieron!";
			link.l1 = "¿Quizás habías bebido demasiado ron y fuiste excesivamente atrevido en tu acercamiento?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "OS_Matros_4":
			dialog.text = "Puede que estuviera bebido, pero recuerdo claro como el mar en calma lo que pasó allí. No era yo quien la cazaba - ella me rondaba como un tiburón oliendo sangre. ¡Había estado revoloteando a mi alrededor todo el maldito día!";
			if (pchar.sex == "woman")
			{
				link.l1 = "¿Y por semejante nimiedad estás dispuesto a pelear con la primera persona que encuentras? ¿O pasó algo más esa noche?";
			}
			else
			{
				link.l1 = "Escucha, dijiste 'otro amante'. ¿Sabes algo sobre sus aventuras?";
			}
			link.l1.go = "OS_Matros_5";
		break;

		case "OS_Matros_5":
			dialog.text = "Después de que sus gritos se apagaron, mis compañeros de barco me dijeron que estaba perdiendo el tiempo intentando echar el anzuelo en sus aguas. Dijeron que tiene algún pretendiente en el pueblo que es uña y carne con nuestro capitán.";
			link.l1 = "Interesante. ¿Notaste algo más inusual? ¿Quizás alguien acercándose al mostrador durante el alboroto?";
			link.l1.go = "OS_Matros_6";
		break;

		case "OS_Matros_6":
			dialog.text = "¡Demonios...! Me estalla la cabeza y tú vienes con tus malditas preguntas. No vi ni oí una maldita cosa. Mejor dame unos pesos en vez de torturar a un lobo de mar con este interrogatorio.";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Aquí tienes cien pesos. Cuídate de no emborracharte y caer nuevamente bajo el hechizo de esa camarera, ¿eh?";
				link.l1.go = "OS_Matros_7_harizma";
			}
			link.l2 = "Te las arreglarás sin mi moneda. De lo contrario, simplemente te emborracharás e irás a molestar a esa camarera otra vez.";
			link.l2.go = "OS_Matros_7_fortuna";
		break;
		
		case "OS_Matros_7_harizma":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddQuestRecord("OS", "3");
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Matros_7_fortuna":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddQuestRecord("OS", "3");
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Dialog_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "¡Eh, Jack! ¡Tienes una ramera de puerto en tus aposentos! ¡Ja-ja! Mírala bien - ¡qué diablesa tan atractiva! Me pregunto, ¿habrá registrado todos nuestros cofres, o la interrumpimos en la parte más interesante?";
				link.l1 = "...";
			}
			else
			{
				dialog.text = "¡Eh, Jack! ¡Mira lo que tenemos aquí - una rata ladrona! ¡Ja-ja! ¡Mira a este sinvergüenza! Ya ha estado hurgando en nuestros baúles, ¿eh, perro furtivo?";
				link.l1 = "...";
			}
			link.l1.go = "OS_Dialog_2";
		break;

		case "OS_Dialog_2":
			StartInstantDialog("OS_Jack", "OS_Dialog_3", "Quest\\MiniEvents\\OldScores_dialog.c");
		break;

		case "OS_Dialog_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Una gallinita atrevida. Meterse en la guarida de Jack Veils - no muchos tendrían el valor. Entonces, ¿qué te trae por aquí, cariño? ¿Pensaste que podrías entretenernos, eh?";
				link.l1 = "¿Entreteneros? ¡Ja! Sois unos soñadores, caballeros. Estoy aquí para recuperar lo que robasteis. ¿De verdad creísteis que vuestra patética actuación pasaría desapercibida?";
			}
			else
			{
				dialog.text = "Un gusano valiente. Meterse en la casa de Jack Veils - no muchos tendrían el valor. Entonces, ¿qué haces aquí?";
				link.l1 = "Digamos que vine a recuperar lo robado. ¿Pensabais que vuestra ridícula farsa pasaría desapercibida?";
			}
			link.l1.go = "OS_Dialog_4";
		break;

		case "OS_Dialog_4":
			StartInstantDialog("OS_capWolf", "OS_Dialog_5", "Quest\\MiniEvents\\OldScores_dialog.c");
		break;

		case "OS_Dialog_5":
			if (pchar.sex == "woman")
			{
				dialog.text = "¿Patética actuación?! ¡Que me tueste el diablo, te desollaré viva y usaré tu piel para las velas! ¡Ja-ja! Aunque quizás primero deberíamos... ¿divertirnos un poco contigo?";
				link.l1 = "¿Veo que estáis ansiosos por encontraros con vuestro creador? Muy bien, no os haré esperar - ¡en guardia, sucios bastardos!";
			}
			else
			{
				dialog.text = "¿Patética actuación? ¡Que me tueste el diablo, te desollaré y usaré tu piel para las velas! ¡Se acabaron las palabras, bastardo!";
				link.l1 = "Pues si así lo queréis, ¡a las armas, miserables!";
			}
			link.l1.go = "OS_Dialog_bitva";
		break;
				
		case "OS_Dialog_bitva":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("OS_Jack");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("OS_capWolf");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "OS_VernuliBochonok");
		break;
		
		case "Zaharia_1":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = ""+sld.name+", ¡¿dónde está mi ginebra?! ¡Si no la tienes, personalmente te enviaré a alimentar a los peces en el fondo del puerto!";
			link.l1 = "...";
			link.l1.go = "Zaharia_2";
			CharacterTurnByChr(npchar, sld);
		break;

		case "Zaharia_2":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "...";
			link.l1 = "Acabo de entregarlo yo mism"+GetSexPhrase("o","a")+". Aquí está.";
			link.l1.go = "Zaharia_3";
			CharacterTurnByChr(npchar, pchar);
			TakeItemFromCharacter(pchar, "cask_gin");
			notification("Has entregado el barril de ginebra", "NONE");
		break;

		case "Zaharia_3":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "Me alegra ver que mi fe en ti no estaba mal depositada, "+sld.name+". Pasa por mis aposentos mañana por tus doblones.";
			link.l1 = "...";
			link.l1.go = "Zaharia_4";
			CharacterTurnByChr(npchar, sld);
		break;

		case "Zaharia_4":
			DialogExit();
			LAi_SetStayType(pchar);
			sld = CharacterFromID("OS_Zaharia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.lifeday = 0;
			sld.location = "None";
			DoQuestFunctionDelay("OS_RazgovorTavern", 1.5);
		break;

		case "Tavern_1":
			dialog.text = "Capitán, sobre esa placa...";
			link.l1 = "¿Qué placa? Ah, esa... Me atrevería a decir que no necesito tales honores. No se moleste por mi cuenta.";
			link.l1.go = "Tavern_2";
		break;

		case "Tavern_2":
			dialog.text = "¡Puedo ofrecer algo mucho mejor! ¡A partir de hoy, siempre tendrá alojamiento gratuito y bebidas por cuenta de la casa en mi taberna! ¡Una persona de su calibre ciertamente merece tanto!";
			link.l1 = "¡Ahora eso sí me agrada! ¡Tales privilegios puedo apreciarlos de corazón! Hasta pronto, "+npchar.name+".";
			link.l1.go = "Tavern_3";
		break;
		
		case "Tavern_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			AddQuestRecord("OS", "5");
			AddQuestUserData("OS", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.OS_Tavern_FreeBuhlo = true;
			ChangeShowIntarface();
			
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			sld.dialog.filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First Time";
			LAi_SetBarmanType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			
			PChar.quest.OS_AttackSea.win_condition.l1 = "location";
			PChar.quest.OS_AttackSea.win_condition.l1.location = "Cuba1";
			PChar.quest.OS_AttackSea.function = "OS_AttackSea";
			
			// вражеский корабль атакует в море
			sld = CharacterFromID("OS_Pirate");
			DeleteAttribute(sld, "AlwaysFriend");
			DeleteAttribute(sld, "ShipEnemyDisable");
			sld.AlwaysEnemy = true;
			LAi_SetImmortal(sld, false);
			
			PChar.quest.TPZ_Potopil.win_condition.l1 = "NPC_Death";
			PChar.quest.TPZ_Potopil.win_condition.l1.character = "OS_Pirate";
			PChar.quest.TPZ_Potopil.function = "OS_Pobeda";
		break;
		
		
		
		
		
		
		
	}
}