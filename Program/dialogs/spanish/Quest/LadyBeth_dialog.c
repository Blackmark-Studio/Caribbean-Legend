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
			dialog.text = "¿Qué es lo que usted necesita?";
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
		
		case "AlonsoNaPalube":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube"))
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube2 = true;
				dialog.text = "¿Su decisión, Capitán? ¿Quizás no deberíamos?";
				link.l1 = "¿Consiguió reunir a más voluntarios para la tarea?";
				link.l1.go = "AlonsoNaPalube_StrongGroup";
			}
			else
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube = true;
				dialog.text = "Capitán, una palabra.";
				link.l1 = "Informe, Alonso.";
				link.l1.go = "AlonsoNaPalube_2";
			}
			locCameraFromToPos(-10.33, 9.69, -22.16, true, -5.22, 7.19, -21.06);
		break;
		
		case "AlonsoNaPalube_2":
			dialog.text = "La tripulación se pregunta cuáles son sus planes para las Caimán. La gente está preocupada.";
			link.l1 = "Aún no lo he decidido. ¿Y por qué están preocupados los hombres, Alonso?";
			link.l1.go = "AlonsoNaPalube_3";
		break;
		
		case "AlonsoNaPalube_3":
			dialog.text = "Esta isla es dominio del capitán Blackwood. Los marineros dicen que la excava como un poseso, a lo largo y ancho. Que ha malogrado a docenas de hombres en sus excavaciones... Y los que lo abandonan... cuentan extrañas historias.";
			link.l1 = "¿Qué tipo de historias?";

			link.l1.go = "AlonsoNaPalube_4";
		break;
		
		case "AlonsoNaPalube_4":
			dialog.text = "Que Blackwood ya no es el hombre que una vez fue. Que está obsesionado con encontrar el tesoro de un conquistador. Que está dispuesto a sacrificar todo y a todos por ello. Sabemos lo mucho que te gusta meterte en historias bonitas, desembarcar solo y caer en trampas... Pues de esta no saldrás.";
			link.l1 = "Gracias por el informe y la advertencia. Si decido hacer un desembarco, me aseguraré de llevar la vanguardia y un destacamento de nuestros mejores combatientes.";
			link.l1.go = "AlonsoNaPalube_5";
		break;
		
		case "AlonsoNaPalube_5":
			dialog.text = "Eso puede ser difícil, capitán. Abordar es una cosa, pero desembarcar bajo las balas de los marines y los sables de la gentuza que supuestamente Blackwood ha contratado de todos los agujeros de las Antillas Menores es otra muy distinta. Y hay malos rumores sobre Caimán... No, no encontrarás muchos voluntarios para ese trabajo.";
			link.l1 = "Entonces tendremos que apañarnos con quien podamos. Tu participación es obligatoria, Alonso.";
			link.l1.go = "AlonsoNaPalube_LiteGroup";
			link.l2 = "En mi opinión, ya he demostrado a todo el mundo todo lo que se podía demostrar. Todos los buenos luchadores y tiradores irán. Es una orden.";
			link.l2.go = "AlonsoNaPalube_StrongGroup";
			link.l3 = "Hmm... Bueno, necesito pensarlo bien. Quizá retomemos esta cuestión más adelante.";
			link.l3.go = "AlonsoNaPalube_Exit";
		break;
		
		case "AlonsoNaPalube_Exit":
			SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
			EndQuestMovie();
			bQuestDisableMapEnter = false;
			chrDisableReloadToLocation = false;
			if(UnloadLocation(loadedLocation) == true)
			{
				pchar.Ship.Pos.x = 0;
				pchar.Ship.Pos.z = 0;
				pchar.Ship.Ang.y = 0;
				Land_MapLoad();
				pchar.location = "";
			}
		break;
		
		case "AlonsoNaPalube_LiteGroup":
			dialog.text = "¡Sí, Capitán!";
			link.l1 = "¿Y la nave de Blackwood? ¿No causará problemas?";
			link.l1.go = "AlonsoNaPalube_Vpered";
			pchar.questTemp.LadyBeth_LiteGroup = true;
		break;
		
		case "AlonsoNaPalube_StrongGroup":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50 || sti(pchar.rank) >= 17)
			{
				dialog.text = "¡Sí, Capitán!";
				link.l1 = "¿Y la nave de Blackwood? ¿No causará problemas?";
				link.l1.go = "AlonsoNaPalube_Vpered";
				pchar.questTemp.LadyBeth_StrongGroup = true;
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50) notification("¡Comprobación superada!", SKILL_Leadership);
				if (sti(pchar.rank) >= 17) notification("¡Chequeo de nivel superado!", "None");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube2"))
				{
					dialog.text = "Me temo que aún no, Capitán.";
				}
				else
				{
					dialog.text = "No tiene nada que demostrarme ni a mí ni a sus oficiales, e iremos por orden a donde usted diga, pero el marinero de a pie piensa de otra manera. Me temo que habrá problemas, Capitán.";
				}
				link.l1 = "Entonces tendremos que apañarnos con quien podamos. Tu participación es obligatoria, Alonso.";
				link.l1.go = "AlonsoNaPalube_LiteGroup";
				link.l2 = "Hmm... Bueno, necesito pensarlo bien. Quizá retomemos esta cuestión más adelante.";
				link.l2.go = "AlonsoNaPalube_Exit";
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) < 50) notification("¡Habilidad insuficientemente desarrollada! (50)", SKILL_Leadership);
				if (sti(pchar.rank) < 17) notification("¡Se requiere nivel 17!", "None");
			}
		break;
		
		case "AlonsoNaPalube_Vpered":
			dialog.text = "Es un Snow. Dicen que una verdadera belleza con un temperamento feroz. Yo no me preocuparía por ella. Lo más probable es que toda la tripulación esté esclavizada en tierra mientras el barco está a salvo oculto en los recovecos de la costa. Cuando ganemos, podremos llevárnosla como premio de la costa.";
			link.l1 = "Reúne a los hombres. Hoy es un buen día, la fortuna estará de nuestro lado.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_AlonsoNaPalube_Vpered");
		break;
		
		// Диалог в таверне с Блеквудом
		case "LadyBeth_DialogInCity": // главное меню
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Fourth"))
			{
				dialog.text = "Me alegro de verle, capitán. Creo que ya hemos hablado de todo.";
				link.l1 = "En efecto. Adiós.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LadyBeth_DialogInCity_again";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Third"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", Albert.";
				link.l1.go = "LadyBeth_DialogInCity_Third_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", capitán Blackwood.";
				link.l1.go = "LadyBeth_DialogInCity_Second_1";
				break;
			}
			if (startHeroType == 4)
			{
				dialog.text = "...";
				link.l1 = "Hola. ¿Es usted el Capitán Blackwood?";
				link.l1.go = "LadyBeth_DialogInCity_First_Helena_1";
			}
			else
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+". ¿Es usted el Capitán Albert Blackwood? ¿Estoy en lo correcto?";
				link.l1.go = "LadyBeth_DialogInCity_First_1";
			}
		break;
		
		case "LadyBeth_DialogInCity_again": // повтор
			dialog.text = "Me alegro de verle, capitán. Creo que ya hemos hablado de todo.";
			link.l1 = "En efecto. Adiós.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LadyBeth_DialogInCity_again";
		break;

		case "LadyBeth_DialogInCity_First_1": // первый диалог
			dialog.text = "Sí, soy yo. ¿Y usted?";
			link.l1 = "Capitán "+GetFullName(pchar)+". Dirijo la nave '" + PChar.Ship.Name + "'.";
			link.l1.go = "LadyBeth_DialogInCity_First_2";
		break;

		case "LadyBeth_DialogInCity_First_2":
			dialog.text = "Capitán... ¿Has estado en Caimán?";
			link.l1 = "Acabo de pasar.";
			link.l1.go = "LadyBeth_DialogInCity_First_3";
		break;

		case "LadyBeth_DialogInCity_First_3":
			dialog.text = "¿Has oído algo sobre unos tesoros allí?";
			link.l1 = "No, nada específico.";
			link.l1.go = "LadyBeth_DialogInCity_First_4";
		break;

		case "LadyBeth_DialogInCity_First_4":
			dialog.text = "¿Rastros de españoles? ¿Armas antiguas? ¿Monedas de la época de los conquistadores?";
			link.l1 = "No he encontrado nada parecido.";
			link.l1.go = "LadyBeth_DialogInCity_First_5";
		break;

		case "LadyBeth_DialogInCity_First_5":
			dialog.text = "¿Leyendas locales? ¿Historias sobre Cortés? ¿Algo sobre enterramientos?";
			link.l1 = "Lo siento, Capitán, pero no tengo esa información. Y esto ya empieza a parecer un interrogatorio.";
			link.l1.go = "LadyBeth_DialogInCity_First_6";
		break;

		case "LadyBeth_DialogInCity_First_6":
			dialog.text = "Pido disculpas... Es una mala costumbre de un antiguo oficial. Es sólo que... esto es extremadamente importante para mí.";
			link.l1 = "¿Por qué le interesa tanto Caimán en concreto?";
			link.l1.go = "LadyBeth_DialogInCity_First_7";
		break;

		case "LadyBeth_DialogInCity_First_7":
			dialog.text = "No es importante. Una vez más, pido disculpas.";
			link.l1 = "Entiendo. Buena suerte en sus búsquedas.";
			link.l1.go = "LadyBeth_DialogInCity_First_8";
		break;

		case "LadyBeth_DialogInCity_First_8":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Buenas noches";
			else sStr = "Un buen día para usted";
			dialog.text = "Venga a verme si encuentra algo que merezca la pena. Me gustaría conversar con otro capitán... con alguien que entienda el mar. Que tenga un buen día. " + sStr + ".";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_First_9";
		break;
		
		case "LadyBeth_DialogInCity_First_9":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_1": // первый диалог с Элен
			dialog.text = "En carne y hueso. Y usted... ¿La capitana Helen MacArthur? La protegida de Jan Svenson, ¿verdad? He oído hablar de ti.";
			link.l1 = "Está bien informado, Capitán Blackwood. Pero no me sorprende que un oficial inglés sepa de mí.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_2";
		break;

		case "LadyBeth_DialogInCity_First_Helena_2":
			dialog.text = "Antiguo oficial. Y todos los casacas rojas saben de ti y tus... preferencias únicas de la Corona. El sándalo, como dicen, no huele. Y la historia de cómo tu padre Sean MacArthur te llevó al mar desde niño y te hizo capitán se ha convertido en una especie de leyenda en la flota.";
			link.l1 = "¿Y qué se siente al conocer a esta leyenda?";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_3";
		break;

		case "LadyBeth_DialogInCity_First_Helena_3":
			dialog.text = "A mí personalmente me impresiona. Aunque muchos de mis antiguos colegas, debo admitir, lo encuentran bastante irritante. Pero para ser capitán hace falta algo más que un nacimiento noble o una patente real, ¿no?";
			link.l1 = "Cierto. Se necesitan conocimientos, experiencia y una disposición constante a demostrar tu competencia. Especialmente en mi caso.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_4";
		break;

		case "LadyBeth_DialogInCity_First_Helena_4":
			dialog.text = "Exacto. En el mar, como en la vida, lo que importa no son los títulos, sino los resultados. Encantado de conocerlo, capitana MacArthur. Espero que nos volvamos a ver. ¿Quizá pase a tomar una copa de vino cuando regrese de mi expedición?";
			link.l1 = "Tal vez. Buena suerte en sus búsquedas, Capitán.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_5_harizma";
			link.l2 = "No me interesa. Pero buena suerte en sus búsquedas, Capitán.";
			link.l2.go = "LadyBeth_DialogInCity_First_Helena_5_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_harizma":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_oruzhie":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_1": // второй диалог
			dialog.text = "¡Ah, capitán "+pchar.lastname+"! Me alegro de verle. ¿Quiere sentarse?";
			link.l1 = "Con mucho gusto.";
			link.l1.go = "LadyBeth_DialogInCity_Second_2";
		break;

		case "LadyBeth_DialogInCity_Second_2":
			dialog.text = "Capitán... dígame, ¿qué significan para usted los verdaderos tesoros?";
			link.l1 = "Un verdadero tesoro es el amor. La persona adecuada a tu lado. No hay nada peor que estar solo.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love";
			link.l2 = "Dinero, por supuesto. ¿Qué otra cosa podría ser un tesoro?";
			link.l2.go = "LadyBeth_DialogInCity_Second_3_sokrovisha";
			link.l3 = "Equipos valiosos y únicos. Una buena espada o pistola vale más que el oro.";
			link.l3.go = "LadyBeth_DialogInCity_Second_3_oruzhie";
			link.l4 = "Conocimientos. El tesoro más valioso es lo que tienes en la cabeza.";
			link.l4.go = "LadyBeth_DialogInCity_Second_3_znania";
		break;

		case "LadyBeth_DialogInCity_Second_3_love":
			if (startHeroType == 4)
			{
				dialog.text = "¿Amor? Hmm... No esperaba tal respuesta de la hija de un pirata... Yo estaba comprometido con Elizabeth. La hija del dueño de una plantación de Barbados. Pero su padre... decidió que yo no tenía suficiente dinero. ¿Qué podía ofrecerle a su hija además de mi amor? Tuvo suerte, capitana MacArthur. Tuviste un padre que valoró más tus habilidades que tu dote.";
				link.l1 = "Quizá no se trate de suerte, sino de que el amor verdadero no se mide en oro. Mi padre lo entendía. ¿Y tu prometida? ¿Comparte la opinión de su padre?";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_1";
			}
			else
			{
				dialog.text = "¿Amor? Sí... Tal vez tengas razón. I... Estuve comprometida. En Barbados. Nos amábamos, pero... su padre me consideró un partido indigno. ¡Ja! No lo suficientemente rico. Es por eso que estoy aquí, en busca de tesoros para demostrar que están equivocados. ¿Tal vez sea en vano?";
				link.l1 = "¿Quizás deberías hablar con ella? Al diablo con el dueño de la plantación.";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_2";
			}
			AddComplexLandExpToScill(100, 100, 0);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_2":
			dialog.text = "Hablar... Sí, tal vez. ¿Pero qué diría? ¿'Lo siento, no pude darte una vida decente'? No, debo devolver un ganador, o no volver en absoluto.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;

		case "LadyBeth_DialogInCity_Second_3_love_Helena_1":
			dialog.text = "¿Elizabeth? No... ella me ama. Pero yo... No podía dejarla vivir en la pobreza. Se merece algo mejor. Y debo probar que soy digno de ella.";
			link.l1 = "A veces el orgullo obstaculiza la felicidad más que la pobreza, Capitán.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_2";
		break;

		case "LadyBeth_DialogInCity_Second_3_love_Helena_2":
			dialog.text = "No puedo volver con las manos vacías. Simplemente no puedo. Pido disculpas, tengo mucho trabajo. Fue un placer charlar con usted, capitana MacArthur.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;

		case "LadyBeth_DialogInCity_Second_3_sokrovisha":
			dialog.text = "Qué respuesta tan banal. Pero es difícil discutirla. De hecho, cuando creces en los barrios bajos de Bristol, cuando tienes que luchar por las sobras... empiezas a entender el verdadero valor del dinero. No es lujo. Es libertad. La capacidad de no volver nunca a esa inmundicia de la que saliste con tanta dificultad.";
			link.l1 = "Estoy de acuerdo. El dinero resuelve la mayoría de los problemas. Y si no los resuelve, es que simplemente no hay suficiente.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_sokrovisha_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "LadyBeth_DialogInCity_Second_3_sokrovisha_2":
			dialog.text = "Exacto. Entiéndelo. El dinero no te hace feliz, pero su ausencia te hace infeliz seguro. Lo sé muy bien...";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;

		case "LadyBeth_DialogInCity_Second_3_oruzhie":
			dialog.text = "¿Interesante, práctico? Tengo un arcabuz... uno de verdad, de la época de los conquistadores. Un regalo de cierto sacerdote. A veces pienso que vale más que todo el oro que he encontrado. Pero... no resolverá los problemas.";
			link.l1 = "Las buenas armas pueden resolver muchos problemas. Y nunca te traicionarán.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;

		case "LadyBeth_DialogInCity_Second_3_oruzhie_2":
			dialog.text = "Eso es cierto. Pero algunas batallas no pueden ganarse por la fuerza de las armas.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;

		case "LadyBeth_DialogInCity_Second_3_znania":
			dialog.text = "Conocimiento... Sí, entiendo. He estudiado todo lo que he podido sobre los conquistadores, sobre tesoros. He compilado todo un manual sobre la búsqueda de tesoros. Ideé un sistema de ejercicios regulares e incentivos materiales para la compañía de fusileros del barco.\nCualquier capitán estaría encantado de tener mi manual. Pero todo este conocimiento... Es inútil si no conduce a resultados. A resultados reales.";
			link.l1 = "Pero son los conocimientos los que ayudan a conseguir resultados. Sin él, cualquier búsqueda no es más que vagar en la oscuridad.";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "LadyBeth_DialogInCity_Second_4":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Bueno, es tarde, y tengo mucho trabajo";
			else sStr = "Bueno, tengo mucho trabajo";
			dialog.text = "" + sStr + "... Gracias por la conversación, capitán. Fue realmente interesante.";
			link.l1 = "Gracias a ti también. "+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;

		case "LadyBeth_DialogInCity_Second_5":
			DialogExit();

			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Third = true;
		break;

		case "LadyBeth_DialogInCity_Third_2": // третий диалог
			dialog.text = "¡Ah, "+pchar.name+"! Me alegra verte. Traigo excelentes noticias: por fin he encontrado una solución a mis problemas. ¡Pronto partiré en una expedición, y esta vez volveré con un verdadero tesoro! Por cierto, un consejo de amigo: mantente alejado de las Caimán. Es mi territorio.";
			link.l1 = "Caimán no te pertenece, Albert. No tienes los derechos de la corona. Eso es piratería.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma";
			link.l2 = "¿Me estás amenazando, Blackwood?";
			link.l2.go = "LadyBeth_DialogInCity_Third_3_oruzhie";
		break;

		case "LadyBeth_DialogInCity_Third_3_harizma":
			dialog.text = "¿Derechos de la Corona? Deberías haber vivido en los barrios bajos de Bristol, "+pchar.name+", entonces entenderías lo que valen esos papeles. Cuando tienes hambre, la ley no tiene sentido. Sin embargo... tienes razón. Formalmente, no tengo derechos sobre la isla.\nPero he encontrado allí lo que he estado buscando durante años. Y no dejaré que nadie me lo quite.";
			link.l1 = "Espero que entiendas que deambulas por un camino peligroso.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;

		case "LadyBeth_DialogInCity_Third_3_harizma_2":
			dialog.text = "Siempre entendí que mi camino no sería fácil. Adiós, "+pchar.name+". Tal vez nos encontremos de nuevo.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;

		case "LadyBeth_DialogInCity_Third_3_oruzhie":
			dialog.text = "¿Amenazar? No, en absoluto. Sólo es un consejo amistoso de un capitán a otro. Las Caimán son peligrosas... especialmente para los que interfieren en mis asuntos.";
			link.l1 = "Recordaré tus 'consejos'. Buena suerte en las Caimán.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;

		case "LadyBeth_DialogInCity_Third_3_oruzhie_2":
			dialog.text = "Buena suerte, Capitán. Espero que no la necesite. Hasta la vista.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_4":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Fourth = true;
		break;
		
		// Ловушка, абордаж в каюте
		case "LadyBeth_abordage":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "¡¿Tú?! ¿Crees que me rendiré? ¿Crees que volveré a la pobreza? ¡Prefiero morir a morir de hambre en los barrios bajos otra vez! ¡Sin piedad, sin recompensa, sin victoria! Debajo de la litera hay un barril de pólvora... ¡Todos nos iremos al fondo!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
			else
			{
				dialog.text = "¡¿Quién eres tú para atacarme?! ¿Crees que me rendiré? ¡No! ¡Prefiero morir a morir de hambre en los barrios bajos otra vez! ¡Sin piedad, sin recompensa, sin victoria! Debajo de la litera hay un barril de pólvora... ¡Iremos todos al fondo!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
		break;
		
				// Блеквуд разговаривает с ГГ перед битвой на Каймане
		case "LadyBeth_BlackWood_Boss":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "¡Capitán! Se lo advertí. Ahora pagarás el precio de tu curiosidad.";
			}
			else
			{
				dialog.text = "¡¿Quién eres y cómo te atreves a invadir mi territorio?! ¡Esta isla es mía!";
			}
			link.l1 = "Ya veremos, Blackwood. Hoy habrá un obseso menos en este mundo.";
			link.l1.go = "LadyBeth_BlackWood_Boss_oruzhie_1";
			link.l2 = "Resolvamos esto pacíficamente, Blackwood. Puedo dejar.";
			link.l2.go = "LadyBeth_BlackWood_Boss_torgovlya_1";
			link.l3 = "¡Blackwood, eres un hombre razonable! ¡Usted es un oficial! ¡Tienes la bandera real ondeando sobre tu campamento, por el amor de Dios! ¿No podemos llegar a un acuerdo?";
			link.l3.go = "LadyBeth_BlackWood_Boss_harizma_1";
		break;

		case "LadyBeth_BlackWood_Boss_oruzhie_1":
			dialog.text = "¿Obsesionado? ¡Ja! ¡Sólo soy un hombre que sabe lo que quiere!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;

		case "LadyBeth_BlackWood_Boss_torgovlya_1":
			dialog.text = "¿Irme? ¿Después de lo que has visto? ¡No, no, no! ¡Nadie debe saber lo que he encontrado aquí! ¡Nadie!";
			link.l1 = "Te doy mi palabra de que no se lo diré a nadie. Lo juro por el honor de un capitán.";
			link.l1.go = "LadyBeth_BlackWood_Boss_torgovlya_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "LadyBeth_BlackWood_Boss_torgovlya_2":
			dialog.text = "No hay honor en este mundo, Capitán. Sólo hay suciedad, pobreza y desprecio. Lo lamento, pero debes morir aquí.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
		break;

		case "LadyBeth_BlackWood_Boss_harizma_1":
			dialog.text = "He pensado sobre ello. Y me di cuenta de que esta es mi única oportunidad. O encuentro el oro de Cortez, o... nada. ¿Entiendes? ¡NADA! ¡No volveré a mi vida anterior! ¡No volveré a la suciedad y la pobreza! ¡Es mejor morir aquí!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;

		case "LadyBeth_BlackWood_Boss_2":
			dialog.text = "¡A la batalla! ¡Bullock, Fraser, disparen si se acercan! ¡Hopkins, a la carga!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_CaimanKino_11");
		break;
		
		// Диалоги с офицерами
		case "LadyBeth_Helena_1": // Элен
			dialog.text = "¿Se encuentra bien?";
			link.l1 = "Sí, todo va bien. ¿Y usted?";
			link.l1.go = "LadyBeth_Helena_2";
			DelLandQuestMark(npchar);
		break;

		case "LadyBeth_Helena_2":
			dialog.text = "Vivo. Pero estas batallas campales no son para mí. Dame una cubierta bajo mis pies y destrozaré cualquier barco, pero aquí... es un lugar extraño. Hacer desembarcar a cien lobos de mar, clavar picos, construir fortificaciones... Yo no podría hacer eso.";
			link.l1 = "Blackwood sabía cómo inspirar a su tripulación.";
			link.l1.go = "LadyBeth_Helena_3";
		break;

		case "LadyBeth_Helena_3":
			dialog.text = "Oí hablar de él en Bluefield. Muchos marineros ingleses hablaban de él con respeto. El mejor oficial de la flota, una carrera brillante... y de repente lo tiró todo por la borda para cazar tesoros.";
			link.l1 = "¿Qué opina de él?";
			link.l1.go = "LadyBeth_Helena_4";
		break;

		case "LadyBeth_Helena_4":
			dialog.text = "Creo que el ejemplo de Blackwood muestra claramente la carga de responsabilidad que nosotros... quiero decir tú, llevas ante tus hombres. Por favor, no te conviertas en el mismo tipo de capitán que él.";
			link.l1 = "Lo intentaré, Helen.";
			link.l1.go = "LadyBeth_Helena_5";
		break;

		case "LadyBeth_Helena_5":
			dialog.text = "Gracias, mi Capitán. Sé que tendrá éxito.";
			link.l1 = "Lo haremos.";
			link.l1.go = "LadyBeth_Helena_6";
		break;

		case "LadyBeth_Helena_6":
			dialog.text = "Lo haremos.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Helena_7";
		break;

		case "LadyBeth_Helena_7":
			DialogExit();
			Return_HelenaOfficer();
		break;
		
		case "LadyBeth_Mary_1": // Мэри
			dialog.text = "Charles... qué espantoso es esto.";
			link.l1 = "¿Estás bien, Mary? Aguantaste como una verdadera soldado.";
			link.l1.go = "LadyBeth_Mary_2";
			DelLandQuestMark(npchar);
		break;

		case "LadyBeth_Mary_2":
			dialog.text = "No, no me encuentro bien, sí, ¿eh? ¡Mira a esta gente! Trabajaron hasta el agotamiento, vivieron con hambre, murieron de enfermedades... ¿Y para qué? Por el oro que podría ni siquiera existir.";
			link.l1 = "Blackwood creía que estaba aquí.";
			link.l1.go = "LadyBeth_Mary_3";
		break;

		case "LadyBeth_Mary_3":
			dialog.text = "Esta casaca roja... es como la mía. Un oficial inglés... De repente pensé en mis padres, sí, ¿eh? Sobre mis raíces... sobre lo que nunca conocí. ¿Tal vez yo también soy uno de esos?";
			link.l1 = "¿Uno de esos?";
			link.l1.go = "LadyBeth_Mary_4";
		break;

		case "LadyBeth_Mary_4":
			dialog.text = "Los que buscan algo que puede que ni siquiera exista. Y luego se pierden en la búsqueda... Me gustaría hablar de esto más tarde, sí, ¿eh? Cuando dejemos este terrible lugar.";
			link.l1 = "Por supuesto, Mary.";
			link.l1.go = "LadyBeth_Mary_5";
		break;

		case "LadyBeth_Mary_5":
			dialog.text = "¿Qué te parece si lo enterramos primero, por favor? Aunque no se lo merezca. Por el bien del hombre que una vez fue.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Mary_6";
		break;
		
		case "LadyBeth_Mary_6":
			DialogExit();
			Return_MaryOfficer();
		break;
		
		case "LadyBeth_Tichingitu_1": // Тичингиту
			dialog.text = "Capitán, Tichingitu ver mal lugar aquí. Muy mal lugar.";
			link.l1 = "¿A qué te refieres?";
			link.l1.go = "LadyBeth_Tichingitu_2";
			DelLandQuestMark(npchar);
		break;

		case "LadyBeth_Tichingitu_2":
			dialog.text = "Esta isla ahora está maldita. Tierra absorber demasiada sangre y lágrimas. Todos los que cavar aquí, respiran esta maldición.";
			link.l1 = "¿Crees que Blackwood estaba poseído?";
			link.l1.go = "LadyBeth_Tichingitu_3";
		break;

		case "LadyBeth_Tichingitu_3":
			dialog.text = "No sólo poseído. Él ser ... cómo decirlo ... recipiente vacío. Algo entra en él y expulsa su alma. He visto esto antes. Cuando chamán de mi tribu llevar sacrificio humano a espíritus. Ese chamán tenía la misma mirada.";
			link.l1 = "Pero, ¿qué puede causar semejante obsesión?";
			link.l1.go = "LadyBeth_Tichingitu_4";
		break;

		case "LadyBeth_Tichingitu_4":
			dialog.text = "Hombre con vacío interior fácil de llenar con otros pensamientos. Alguien encuentra su debilidad y la utiliza. Tichingitu casi sentir lástima por este hombre.";
			link.l1 = "¿Casi?";
			link.l1.go = "LadyBeth_Tichingitu_5";
		break;

		case "LadyBeth_Tichingitu_5":
			dialog.text = "Sí, casi. Cada guerrero es responsable de su propia elección. Aunque los demonios le susurren al oído.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Tichingitu_6";
		break;
		
		case "LadyBeth_Tichingitu_6":
			DialogExit();
			Return_TichingituOfficer();
		break;
		
		case "LadyBeth_Irons_1": // Томми
			dialog.text = "¡Maldita sea, Capitán! ¡Mira esto! ¡Como en los viejos tiempos!";
			link.l1 = "Sabes bien cómo es la guerra en tierra.";
			link.l1.go = "LadyBeth_Irons_2";
			DelLandQuestMark(npchar);
		break;

		case "LadyBeth_Irons_2":
			dialog.text = "Me recuerda a la batalla de Naseby. Nuestra ala de caballería chocó con la caballería de Rupert. Lucharon con la misma ferocidad por su rey.";
			link.l1 = "¿Qué opina de Blackwood?";
			link.l1.go = "LadyBeth_Irons_3";
		break;

		case "LadyBeth_Irons_3":
			dialog.text = "Este Blackwood era o un genio o un completo chiflado. Creo que ambas cosas. ¿Sabes lo que me sorprende? Sus hombres. Muchos de ellos son ex militares. No unas ratas callejeras, sino gente de verdad. Y todos lo siguieron en esta locura. Incluso la infantería de marina de Fox. ¡Ja! ¡Ahora hay alguien que estará encantado con la carnicería de hoy! Nunca les perdonó que desertaran.";
			link.l1 = "¿Tal vez sea por el dinero?";
			link.l1.go = "LadyBeth_Irons_4";
		break;

		case "LadyBeth_Irons_4":
			dialog.text = "No, hay algo más. Este tipo tenía poder sobre ellos. Verdadero poder. Y también escuché que estaba comprometido con una chica rica de Barbados. Es extraño que no se casara con ella después de conseguir todos estos tesoros. El típico soldado que no sabe cuándo terminar una la guerra.";
			link.l1 = "Gracias, Tommy. Eres un verdadero hombre que reflexiona.";
			link.l1.go = "LadyBeth_Irons_5";
		break;

		case "LadyBeth_Irons_5":
			dialog.text = "¿Eh?";
			link.l1 = "Nada.";
			link.l1.go = "LadyBeth_Irons_6";
		break;
		
		case "LadyBeth_Irons_6":
			DialogExit();
			Return_IronsOfficer();
		break;
		
