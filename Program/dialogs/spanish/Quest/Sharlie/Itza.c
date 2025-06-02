// диалоги Уракана, Канека и прочих индейцев ица
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
			dialog.text = "¿Hay algo que necesites?";
			link.l1 = "No, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// ица-горожане
		case "itza_ctz":
			dialog.text = LinkRandPhrase("Otro rostro pálido... Gran sacerdote feliz de arrancarte el corazón...","El rostro pálido sabe cómo llegar a Tayasal, ¡pero nadie sale de la ciudad!","Me sorprende, cara pálida: aún no has ido a la tierra de los espíritus... Camina mientras puedas, pronto verás a tus ancestros.");
			link.l1 = LinkRandPhrase("Bueno, bueno. Ya veremos...","No intentes asustarme, guerrero de piel roja. He visto cosas peores que eso.","Vete, vete. Intenta asustar a los niños.");
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz";
		break;
		
		case "itza_ctz_1":
			dialog.text = LinkRandPhrase("¡Bendíceme para la batalla contra el enemigo, gran Cavil!","Gran Cavil y gran Kukulcán nos honran con su presencia. ¡Ni siquiera en la antigua Maya esto sucedía!","¡Pasamos la leyenda de la gran batalla de Kukulcán y Cavil a nuestros hijos!");
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz_1";
		break;
		
		// Уракан - вождь ица
		case "urakan":
			dialog.text = "Eres un gran guerrero, cara pálida. Llevamos tu sangre a los dioses. Mueres con dignidad.";
			link.l1 = "Tranquilo, guerrero de piel roja. No voy a permitir que tu Kanek me lleve como sacrificio a Kukulcán ni a nadie más, en cuanto a eso. Tus guerreros no pudieron capturarme. Cada uno de ellos ha caído en batalla.";
			link.l1.go = "urakan_1";
		break;
		
		case "urakan_1":
			dialog.text = "Sí, tú, noble guerrero, rostro pálido. Pero no resistirás a cientos de guerreros Tayasal Itza. Sin embargo, dices una palabra interesante. ¿Cómo sabes sobre el gran Kanek y Kukulcán?";
			link.l1 = "Bueno, déjame adivinar... Ya que no eres Kanek, ¿tu nombre debe ser Urakan y eres el hijo del sacerdote Kanek?";
			link.l1.go = "urakan_2";
		break;
		
		case "urakan_2":
			dialog.text = "Sus labios hablan la verdad, rostro pálido. Soy Urakan, y estoy sorprendido.";
			link.l1 = "Te vas a sorprender aún más cuando veas esto... Mira.";
			link.l1.go = "urakan_3";
		break;
		
		case "urakan_3":
			dialog.text = "¡Oh, dioses! Si el rostro pálido tiene máscara, eso significa que ha llegado el momento... Eres aquel del que Kukulcán habló. Ordenó llevarte a él cuando llegues a Tayasal. Sabe que vienes.";
			link.l1 = "¿Kukulcán?! ¿Está aquí en Tayasal?";
			link.l1.go = "urakan_4";
		break;
		
		case "urakan_4":
			dialog.text = "Sí, guerrero blanco. Quetzalcóatl venir Tayasal. Pronto partirá para traer luz a los ancestros, gran ciudad de los Maya.";
			link.l1 = "¡Maldita sea! Entonces, él ya está aquí... (bajando la voz) Urakan, lo sé todo. Sé que tú eres quien envió a Ksatl Cha con el Guardián de la Verdad a buscar Ksocheatem y la máscara de Kukulcán...";
			link.l1.go = "urakan_5";
		break;
		
		case "urakan_5":
			dialog.text = "";
			link.l1 = "Veo sorpresa en tus ojos pero también duda, gran jefe Urakan. No estás contento con Kukulcán, ¿verdad?";
			link.l1.go = "urakan_6";
		break;
		
		case "urakan_6":
			dialog.text = "Cada guerrero Itza feliz gran Kukulcán venir, guerrero blanco. Debes presentarte ante Kukulcán. Él te espera muchas noches. Él es gran profeta. Sabe todo de antemano. Ve a la Serpiente Voladora, no tienes otro camino. No te permitimos dejar Tayasal.";
			link.l1 = "¿No entiendes que tan pronto como Kukulcán cruce las puertas del tiempo, todos ustedes, así como tú personalmente, dejarán de existir? Y lo mejor de todo es que renacerás en otra imagen, en otro cuerpo... Tal vez como un simple guerrero, o quizás incluso como un lisiado o mendigo...";
			link.l1.go = "urakan_7";
		break;
		
		case "urakan_7":
			dialog.text = "Ve, guerrero de piel pálida. Encontrarás a Kukulcán en el Gran Templo de los Guerreros de Itza. Sigue recto por el puente, hasta que veas la gran pirámide. Entra por la puerta inferior del templo y acércate al santuario.";
			link.l1 = "Está bien. Iré a Kukulkán, pues veo que no escaparemos de este encuentro. Pero te lo he advertido.";
			link.l1.go = "urakan_8";
		break;
		
		case "urakan_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_warrior_SetStay(npchar, true);
			LAi_warrior_DialogEnable(npchar, true);
			NextDiag.CurrentNode = "urakan_9";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			AddQuestRecord("Tieyasal", "25");
			pchar.quest.Tieyasal_Templegreat.win_condition.l1 = "location";
			pchar.quest.Tieyasal_Templegreat.win_condition.l1.location = "Temple_great";
			pchar.quest.Tieyasal_Templegreat.function = "Tieyasal_InGreatTemple";
			// экспа за бой
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "urakan_9":
			dialog.text = "Ve, guerrero blanco. Kukulcán te espera.";
			link.l1 = "Estoy en camino...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_9";
		break;
		
		case "urakan_10":
			PlaySound("Voice\Spanish\Complete.wav");
			dialog.text = "¡Finalmente, está hecho! ¡Se ha cumplido! Cuando veo cómo luchas contra Kukulcán, sé que eres Cavil en persona. Vienes a Tayasal para salvar al pueblo Itza de la muerte a causa de mi padre y de Kukulcán. Mi padre, el gran sacerdote Kanek, condenó al pueblo Itza en la gloria de los ancestros mayas hace mucho tiempo muertos.\nSoy el jefe de guerra Urakán, quien ha protegido al pueblo Itza durante muchos años. Ni un solo rostro pálido dejará Tayasal con vida. Yo y mis guerreros nos aseguramos de que el pueblo Itza permanezca protegido y vivo por muchos, muchos años por venir. No quiero sacrificar a todo mi pueblo.";
			link.l1 = "Lo sabía, Urakan. Y te pedí que me ayudaras en el puente.";
			link.l1.go = "urakan_11";
		break;
		
		case "urakan_11":
			dialog.text = "Nada se esconde de los ojos del gran Cavil. Perdona a Urakan por no entender quién eres realmente.";
			link.l1 = "No te preocupes por eso, jefe. He derrotado a la encarnación mortal de Kukulcán, pero tenemos una segunda tarea importante por delante: cerrar las puertas al pasado. Este agujero antinatural en el tiempo debe ser eliminado. ¿Me ayudarás?";
			link.l1.go = "urakan_12";
		break;
		
		case "urakan_12":
			dialog.text = "¿Con qué puede ayudarte Urakan, oh Cavil?";
			link.l1 = "Enviaste a Ksatl Cha con el Guardián de la Verdad a buscar a Ksocheatem y la máscara de Kukulcán. Así que sabes que puede usarse para cerrar las puertas del tiempo. ¿Te contó tu padre sobre eso?";
			link.l1.go = "urakan_13";
		break;
		
		case "urakan_13":
			dialog.text = "Padre no habla. Estudio escritos en el templo del Conocimiento y la Sabiduría. Pero mucho no está claro para Urakan. ¿Quizá Cavil pueda entender?";
			link.l1 = "¿Qué exactamente descubriste?";
			link.l1.go = "urakan_14";
		break;
		
		case "urakan_14":
			dialog.text = "Aprendo de memoria. Escribo proclamar: 'Cuando el sol se levante contra la lluvia, y el fuego entre ellos en triángulo, golpea la pierna de Tohil contra la pierna e incinera la máscara de Kukulcán en el altar del tiempo. Y sella las puertas de Itzamná del tiempo hasta el fin de los días.'";
			link.l1 = "Qué.";
			link.l1.go = "urakan_15";
		break;
		
		case "urakan_15":
			dialog.text = "Sí.";
			link.l1 = "Jesús... Muéstrame las puertas.";
			link.l1.go = "urakan_16";
		break;
		
		case "urakan_16":
			dialog.text = "Se encuentran en el templo Kukulcán. Pero la puerta allí está cerrada. Solo mi padre puede cerrar y abrir. Cuando él abre la puerta del templo Kukulcán, dice: 'El sol viene y va, el agua cae y se retira, el fuego se enciende y se apaga, la guerra y la paz se intercambian, pero solo el cielo es eterno. Por encima del tiempo solo está el cielo.'";
			link.l1 = "Interesante... Recordemos eso y veamos qué podemos hacer...";
			link.l1.go = "urakan_17";
		break;
		
		case "urakan_17":
			dialog.text = "Me quedo aquí, abajo, cerca del altar del tiempo. Veo cada pirámide y edificio en Taysal desde dentro. Encuentra las llaves. Me quedo aquí.";
			link.l1 = "Si tengo alguna pregunta de importancia, definitivamente acudiré a ti.";
			link.l1.go = "urakan_18";
		break;
		
		case "urakan_18":
			DialogExit();
			NextDiag.CurrentNode = "urakan_adv";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1 = "location";
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Tieyasal_UrakanTemple.function = "Tieyasal_UrakanInTemple";
			AddQuestRecord("Tieyasal", "26");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "quest", "urakan", "", -1);
			// экспа за бой
			AddComplexSelfExpToScill(1000, 1000, 1000, 1000);
			AddCharacterExpToSkill(pchar, "Leadership", 3000);
			AddCharacterExpToSkill(pchar, "Fortune", 1500);
		break;
		
		case "urakan_adv":
			dialog.text = "¿Puede Urakan ayudar al gran Cavil con consejo o acción?";
			if (Tieyasal_CheckTablets() && !CheckAttribute(npchar, "quest.tablets"))
			{
				link.l1 = "Échale un vistazo a esta tablilla que encontré. A juzgar por el lugar donde la hallé, debe tener algo que ver con tu padre y claramente no es un objeto común...";
				link.l1.go = "tablets";
			}
			if (CheckAttribute(npchar, "quest.treasureentrance"))
			{
				link.l1 = "He encontrado otra entrada en la cima del Gran Templo, pero está sellada. ¿Cómo puedo entrar allí? Quizás lo que busco esté allí dentro.";
				link.l1.go = "treasure";
			}
			link.l9 = "Nada por ahora, Urakan. Me las arreglaré solo...";
			link.l9.go = "exit";
			NextDiag.TempNode = "urakan_adv";
		break;
		
		case "tablets":
			dialog.text = "Placa de piedra de los dioses. Padre tiene varias piezas diferentes y son muy valiosas para él. Los antiguos constructores de Tayasal usaban la placa para activar mecanismos ocultos, abrir y cerrar puertas, incluso hacer rituales mágicos.\nFuncionan si se colocan en el lugar correcto, eso es lo que hace mi padre. Pero yo soy un guerrero como tú, no sé cómo usarlas correctamente. Quizás Cavil lo sepa.";
			link.l1 = "Definitivamente, llegaremos al fondo de esto...";
			link.l1.go = "exit";
			npchar.quest.tablets = "true";
			NextDiag.TempNode = "urakan_adv";
			AddQuestRecord("Tieyasal", "31");
		break;
		
		case "treasure":
			dialog.text = "Esta es la puerta a los tesoros de Tayasal. Allí yacen las riquezas de los indios Itza. La puerta por dentro solo mi padre puede abrir y cerrar. Nadie se atreve a entrar a los tesoros sin él. Ni siquiera yo.";
			link.l1 = "¿Cómo abrió tu padre la entrada?";
			link.l1.go = "treasure_1";
		break;
		
		case "treasure_1":
			dialog.text = "Mi padre dice: 'Cualquier riqueza tiene dos caras. Sólo aquel que conoce estas dos caras entra a los tesoros de Tayasal.' Qué significa esto, no lo sé. ¿Quizá, Cavil lo adivine?";
			link.l1 = "También resolveremos esto...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_adv";
			DeleteAttribute(npchar, "quest.treasureentrance");
			AddQuestRecord("Tieyasal", "32");
		break;
		
		case "urakan_19":
			PlaySound("Voice\Spanish\Complete.wav");
			dialog.text = "¡Finalmente, está hecho! Lo lograste, ¡oh gran Cavil! El pueblo de Itza ahora está a salvo. Yo, Urakan, hijo de Kanek, te aseguro que no deshonraré el honor que me das y protegeré Tayasal de cualquier invasión de rostros pálidos deshonrosos en tu nombre.";
			link.l1 = "Bien puedo creerlo, jefe. Bueno, ahora podemos celebrar: hemos detenido los traicioneros planes de Kukulcán. Nunca más podrá materializar una revolución temporal.";
			link.l1.go = "urakan_20";
		break;
		
		case "urakan_20":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "¡Gloria al gran Cavil! A mí y a mi generación nos toca el gran honor de ver en Tayasal a dos dioses. Escribimos esta historia para nuestros hijos. ¡Ellos sabrán sobre la batalla de los dioses en Tayasal! ¡Gloria a Cavil! ¡Gloria!";
			link.l1 = "Necesito una bebida...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_Win_IndianBead");
		break;
		
		// Канек - жрец ица
		case "kanek":
			dialog.text = "Te encuentras ante la Serpiente Emplumada, rostro pálido. El espíritu del poderoso Kukulcán en carne humana. Eres afortunado de ser su hermano a través del padre de su encarnación, así como yo soy afortunado de ser el padre de su madre, la mujer que lo dio a luz. Es un gran honor. Quizás por eso te has convertido en un guerrero fuerte y aún estás vivo. Pero tu tiempo se acabará, rostro pálido. Comenzaremos un nuevo tiempo, el tiempo de los grandes Maya. Estableceremos nuestro propio poder y nunca dejaremos que los rostros pálidos entren en nuestro mundo. Pronto. Yo, Kanek el sacerdote, iré a iniciar el ritual.";
			link.l1 = "Maravilloso...";
			link.l1.go = "kanek_1";
		break;
		
		case "kanek_1":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kanek_2":
			dialog.text = "Urakan, has oído lo que dijo nuestro señor. ¡Sométete ahora!";
			link.l1 = "Cuando los grandes se baten entre sí, mejor es para nosotros, simples mortales, mantenernos al margen y observar desde la distancia, padre...";
			link.l1.go = "kanek_3";
		break;
		
		case "kanek_3":
			dialog.text = "¿Qué?! ¡Recapacita, hijo!";
			link.l1 = "Este hombre es el hermano de Kukulcán y un gran guerrero. ¡Veo la encarnación del mismo Cavil en él! Nadie, aparte de él, soporta a un dios así. ¡No es un juego de niños en el duelo de dioses, padre! Y si traes ofrendas a Kukulcán, ¡mis guerreros darán su sangre a Cavil!";
			link.l1.go = "kanek_4";
		break;
		
		case "kanek_4":
			dialog.text = "¿Estás en tu sano juicio, Urakan?";
			link.l1 = "Muchos años llevo, nombrado en honor a Hurakan, protegiendo con éxito nuestras tierras en nombre de Cavil de la invasión de forasteros. Cientos de ellos han caído bajo nuestros garrotes y nadie ha dejado Tayasal. Pero nunca en mi vida he visto a un guerrero tan fuerte y rápido como este rostro pálido. ¡Si es capaz de derrotar a Kukulcán, entonces es la encarnación del espíritu del mismo Cavil!";
			link.l1.go = "kanek_5";
		break;
		
		case "kanek_5":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
