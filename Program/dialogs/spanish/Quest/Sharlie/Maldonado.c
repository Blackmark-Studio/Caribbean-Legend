// Алонсо де Мальдонадо
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
			dialog.text = "¿Necesitáis algo?";
			link.l1 = "No, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "ksochitam":
			dialog.text = "Detente, Capitán "+GetFullName(pchar)+"...";
			link.l1 = "De alguna manera, ni siquiera me sorprende la presencia de los soldados españoles aquí... Supongo que ya me he acostumbrado a que siempre haya alguien pisándome los talones. ¿Qué estás buscando en esta isla olvidada por Dios, castellano? ¿Buscas una forma rápida de estirar la pata?";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Mi nombre es Alonso de Maldonado. Eso tal vez no signifique nada para ti, pero Diego de Montoya podría sonarte. Era mi mejor amigo. Me salvó la vida y ahora su sangre está en tus manos.";
			link.l1 = "¿Supongo que me has seguido hasta aquí para buscar venganza?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "No solo busco venganza. Por lo que entiendo, ¿tienes la máscara de Kukulcán?";
			link.l1 = "¡Maldita sea! ¡Otro cazador de tesoros! ¿Vienes a terminar algún asunto pendiente que comenzó Don Diego?";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			dialog.text = "No estoy interesado en tesoros. He visto las riquezas en Tayasal. Miguel Dichoso no pudo sacar mucho más que un bocado. La máscara es lo que quiero.";
			link.l1 = "¿Has estado en Tayasal? Eso es difícil de creer. Hasta donde recuerdo, Dichoso fue el único sobreviviente de la expedición.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			dialog.text = "Fui a Tayasal veinte años antes de que Dichoso llegara allí. Al mismo tiempo, ese hechicero loco Kanek usó ese despreciable ritual de sacrificio humano para esconder la máscara en esta isla.";
			link.l1 = "¡No puedo creer lo que estoy oyendo! ¿Eres de la misma banda de conquistadores que fue llevada allí para ser sacrificada cuando se estaba creando el Guardián de la Verdad? ¡Todos deberían estar muertos!";
			link.l1.go = "ksochitam_5";
		break;
		
		case "ksochitam_5":
			dialog.text = "No todos nosotros. Yo sobreviví.";
			link.l1 = "¿Por qué los Itza decidieron perdonarte? ¿Qué te hace tan diferente?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "No lo entenderías. Demonios, yo tampoco lo entendía. Nadie me perdonó. Lo recuerdo como si fuera ayer... Justo después de que ese salvaje tomara un puñal y desollara un trozo de piel de la espalda de Casco antes de darle muerte y empezar a aullar como un maníaco, creo que fui absorbido por el ídolo. Me desperté muy lejos de Tayasal veinte años después, en lo que pareció un mero momento.";
			link.l1 = "Un embudo espacio-temporal... ¡Maldita sea, todo lo que dijo Ksatl Cha tenía sentido! ¿Cómo te enteraste de la máscara? ¿Para qué la necesitas?";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			dialog.text = "Debo detener a la prole del infierno, invocada por un hechicero indio loco. ¡Esta abominación pretende hacer una hoguera de nuestro mundo!";
			link.l1 = "Hmm... ¿Has hablado con el padre Vincento, no? El Inquisidor está jugando a dos bandos. ¡Sorpresa, sorpresa! ¿Te ha enviado para rastrearme para una batalla campal? ¡Bien hecho! ¡Has completado tu misión, Don Alonso!";
			link.l1.go = "ksochitam_8";
		break;
		
		case "ksochitam_8":
			dialog.text = "El señor fortalece mi mano en la batalla contra el mal. Regresaré a Tayasal y usaré la máscara para cerrar las puertas para siempre. Y ningún demonio en forma humana volverá a cruzar a nuestro mundo.";
			link.l1 = "Solo hay un pequeño problema en tu plan, Don Alonso. El demonio YA está entre nosotros. Todo lo que necesitamos hacer es no dejarlo SALIR por estas puertas. No podrá hacerlo mientras mantengas la máscara alejada de él.";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "Hará falta más que eso. Quienquiera que de nosotros tenga razón, una cosa es segura: las puertas deben cerrarse para siempre. Y solo hay una forma de hacerlo: destruir la máscara en el altar de Tayasal. Al hacerlo, el demonio será despojado de todo su poder.";
			link.l1 = "Hum. Estoy de acuerdo en que es nuestra mejor apuesta... ¿Cómo planeas llegar a Tayasal? ¿Conoces el camino hasta allí?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "El camino fácil que usábamos entonces ya no existe. Los caminos están enterrados con piedras y perdidos en las junglas. Hay otra manera de llegar a la ciudad, pero es larga y peligrosa. El camino empieza en la bahía más al norte de Yucatán.\nCon la ayuda del padre Vincento y don Ramón de Mendoza reuniré un escuadrón de soldados de élite y lucharemos a través de la selva protegida por los salvajes Itza. No será fácil, pero Dios nos concederá fuerza y valentía para nuestra lucha en el nombre de nuestra fe.";
			link.l1 = "Don Alonso, mis aspiraciones coinciden con las suyas. ¿No es hora de dejar a un lado los rencores por un momento y unir fuerzas? Juntos tendremos una mejor oportunidad de completar esta cruzada con éxito.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "Soy un soldado español. No formo alianzas con herejes ni hago tratos con franceses. Además, ya he declarado mi vendetta contra ti por Don Diego. ¡Una vida por una vida!";
			link.l1 = "¡Eres más terco que un buey, Don Alonso! Ahí estás, predicando que el mundo está amenazado por un gran mal, ¡y aún así rechazas mi ayuda para tener éxito en una tarea tan astronómica!";
			link.l1.go = "ksochitam_12";
		break;
		
		case "ksochitam_12":
			dialog.text = "¡Ahora tomo las decisiones yo, no el padre Vincento! ¡Reza tus oraciones y prepárate para morir, capitán francés!..";
			link.l1 = "¡Oh, he escuchado eso tantas veces en los últimos meses! ¡En guardia, testarudo caballero!";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_mushketer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_MaldonadoDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			if (MOD_SKILL_ENEMY_RATE > 4) Ksochitam_CreateMaldonadoHelpers();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