case "LadyBeth_Knippel_1": // Книппель
			dialog.text = "Qué amargo es ver esto, Capitán. ¡¿En qué nos hemos sumido?!";
			link.l1 = "¿Nosotros?";
			link.l1.go = "LadyBeth_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Knippel_2":
			dialog.text = "¡La flota inglesa! ¡Sólo mira los pequeños puntos rojos que yacen en el montón de esa escoria muerta!";
			link.l1 = "Parte de esa 'escoria' es nuestra gente, Charlie. Entiendo tus sentimientos, pero...";
			link.l1.go = "LadyBeth_Knippel_3";
		break;
		
		case "LadyBeth_Knippel_3":
			dialog.text = "¡A la mierda, señor!";
			link.l1 = "Entiendo tus sentimientos, pero será mejor que dirijas tu ira y decepción hacia Blackwood. Él es quien desertó de tu amada flota inglesa y los trajo aquí.";
			link.l1.go = "LadyBeth_Knippel_4";
			link.l2 = "Indeed. Vamos, el día aún no ha terminado.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_4":
			dialog.text = "¡Sólo seguían a su comandante!";
			link.l1 = "¿Como seguiste a Fleetwood?";
			link.l1.go = "LadyBeth_Knippel_5";
			link.l2 = "En efecto. Vamos, el día aún no ha terminado.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_5":
			dialog.text = "¡Como si te siguiera!";
			link.l1 = "Espero demostrar que soy mejor capitán que Blackwood y Fleetwood. Vamos, el día aún no ha terminado.";
			link.l1.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_6":
			dialog.text = "Sí, Capitán. Y cuando termine... beberé hasta que termine la próxima.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Knippel_7";
		break;
		
		case "LadyBeth_Knippel_7":
			DialogExit();
			Return_KnippelOfficer();
		break;
		
		case "LadyBeth_Alonso_1": // Алонсо
			dialog.text = "¡Madre de Dios, capitán! ¿Está usted bien?";
			link.l1 = "Eso está por verse. ¿Cuántos hombres hemos perdido?";
			link.l1.go = "LadyBeth_Alonso_2";
			DelLandQuestMark(npchar);
		break;

		case "LadyBeth_Alonso_2":
			dialog.text = "¿Muertos? En esta aventura hemos perdido "+sti(pchar.SailorDiedInBattleInfo)+" hombres. No quiero ser insistente, capitán, pero... ¡le advertí!";
			link.l1 = "Ignoraré ese comentario porque hoy te has lucido, Alonso. ¿De dónde vienen tantos talentos?";
			link.l1.go = "LadyBeth_Alonso_3";
		break;

		case "LadyBeth_Alonso_3":
			dialog.text = "Algún día le contaré esa historia, capitán. Si sobrevivimos, claro.";
			link.l1 = "¿Tienes más consejos para mí?";
			link.l1.go = "LadyBeth_Alonso_4";
		break;

		case "LadyBeth_Alonso_4":
			dialog.text = "Si hubiera un tesoro aquí, ya lo habrían encontrado. Pero aún así deberíamos registrar la isla y buscar supervivientes, y luego decidir qué hacer con ellos. Y no hay que olvidar el barco de Blackwood: he oído hablar muy bien de esa hermosa Galeota\nSería una pena dejar pasar ese botín, capitán. Por supuesto, solo transmito la opinión de la tripulación al respecto.";
			link.l1 = "Por supuesto. Vamos. ¡El botín nos espera!";
			link.l1.go = "LadyBeth_Alonso_5";
		break;
		
		case "LadyBeth_Alonso_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		// Диалог с матросом в гроте Каймана
		case "LadyBeth_MatrosyInGrot":
			dialog.text = "¡No disparen! ¡Nos rendimos!";
			link.l1 = "¿Quiénes son ustedes?";
			link.l1.go = "LadyBeth_MatrosyInGrot_2";
		break;

		case "LadyBeth_MatrosyInGrot_2":
			dialog.text = "Nosotros... somos de la 'Lady Beth'. La tripulación del Capitán Blackwood. ¿Está... está vivo?";
			link.l1 = "No. Su capitán está muerto.";
			link.l1.go = "LadyBeth_MatrosyInGrot_3";
		break;

		case "LadyBeth_MatrosyInGrot_3":
			dialog.text = "Así que se acabó... Gracias a Dios.";
			link.l1 = "No parece estar de luto por su capitán.";
			link.l1.go = "LadyBeth_MatrosyInGrot_4";
		break;

		case "LadyBeth_MatrosyInGrot_4":
			dialog.text = "No lo entiende. Blackwood era un gran hombre. El mejor capitán que conocí. Pero en los últimos meses... cambió. Se volvió obsesivo, cruel. Nos hizo trabajar día y noche, buscando algo que tal vez ni siquiera exista.";
			link.l1 = "Te llevaré a mi tripulación. Necesitamos marineros experimentados.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda";
			link.l2 = "Ay de los vencidos, muchachos. Ahora su lugar está en mi poder. Si tienes suerte, vivirás para ver alguna plantación en Barbados.";
			link.l2.go = "LadyBeth_MatrosyInGrot_PlusRaby";
		break;

		case "LadyBeth_MatrosyInGrot_PlusKomanda":
			dialog.text = "¿De verdad? ¿No... no tienes miedo de que... de que nos pase algo después de todo esto?";
			link.l1 = "Todo el mundo merece una segunda oportunidad.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda_1";
		break;

		case "LadyBeth_MatrosyInGrot_PlusKomanda_1":
			dialog.text = "Gracias, Capitán. Le juro que no se arrepentirá. Somos buenos marineros. Y ... tal vez ahora las pesadillas se detendrán.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 30;
		break;

		case "LadyBeth_MatrosyInGrot_PlusRaby":
			dialog.text = "¡Gracias, gracias! Al menos estaremos vivos. Sácanos de aquí, por favor. Esta isla... es como si estuviera maldita.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+30);
		break;

		case "LadyBeth_MatrosyInGrot_exit":
			DialogExit();
			for (i=1; i<=8; i++)
			{
				sld = CharacterFromID("LadyBeth_MatrosyPryachutsya_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		// Диалог с матросом на Леди Бет
		case "LadyBeth_EnemyMatros_1":
			dialog.text = "¡¿Qué demonios?! ¿Cómo os atrevéis a atacar a la “Lady” y matar a Jeremy? No saldréis vivos de aquí, sinvergüenzas, el capitán volverá y...";
			link.l1 = "Tu capitán está muerto. Jeremy disparó primero, y me llevo a tu “Lady” como premio lícito pagado con sangre.";
			link.l1.go = "LadyBeth_EnemyMatros_2";
		break;

		case "LadyBeth_EnemyMatros_2":
			dialog.text = "¿El capitán... ¿muerto? ¡Estás mintiendo, perro! ¡No vales ni un botón de su uniforme!";
			link.l1 = "Si ese uniforme significaba algo, era para el Blackwood que ya se fue. Es vuestra elección luchar por un hombre muerto o salvaguardar vuestras vidas.";
			link.l1.go = "LadyBeth_EnemyMatros_3";
		break;

		case "LadyBeth_EnemyMatros_3":
			if (CharacterIsHere("Helena"))
			{
				StartInstantDialog("Helena", "LadyBeth_EnemyMatros_Helena_1", "Quest\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Knippel"))
			{
				StartInstantDialog("Knippel", "LadyBeth_EnemyMatros_Knippel_1", "Quest\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Irons"))
			{
				StartInstantDialog("Irons", "LadyBeth_EnemyMatros_Irons_1", "Quest\LadyBeth_dialog.c");
				break;
			}
			dialog.text = "¡No te daremos la nave sin luchar!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;

		case "LadyBeth_EnemyMatros_Helena_1":
			dialog.text = "Escuchad, chicos. Sé que son leales a su capitán. Eso es digno de respeto. Pero él está muerto, y vosotros estáis vivos. Y debéis decidir cómo seguir viviendo. Os ofrecemos la oportunidad de empezar de nuevo.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;

		case "LadyBeth_EnemyMatros_Knippel_1":
			dialog.text = "Capitán, estos hombres no son enemigos. Sólo seguían órdenes. Muchos de ellos son antiguos marineros de la corona, bien entrenados y disciplinados. Sería un desperdicio no usar sus habilidades. Muchachos, he estado en su lugar más de una vez en mi largo servicio en la flota. Y tomé la decisión correcta. Tomadla también.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
		break;

		case "LadyBeth_EnemyMatros_Irons_1":
			dialog.text = "¡Bueno, marineros! La elección es sencilla, o vivís como prisioneros en la bodega o formáis parte de nuestra tripulación con buenas raciones y una paga regular, o... (se pasa un dedo por la garganta) ¡Yo que vosotros elegiría lo primero!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_10";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;

		case "LadyBeth_EnemyMatros_5":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_6", "Quest\LadyBeth_dialog.c");
		break;

		case "LadyBeth_EnemyMatros_6":
			dialog.text = "...";
			link.l1 = "Formarás parte de mi tripulación.";
			link.l1.go = "LadyBeth_EnemyMatros_7";
			link.l2 = "Ay de los vencidos, muchachos. Ahora su lugar está en mi poder. Si tienes suerte, vivirás para ver alguna plantación en Barbados.";
			link.l2.go = "LadyBeth_EnemyMatros_9";
		break;

		case "LadyBeth_EnemyMatros_7":
			dialog.text = "¿Nos aceptas en tu tripulación? ¿Después de todo esto?";
			link.l1 = "Los buenos marineros siempre son valiosos. Y el Capitán Blackwood sabía cómo elegir a sus hombres.";
			link.l1.go = "LadyBeth_EnemyMatros_8";
		break;

		case "LadyBeth_EnemyMatros_8":
			dialog.text = "Gracias, Capitán. No le defraudaremos..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 12;
		break;

		case "LadyBeth_EnemyMatros_9":
			dialog.text = "Bueno... al menos esa es la única forma en que esta aventura podría haber terminado. Perdónenos, Capitán Blackwood. No lo protegimos.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+12);
		break;

		case "LadyBeth_EnemyMatros_10":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_11", "Quest\LadyBeth_dialog.c");
		break;

		case "LadyBeth_EnemyMatros_11":
			dialog.text = "¡No te daremos la nave sin luchar!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		// Диалог с Элизабет Бишоп
		case "LadyBeth_Elizabeth_1":
			dialog.text = "...";
			link.l1 = "Disculpadme. ¿Eres Elizabeth?";
			if (pchar.sex == "man") link.l1.go = "LadyBeth_Elizabeth_2";
			if (pchar.sex == "woman") link.l1.go = "LadyBeth_Elizabeth_Woman_2";
			DelLandQuestMark(npchar);
		break;

		case "LadyBeth_Elizabeth_2":
			dialog.text = "Sí, soy yo. ¿Y tú quién eres?";
			link.l1 = "Capitán "+GetFullName(pchar)+". Yo... conocía a Albert Blackwood.";
			link.l1.go = "LadyBeth_Elizabeth_3";
		break;

		case "LadyBeth_Elizabeth_3":
			dialog.text = "¿Mi Albert? Dios mío... ¿Está... está bien?";
			link.l1 = "Desafortunadamente, no. Murió en batalla. Luchó hasta el final.";
			link.l1.go = "LadyBeth_Elizabeth_4";
		break;

		case "LadyBeth_Elizabeth_4":
			dialog.text = "I... Lo sospechaba. Tantos años sin una sola palabra... Sabes, lo esperé. Esperé mucho tiempo. Padre dijo que Albert sólo tenía que esperar un ascenso. El gobernador ya lo había decidido todo, era cuestión de unos meses. Pero Albert... se tomó la conversación de otra manera. Dijo que volvería adinerado, digno de mi mano. Y se fue. Sólo... se fue.";
			link.l1 = "Pensó en ti hasta su último día.";
			link.l1.go = "LadyBeth_Elizabeth_5";
		break;

		case "LadyBeth_Elizabeth_5":
			dialog.text = "Qué tontería. No necesitaba sus tesoros. Lo amaba a él, no a su dinero. Estaba lista para huir con él... pero era tan orgulloso. Esperé una carta, cualquier palabra... Y entonces sólo llegó este extraño manual. Un documento tan frío, tan calculador... nada que ver con el Albert que yo conocía. Fue entonces cuando me di cuenta de que lo había perdido.";
			link.l1 = "Entre sus cosas, encontré esto.";
			link.l1.go = "LadyBeth_Elizabeth_6";
		break;

		case "LadyBeth_Elizabeth_6":
			dialog.text = "¿Un mapa a mi casa? ¿Yo era su principal tesoro? Qué ironía. Buscó riquezas por todo el Caribe, y lo único que le importaba siempre estaba aquí. Espera. Tengo algo para ti. Este es el manual de Albert. Me lo envió hace un año. Dijo que le ayudaría a encontrar tesoros y volver conmigo. Ahora te será más útil.";
			link.l1 = "Gracias, Elizabeth. Siento que todo haya acabado así.";
			link.l1.go = "LadyBeth_Elizabeth_7";
			GiveItem2Character(PChar, "talisman18");
		break;

		case "LadyBeth_Elizabeth_7":
			dialog.text = "Y me casé con el Sr. Bishop, capitán. Mi padre insistió. No conoces a este hombre... y no querrías conocerlo. Todos los días pienso en cómo habría sido mi vida si Albert hubiera... regresado.";
			link.l1 = "Ahora también lo pensaré.";
			link.l1.go = "LadyBeth_Elizabeth_8";
		break;

		case "LadyBeth_Elizabeth_8":
			dialog.text = "Adiós, Capitán. Y... cuídese. No persigas fantasmas.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;

		case "LadyBeth_Elizabeth_Woman_2":
			dialog.text = "Sí, soy yo.";
			link.l1 = "Capitana Ellen MacArthur. Yo... conocía a Albert Blackwood.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_3";
		break;

		case "LadyBeth_Elizabeth_Woman_3":
			dialog.text = "¿Mi Albert? Dios mío... Él... ¿Y tú quién eres?";
			link.l1 = "Capitana Helen MacArthur, acabo de decir. Mando mi propia nave.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_4";
		break;

		case "LadyBeth_Elizabeth_Woman_4":
			dialog.text = "¿Capitana? ¿Una mujer capitán? Tú... ¿Estabas con Albert? ¿De qué forma, lo conocía?";
			link.l1 = "Sólo como capitán. Lo siento, pero Albert está muerto. Fui testigo de su batalla final.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_5";
		break;

		case "LadyBeth_Elizabeth_Woman_5":
			dialog.text = "Comprendo. Perdona mis sospechas. Es sólo que... El Capitán Blackwood siempre atrajo la atención de las mujeres. Incluso aquí, en Barbados. Especialmente aquí.";
			link.l1 = "Le querías.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_6";
		break;

		case "LadyBeth_Elizabeth_Woman_6":
			dialog.text = "De todo corazón. Mi padre dijo que Albert sólo tenía que esperar un ascenso. Era cuestión de unos meses. Pero él entendió las palabras de padre como un rechazo debido a la pobreza. Dijo que volvería con tesoros. Y se fue.";
			link.l1 = "¡Los hombres y su orgullo!";
			link.l1.go = "LadyBeth_Elizabeth_Woman_7";
		break;

		case "LadyBeth_Elizabeth_Woman_7":
			dialog.text = "Tienes suerte, capitana MacArthur. Eres libre. Navegas adonde quieres. Sin dueños de plantaciones, sin padres que decidan tu destino y sin maridos que te consideran de su propiedad.";
			link.l1 = "La libertad tiene un alto precio. Y hay que defenderla todos los días.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_8";
		break;

		case "LadyBeth_Elizabeth_Woman_8":
			dialog.text = "Puede que tenga algo que te ayude en este asunto. Toma este es su manual de la caza del tesoro. Albert me lo envió hace un año. Dijo que era lo mejor que había creado. Que le ayudaría a hacerse rico y a volver conmigo. Pero con cada página, se parecía cada vez menos al Albert que yo conocía.";
			link.l1 = "Gracias. Me lo quedo.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_9";
			GiveItem2Character(PChar, "talisman18");
		break;

		case "LadyBeth_Elizabeth_Woman_9":
			dialog.text = "Por favor, capitana... valore su libertad. Me casé con el Coronel Bishop. Un hombre al que hasta mi padre teme. Si yo fuera libre, como tú... todo sería diferente.";
			link.l1 = "Lo sé.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_10";
		break;

		case "LadyBeth_Elizabeth_Woman_10":
			dialog.text = "Adiós, Capitán. Y que los buenos vientos te seas propicios.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		// диалог с Диего де Ланда
		case "LadyBeth_DiegoDeLanda_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "¿Has visto a Lady Bishop? Es una historia triste, ¿no?";
				link.l1 = "¿Quién es usted?";
				link.l1.go = "LadyBeth_DiegoDeLanda_First_1";
			}
			else
			{
				dialog.text = "Hola, Capitán.";
				link.l1 = "¡Espera! ¡Ya nos conocíamos! ¿Qué haces en Barbados?";
				link.l1.go = "LadyBeth_DiegoDeLanda_Second_1";
			}
		break;

		case "LadyBeth_DiegoDeLanda_First_1":
			dialog.text = "\nSirvo a la parroquia de Santa María. Pocos católicos de Barbados encuentran consuelo en nuestra iglesia.";
			link.l1 = "¿Conoces a Elizabeth?";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_2";
		break;

		case "LadyBeth_DiegoDeLanda_First_2":
			dialog.text = "Ah, sí. Pobre mujer. Su marido... no es un hombre muy amable. Dicen que sus plantaciones son las más productivas de Barbados y las más crueles. ¿ Sabes cuántos esclavos mueren allí cada mes? Hace poco mató a golpes a un médico inglés, un hombre de gran intelecto y talento. Pero su destino no es mucho mejor, créeme.";
			link.l1 = "Parece bien informado.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_3";
		break;

		case "LadyBeth_DiegoDeLanda_First_3":
			dialog.text = "La gente viene a mí para confesarse, Capitán. Escucho lo que temen decir incluso a sus seres queridos. Sus miedos, sus pecados... su dolor.";
			link.l1 = "¿No teme la persecución? No es fácil para un sacerdote católico vivir en los territorios ingleses.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_4";
		break;

		case "LadyBeth_DiegoDeLanda_First_4":
			dialog.text = "Dime... ¿buscabas específicamente a Blackwood? Es curioso. ¿Pero por qué? Era peligroso y necio. ¿Cuál es su pasión, Capitán? ¿Qué lo impulsa?";
			link.l1 = "Eso no es asunto tuyo.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_5";
		break;

		case "LadyBeth_DiegoDeLanda_First_5":
			dialog.text = "No lo entiendo. A los otros, sí. Pero tú, todavía no.";
			link.l1 = "¿Otros?";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_6";
		break;

		case "LadyBeth_DiegoDeLanda_First_6":
			dialog.text = "Uno, por ejemplo, lucha por la justicia. O había otro... obsesionado con las oscuras aguas de la muerte. La gente se pierde tan fácilmente en sus deseos. ¿No es verdad?";
			link.l1 = "Eres un sacerdote extraño, Santo Padre.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_7";
		break;

		case "LadyBeth_DiegoDeLanda_First_7":
			dialog.text = "...";
			link.l1 = "Creo que me iré ahora.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_8";
		break;

		case "LadyBeth_DiegoDeLanda_First_8":
			dialog.text = "Por supuesto. Su trabajo apenas comienza, Capitán.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Diego_2");
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_1":
			dialog.text = "Sirvo a la parroquia de Santa María. ¿Ha visto a Lady Bishop? Un triste destino. Pero, me temo, merecido.";
			link.l1 = "La última vez hablaste con acertijos. ¿Lo volverás a hacer?";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_2";
		break;

		case "LadyBeth_DiegoDeLanda_Second_2":
			dialog.text = "\nEl verdadero enigma está ante mí ahora. Has coleccionado muchas reliquias... interesantes. La Biblia, la carta. ¿Te gusta coleccionar esas cosas? ¿Eres coleccionista?";
			link.l1 = "¿Cómo sabes lo del manual?";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_3";
		break;

		case "LadyBeth_DiegoDeLanda_Second_3":
			dialog.text = "¿Un cazador de trofeos?";
			link.l1 = "Repito mi pregunta: ¿cómo sabes lo del manual?";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_4";
		break;

		case "LadyBeth_DiegoDeLanda_Second_4":
			dialog.text = "¿Buscas emociones fuertes?";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_5";
		break;

		case "LadyBeth_DiegoDeLanda_Second_5":
			dialog.text = "Ah, por supuesto. Bueno, Capitán, no lo entretendré.";
			link.l1 = "Espere un momento, Santo Padre. Aún no ha respondido a mi pregunta.";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_6";
		break;

		case "LadyBeth_DiegoDeLanda_Second_6":
			dialog.text = "Oh, Capitán. No puedo. A veces las respuestas duelen más que cualquier ignorancia. Ve en paz. Y cuida tu colección... de trofeos. Pueden ser útiles en el viaje que te espera.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Diego_2");
		break;
	}
} 