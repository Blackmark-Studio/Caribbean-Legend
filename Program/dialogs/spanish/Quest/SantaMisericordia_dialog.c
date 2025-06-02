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
			dialog.text = "¿Qué necesitáis?";
			link.l1 = "Nada.";
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
			dialog.text = "...y del Espíritu Santo. Amén.";
			link.l1 = "Rara vez veo militares en las iglesias.";
			link.l1.go = "Alamida_church_2";
		break;
		
		case "Alamida_church_2":
			dialog.text = "Muchos creen que la fe y la espada son incompatibles. Pero, ¿no corta un cirujano para sanar? ¿No castiga un padre para proteger?";
			link.l1 = "Suena a justificación.";
			link.l1.go = "Alamida_church_3";
			link.l2 = "Hay sabiduría en eso. A veces la crueldad es necesaria.";
			link.l2.go = "Alamida_church_4";
		break;
		
		case "Alamida_church_3":
			dialog.text = "Te equivocas. Esto no es justificación, es comprensión. Cuando comencé mi servicio, cada muerte era... difícil. Pero luego... se me abrieron los ojos. 'La crueldad es la manifestación del amor supremo.'";
			link.l1 = "Te dejo con tus oraciones.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_4":
			dialog.text = "¡Sí... sí! Eso es exactamente lo que dijo, el que me guió por este camino. 'La misericordia sin fuerza es inútil, como una espada sin mano.'";
			link.l1 = "Te dejaré con tus oraciones.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_5":
			dialog.text = "Reza por todos nosotros. Por lo que hacemos... y por lo que aún debemos hacer.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_guber":
			dialog.text = "Siete por ciento de déficit. La última vez fue cinco. Creciendo como malezas en un jardín abandonado...";
			link.l1 = "¿Hay un nuevo gobernador en la ciudad?";
			link.l1.go = "Alamida_guber_2";
		break;
		
		case "Alamida_guber_2":
			dialog.text = "¿Qué? Ah, no. Su Excelencia está allí, en la esquina. Yo soy don Fernando de Alamida, inspector real.";
			link.l1 = "Debe de ser trabajo difícil.";
			link.l1.go = "Alamida_guber_3";
		break;
		
		case "Alamida_guber_3":
			dialog.text = "¿Sabes cuál es la parte más difícil de combatir la corrupción? Los culpables no son necesariamente malas personas. Tienen hijos, familias. Y cada vez debes recordarte: el veneno sigue siendo veneno, incluso cuando se sirve en una copa dorada.";
			link.l1 = "¿Pero se puede juzgar tan severamente? Todos somos humanos...";
			link.l1.go = "Alamida_guber_4";
			link.l2 = "Eres demasiado blando. Solo la prisión los reformará.";
			link.l2.go = "Alamida_guber_5";
		break;
		
		case "Alamida_guber_4":
			dialog.text = "La misericordia para el lobo es crueldad para las ovejas. Así lo dijo... un hombre sabio. Y con cada día que pasa, entiendo su sabiduría más y más.";
			link.l1 = "No te distraeré más de tu trabajo.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_5":
			dialog.text = "Hum. Sabes, solía pensar de la misma manera. Pero la prisión es demasiado simple. Se necesita algo más... Purificación.";
			link.l1 = "No te distraeré más de tu trabajo.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_6":
			dialog.text = "Sí. Los papeles no esperarán. Aunque a veces me parece que detrás de cada número aquí se esconde el destino de alguien.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_city":
			dialog.text = "Estoy escuchando atentamente, "+GetAddress_Form(NPChar)+"¿Qué te hizo acercarte a mí así, en la calle?";
			link.l1 = "Destacas entre los demás.";
			link.l1.go = "Alamida_city_2";
		break;
		
		case "Alamida_city_2":
			dialog.text = "Don Fernando de Alamida, inspector real. Eres el primero tan curioso hoy. Todos se esconden, todos me temen. Sin embargo, una persona honesta no tiene nada que temer. ¿Qué nos dice eso?";
			link.l1 = "¿Que tu reputación los asusta?";
			link.l1.go = "Alamida_city_3";
			link.l2 = "¿Que la gente honesta es poca?";
			link.l2.go = "Alamida_city_4";
		break;
		
		case "Alamida_city_3":
			dialog.text = "Divertido. Yo también lo pensé. Hasta que entendí - el miedo purifica. Cuando una persona tiene miedo, se vuelve más honesta. Más cerca de su verdadera naturaleza. De Dios.";
			link.l1 = "Interesante pensamiento. Debo irme. Buen día, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_4":
			dialog.text = "Interesante... Razonas igual que alguien que conocí. Lástima que no todos puedan aceptar esta verdad.";
			link.l1 = "Interesante pensamiento. Debo irme. Buen día, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_5":
			dialog.text = "¿Bueno? Sí, tal vez. Mientras sea justo.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_exit":
			DialogExit();
			
			sld = CharacterFromID("SantaMisericordia_clone_church");
			sld.dialog.filename = "Quest\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_city");
			sld.dialog.filename = "Quest\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_guber");
			sld.dialog.filename = "Quest\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
		break;
		
		case "Alamida_repeat":
			dialog.text = "¿Algo más, Capitán?";
			link.l1 = "No, don Fernando, solo saludando, nada más.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alamida_repeat";
		break;
		
		case "Alamida_abordage":
			if (startHeroType == 4)
			{
				dialog.text = "¿Una doncella con espada? Vaya, nunca pensé que viviría para ver semejante espectáculo. Y, ¿quién podrías ser tú, señorita, para atreverte a atacar al 'Santa Misericordia'?";
				link.l1 = "Capitana Hellen McArthur. Y esa expresión de sorpresa en tu rostro es una que conozco bien.";
				link.l1.go = "Alamida_HelenaCaptain";
			}
			else
			{
				dialog.text = "¿Cómo te atreves? ¡¿Atacar la 'Santa Misericordia'?! Un barco que lleva la voluntad del rey y... Bueno. Ya que estás aquí, dime, ¿por qué? ¿Por qué elegiste esta locura?";
				link.l1 = "Soy un pirata. Y tu galeón seguramente está lleno de tesoros.";
				link.l1.go = "Alamida_abordage_Gold";
				link.l2 = "Qué hermoso barco... Debo poseerlo.";
				link.l2.go = "Alamida_abordage_Ship";
				link.l3 = "Soy un enemigo de su país, don Fernando.";
				link.l3.go = "Alamida_abordage_Hater";
				link.l4 = "Simplemente porque. ¿Por qué no?";
				link.l4.go = "Alamida_abordage_Prikol";
			}
		break;
		
		case "Alamida_HelenaCaptain":
			dialog.text = "Cómo te pareces a la Virgen María, protectora de nuestro barco... Igual de hermosa. Pero Ella protege a los justos, mientras que tú...";
			link.l1 = "He venido por tu barco. Y los cumplidos no ayudarán aquí, don Fernando.";
			link.l1.go = "Alamida_HelenaCaptain_2";
		break;
		
		case "Alamida_HelenaCaptain_2":
			dialog.text = "Qué triste. Tendré que enseñarte humildad entonces. Por la fuerza, ya que no hay otra manera.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Gold":
			dialog.text = "Ah, sí. Por supuesto. Oro. Siempre oro. El veneno que corroe las almas. Por ello morirás.";
			link.l1 = "No seas tan dramático. Esto es solo negocio.";
			link.l1.go = "Alamida_abordage_Gold_2";
		break;
		
		case "Alamida_abordage_Gold_2":
			dialog.text = "Cada moneda en la bodega es el pago de los pecadores por la purificación. ¿La quieres? Entonces comparte su destino.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Ship":
			dialog.text = "Muchos han codiciado la 'Santa Misericordia'. Su belleza ha sido la perdición de más de un capitán.";
			link.l1 = "Entonces seré el primero en reclamarlo.";
			link.l1.go = "Alamida_abordage_Ship_2";
		break;
		
		case "Alamida_abordage_Ship_2":
			dialog.text = "La misericordia sin fuerza es inútil, como una espada sin mano. Esta lección la aprenderás hoy.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Hater":
			dialog.text = "Así que eso es todo. Otro celoso de la grandeza del Imperio.";
			link.l1 = "¿Qué grandeza? Tus maneras rígidas están retrasando este mundo.";
			link.l1.go = "Alamida_abordage_Hater_2";
		break;
		
		case "Alamida_abordage_Hater_2":
			dialog.text = "No te engañes a ti mismo. El miedo a España te hace más honesto. Más cercano a tu verdadera naturaleza. Lo verás por ti mismo ahora.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Prikol":
			dialog.text = "Chiflado. ¿O quizás fuiste enviado a mí como una prueba?";
			link.l1 = "No todo necesita una razón, señor.";
			link.l1.go = "Alamida_abordage_Prikol_2";
		break;
		
		case "Alamida_abordage_Prikol_2":
			dialog.text = "Dijo que las personas como tú son las más peligrosas. Pero esto solo fortalecerá mi mano en la batalla.";
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
				dialog.text = "Tal fortaleza de espíritu... Tal voluntad...";
				link.l1 = "¿Sorprendido?";
			}
			else
			{
				dialog.text = "No está mal. Ha pasado un tiempo desde que encontré un oponente digno.";
				link.l1 = "No te daré tiempo para descansar.";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_2";
		break;
		
		case "Alamida_abordage_TrirdRound_2":
			if (startHeroType == 4)
			{
				dialog.text = "Me advirtieron... sobre tal prueba. Sobre una belleza que podría sacudir la fe de un guerrero.";
				link.l1 = "¿Siempre complicas tanto las cosas simples, don Fernando?";
			}
			else
			{
				dialog.text = "El Señor da fuerza a aquellos que sirven a una causa justa. Aunque... a veces ya no estoy seguro de a qué sirvo.";
				link.l1 = "¿Tienes dudas?";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_3";
		break;
		
		case "Alamida_abordage_TrirdRound_3":
			if (startHeroType == 4)
			{
				dialog.text = "¿Simple? No... Debe haber un significado más profundo. Esto es una prueba. No puedo estar equivocado.";
			}
			else
			{
				dialog.text = "No. Me enseñó a no dudar. Nunca.";
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
			dialog.text = "Espera... Espera. Has ganado. Estoy herido, desangrándome. Permíteme rezar antes de morir.";
			link.l1 = "Muy bien.";
			link.l1.go = "Alamida_abordage_Molitva_2";
		break;
		
		case "Alamida_abordage_Molitva_2":
			if (startHeroType == 4)
			{
				dialog.text = "Señor... perdóname mis pecados y dame fuerza en esta hora de prueba. Bendice las almas de mis camaradas caídos. Marineros fieles, murieron creyendo que llevaban justicia\nPadre, traté de vivir según tus enseñanzas, de luchar contra la injusticia. Pero tu hijo ha manchado el honor de la familia Alamida. Perdóname\nMadre patria... juré servirte fiel y verdaderamente. Pero mi fervor, mi ira... me convertí en aquello contra lo que buscaba luchar\nDiego... ¿Quizás mintió? Todo este tiempo... Ay de mí si es así\nY bendice a esta mujer, Señor. Quizás en tu misericordia final la enviaste a mí... para que pudiera ver cuán lejos me había desviado. Amén.";
			}
			else
			{
				dialog.text = "Señor... perdóname mis pecados y dame fuerza en esta hora de prueba. Bendice las almas de mis camaradas caídos. Marineros fieles, murieron creyendo que llevaban justicia\nPadre, traté de vivir según tus enseñanzas, de luchar contra la injusticia. Pero tu hijo ha manchado el honor de la familia Alamida. Perdóname\nPatria... Juré servirte fiel y verdaderamente. Pero mi fervor, mi ira... Me convertí en lo que buscaba combatir\nDiego... ¿Quizás mintió? Todo este tiempo... ¡Ay de mí si es así!\nSanta Virgen María, ruega a Dios por nosotros y concédenos tu misericordia. Amén.";
			}
			link.l1 = "No te reconozco, don Fernando. Pareces una persona diferente ahora. ¿Y de quién hablabas?";
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
			dialog.text = "¡Mi capitán, felicidades! Qué batalla tan feroz. Ese capitán era hábil, oh tan hábil. Pero tú... tú demostraste ser aún mejor. Qué orgulloso estoy de ti...";
			link.l1 = "Gracias, mi amor. ¿Estás herido?";
			link.l1.go = "Alamida_Helena_2";
		break;
		
		case "Alamida_Helena_2":
			dialog.text = "No, no.  Aunque pensé que estábamos al borde un par de veces - tanto antes de abordar como durante.  ¿Y tú, estás bien?";
			link.l1 = "Estoy bien, gracias de nuevo. Ve a descansar en la cabina, te alcanzaré pronto.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Мэри
		case "Alamida_Mary":
			dialog.text = "Charles, ¿estás bien? Vine tan pronto como pude, está bien.";
			link.l1 = "Estoy bien, gracias, querida. Aunque fue una lucha bastante dura.";
			link.l1.go = "Alamida_Mary_2";
		break;
		
		case "Alamida_Mary_2":
			dialog.text = "¡Me alegra! Pero... Escucha, ¿Charles? ¿Por qué atacamos a estas personas? El Señor no nos perdonará esto, no. Este barco... como un gran templo. Cuando lo vi, mi corazón tembló, igual que cuando vi una iglesia de verdad por primera vez, no solo en los libros. ¡Y ahora sangra!";
			link.l1 = "Mary... Sabes que las apariencias pueden engañar. Y detrás de la máscara de piedad estaban aquellos que tomaban dinero de simples creyentes, igual que tú. ¿Entiendes?";
			link.l1.go = "Alamida_Mary_3";
		break;
		
		case "Alamida_Mary_3":
			dialog.text = "Yo... yo te creo, Charles. Está bien. Solo... ¿donamos al menos algo del oro que encontramos aquí a quienes realmente lo necesitan? Aliviaría mi corazón.";
			link.l1 = "Lo haremos, Mary. Lo prometo. Ahora recoge tus pensamientos e intenta calmarte. Todo ha terminado.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Томми
		case "Alamida_Tommi":
			dialog.text = "¡Ja, pues, felicidades por tu victoria, capitán! ¡Ahora eso es lo que yo llamo negocios! ¡Qué botín en este galeón!..";
			link.l1 = "Tu sonrisa es aún más amplia de lo habitual hoy, Tommy.";
			link.l1.go = "Alamida_Tommi_2";
		break;
		
		case "Alamida_Tommi_2":
			dialog.text = "¡Ya lo creo! Qué despojos. Y qué pelea. Me recordó a la Revolución. Y también... jeje.";
			link.l1 = "¿Qué pasa, Tommy? Vamos, habla.";
			link.l1.go = "Alamida_Tommi_3";
		break;
		
		case "Alamida_Tommi_3":
			dialog.text = "Cómo han adornado todo el barco como una catedral flotante. Y han reunido tanto oro de todas partes. ¡Verdaderos papistas fanáticos! Desgracia y risible.";
			link.l1 = "Este es un barco del tesoro, Tommy. No un barco de la iglesia.";
			link.l1.go = "Alamida_Tommi_4";
		break;
		
		case "Alamida_Tommi_4":
			dialog.text = "No hay mucha diferencia en nuestro caso. De cualquier manera, me alegró darles a esos dones y papistas una buena lección. ¡No soporto a ninguno de ellos! Disfruté mucho de este día, ¡ja-ja-ja!";
			link.l1 = "¡Nunca cambias! Está bien, ya puedes retirarte. Todo está bajo control aquí.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Тичингиту
		case "Alamida_Tichingitu":
			if (startHeroType == 1)
			{
				dialog.text = "Capitán Charles, ganamos la victoria. Esta fue una pelea difícil. Incluso Tichingitu la encontró dura, y yo soy uno de los mejores guerreros de la aldea.";
				link.l1 = "Verdad, mi amigo. Fueron oponentes dignos, sin duda.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Señor de Montoya, el barco es nuestro.";
				link.l1 = "Muy bien, Tichingitu. Yo también acabo de terminar aquí.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Capitán Paterson, la última resistencia aplastada en el barco.";
				link.l1 = "¡Llegas tarde, Tich! La próxima vez será mejor que te quedes conmigo. No es que no pudiera manejarlo solo, tenlo en cuenta...";
			}
			if (startHeroType == 4)
			{
				dialog.text = "¿Capitán McArthur, está bien?";
				link.l1 = "Sí, Tichingitu, estoy bien, gracias por preguntar. Y deja de dudar de tu capitán - lo manejé perfectamente por mi cuenta.";
			}
			link.l1.go = "Alamida_Tichingitu_2";
		break;
		
		case "Alamida_Tichingitu_2":
			if (startHeroType == 1)
			{
				dialog.text = "Los espíritus me dicen esto durante la pelea. Y preguntan por qué los maté. Ahora te pregunto lo mismo. Tichingitu lo ve en sus ojos, ellos no son villanos. Aún no.";
				link.l1 = "Ah, ¿qué puedo decirte? No tengo una respuesta, Tichingitu.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Quiero hacerle una pregunta, Capitán de Montoya.";
				link.l1 = "Estoy escuchando.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Tichingitu quiere hacerle una pregunta, Capitán William, si lo permite.";
				link.l1 = "Concedido.";
			}
			if (startHeroType == 4)
			{
				dialog.text = "No lo dudo, me preocupo por ti, capitán.";
				link.l1 = "Está bien, está bien. Puedo ver en tus ojos que quieres preguntarme algo más.";
			}
			link.l1.go = "Alamida_Tichingitu_3";
		break;
		
		case "Alamida_Tichingitu_3":
			if (startHeroType == 1)
			{
				dialog.text = "Hum, como digas, capitán. ¿Terminamos aquí?";
				link.l1 = "Sí. Miraré un poco más alrededor, luego me uniré a los demás.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 2)
			{
				dialog.text = "¿Esta gente no es del mismo tribu que tú? ¿No son españoles? ¿Por qué decidiste atacar?";
				link.l1 = "Eso es cierto. Pero, ¿acaso las tribus indias no se pelean entre sí también? ¿O no hay disputas y rencillas dentro de una misma tribu?";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 3)
			{
				dialog.text = "La nave parece una iglesia. ¿Odias la iglesia y al dios blanco?";
				link.l1 = "No del todo. Pero es solo decoración, ¿ves? Este es un barco del tesoro. Aunque no lo entenderías, escuché que tu gente ni siquiera sabe qué son los impuestos. Diablos afortunados.";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Sí. Sé sincero. Capitán MacArthur, ¿por qué atacamos esta iglesia flotante?";
				link.l1 = "¡Iglesia flotante, ja-ja-ja! No, no. Este es un barco del tesoro. Hmm, veo que no entiendes del todo. Bueno, llevaban oro. ¡Puedo imaginarme lo orgulloso que estará Jan cuando le diga que derroté a Fernando de Alamida!";
				link.l1.go = "Alamida_Tichingitu_4";
			}
		break;
		
		case "Alamida_Tichingitu_4":
			if (startHeroType == 2)
			{
				dialog.text = "Mm, tienes razón, capitán. Pero con los indios esto sucede menos que con el hombre blanco.";
				link.l1 = "Tal vez. Bueno, este hombre estaba... interfiriendo conmigo.";
				link.l1.go = "Alamida_Tichingitu_5";
			}
			if (startHeroType == 3)
			{
				dialog.text = "En verdad, Maskogi no tiene castillos ni impuestos.";
				link.l1 = "Exactamente. Puedes irte, ya estás tarde de todos modos. Más tarde decidiremos qué hacer con este hermoso galeón. No me gustan estas bañeras, pero maldita sea, es una belleza.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Tichingitu también está orgulloso de ti, capitán. Y te felicita por la victoria en esta dura batalla.";
				link.l1 = "Gracias. Ahora vamos a dividir el botín.";
				link.l1.go = "Alamida_BitvaEnd";
			}
		break;
		
		case "Alamida_Tichingitu_5":
			dialog.text = "¿Interfiriendo, Señor de Montoya?";
			link.l1 = "Exactamente. Este Archipiélago es demasiado pequeño para los dos. Y soy de mucho más uso para nuestro estado aquí. Recuerda a Hoja de Cacao - hizo más daño que bien a sus hermanos. Lo mismo aquí.";
			link.l1.go = "Alamida_Tichingitu_6";
		break;
		
		case "Alamida_Tichingitu_6":
			dialog.text = "Ahora entiendo. ¿Tichingitu puede irse, capitán?";
			link.l1 = "Sí, ve. Me uniré a vosotros pronto también.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		case "Alamida_monah":
			dialog.text = "Curioso... ¿Qué trae a un hijo de Dios a este lugar de... descanso?";
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				link.l1 = "Yo...";
				link.l1.go = "Alamida_monah_2";
			}
			else
			{
				link.l1 = "Yo... ¡Espere! ¡Ya nos hemos visto antes!";
				link.l1.go = "Alamida_monah_Second_2";
			}
		break;
		
		case "Alamida_monah_2":
			dialog.text = "¿Sabes qué tiene de especial esta cripta? Dos almas descansan aquí, unidas por... lazos de sangre. Padre e hijo de Alamida. Uno cayó en manos de pecadores, el otro... Hmm, encontró su camino hacia el Señor.";
			link.l1 = "El diario de Don Fernando me llevó hasta aquí.";
			link.l1.go = "Alamida_monah_3";
			link.l2 = "Solo busco algo valioso en esta cripta.";
			link.l2.go = "Alamida_monah_6";
		break;
		
		case "Alamida_monah_3":
			dialog.text = "Ah... El diario. Una cosa notable - la palabra escrita. Es como... un camino en la oscuridad. Lleva a donde... espera la revelación. Nuestra parroquia era visitada a menudo por don Fernando. Especialmente en el último año.";
			link.l1 = "¿Sirves en la parroquia? ¿Conocías al don Fernando?";
			link.l1.go = "Alamida_monah_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Alamida_monah_4":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "Alamida_monah_5";
		break;
		
		case "Alamida_monah_5":
			dialog.text = "Yo... observé su camino. Y este libro que tomaste. ¿Sabes qué lo hace especial?";
			link.l1 = "Parece antiguo.";
			link.l1.go = "Alamida_monah_5_1";
		break;
		
		case "Alamida_monah_5_1":
			dialog.text = "¿Vieja? Oh no. Es... ilustrada. La Biblia de don de Alamida Senior. Cada palabra en ella - como un faro en la oscuridad. Tómala. Ayuda a tus hermanos en Cristo y luego, quizás... te llevará a algo... mayor.";
			link.l1 = "... ";
			link.l1.go = "Alamida_monah_9";
		break;
		
		case "Alamida_monah_6":
			dialog.text = "Qué... mundano. Y sin embargo... ¿No es notable? De todas las criptas, viniste a esta. ¿Coincidencia?";
			link.l1 = "...";
			link.l1.go = "Alamida_monah_7";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Alamida_monah_7":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "Alamida_monah_8";
		break;
		
		case "Alamida_monah_8":
			dialog.text = "Oh no. El Señor siempre encuentra un camino incluso para aquellos que vagan en la oscuridad.";
			link.l1 = "...";
			link.l1.go = "Alamida_monah_9";
		break;
		
		case "Alamida_monah_9":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload2", "", -1);
			DoQuestFunctionDelay("SantaMisericordia_HavanaCrypt_9", 2.4);
		break;
		
		case "Alamida_monah_10":
			dialog.text = "¿Sabes qué es lo más notable del destino de don Fernando?";
			link.l1 = "¿Qué es eso?";
			link.l1.go = "Alamida_monah_11";
		break;
		
		case "Alamida_monah_11":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1) sStr = "primero";
 			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)	sStr = "segundo";
			dialog.text = "Que él era simplemente... el " + sStr + ".";
			link.l1 = "...";
			link.l1.go = "Alamida_monah_12";
		break;
		
		case "Alamida_monah_12":
			DialogExit();
			
			sld = CharacterFromID("SantaMisericordia_priest");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "SantaMisericordia_Final", 3);
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		break;
		
		case "Alamida_monah_Second_2":
			dialog.text = "¿Sabes qué tiene de especial esta cripta? Dos almas descansan aquí, unidas por... lazos de sangre. Padre e hijo de Alamida. Uno cayó en manos de los pecadores, el otro... encontró su camino hacia el Señor.";
			link.l1 = "¿Sirves en la parroquia? ¿Conocías a don Fernando?";
			link.l1.go = "Alamida_monah_Second_3";
		break;

		case "Alamida_monah_Second_3":
			dialog.text = "Yo... observé su camino. Y este manual que tomó. ¿Sabe qué lo hace especial?";
			link.l1 = "Parece viejo.";
			link.l1.go = "Alamida_monah_Second_4";
		break;

		case "Alamida_monah_Second_4":
			dialog.text = "Tiene una rica historia, y harías bien en dedicar algún esfuerzo a servir a los Hermanos en Cristo llevándola cerca de tu corazón. Pero eso no es lo interesante.";
			link.l1 = "La última vez hablaste con acertijos. ¿Lo volverás a hacer?";
			link.l1.go = "Alamida_monah_Second_5";
		break;

		case "Alamida_monah_Second_5":
			dialog.text = "\nEl verdadero enigma está ante mí ahora. Has coleccionado muchas reliquias... interesantes. La Biblia, la carta. ¿Te gusta coleccionar esas cosas? ¿Eres coleccionista?";
			link.l1 = "¿Cómo sabes lo del manual?";
			link.l1.go = "Alamida_monah_Second_6";
		break;

		case "Alamida_monah_Second_6":
			dialog.text = "¿Un cazador de trofeos?";
			link.l1 = "Repito mi pregunta: ¿cómo sabes lo del manual?";
			link.l1.go = "Alamida_monah_Second_7";
		break;

		case "Alamida_monah_Second_7":
			dialog.text = "¿Buscas emociones fuertes?";
			link.l1 = "...";
			link.l1.go = "Alamida_monah_Second_8";
		break;

		case "Alamida_monah_Second_8":
			dialog.text = "\nAh, por supuesto. Bueno, Capitán, no lo entretendré....";
			link.l1 = "Espere un momento, Santo Padre. Aún no ha respondido a mi pregunta.";
			link.l1.go = "Alamida_monah_Second_9";
		break;

		case "Alamida_monah_Second_9":
			dialog.text = "Oh, Capitán. No puedo. A veces las respuestas duelen más que cualquier ignorancia. Ve en paz. Y cuida tu colección... de trofeos. Pueden ser útiles en el viaje que te espera.";
			link.l1 = "...";
			link.l1.go = "Alamida_monah_9";
		break;

		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			dialog.text = LinkRandPhrase("¡Oye, ¿qué pasa con todo ese balanceo de armas?! ¡Guárdala de inmediato!","¡Te ordeno que guardes tu arma de inmediato!","¡Eh, "+GetAddress_Form(NPChar)+", ¡deja de asustar a la gente! Guarda tu arma.");
			link.l1 = LinkRandPhrase("Está bien, lo guardaré...","Ya está hecho.","Como usted diga...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("¡Que te den!","¡Supongo que voy a usarlo!","Lo guardaré cuando sea el momento adecuado.");
			link.l2.go = "fight";
		break;
		
	}
} 