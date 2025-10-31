void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		case "Alonso":
			NextDiag.TempNode = "Alonso";
			
			if (GetDLCenabled(DLC_APPID_1))
			{
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FirstStage", "ready"))
				{
					dialog.text = "¿Permiso para hablar, capitán?";
					link.l1 = "Más tarde, Alonso.Adelante.";
					link.l1.go = "exit";
					link.l2 = "Adelante.";
					link.l2.go = "Alonso_1";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.SecondStage", "ready"))
				{
					dialog.text = "¿Permiso para hablar, capitán?";
					link.l1 = "Más tarde, Alonso.Adelante.";
					link.l1.go = "exit";
					link.l2 = "Adelante.";
					link.l2.go = "Alonso_Lvl_8_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.ThirdStage", "ready"))
				{
					dialog.text = "¿Permiso para hablar, capitán?";
					link.l1 = "Más tarde, Alonso.Adelante.";
					link.l1.go = "exit";
					link.l2 = "Adelante.";
					link.l2.go = "Alonso_Lvl_12_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FourthStage", "ready"))
				{
					dialog.text = "¿Permiso para hablar, capitán?";
					link.l1 = "Más tarde, Alonso.Adelante.";
					link.l1.go = "exit";
					link.l2 = "Adelante.";
					link.l2.go = "Alonso_Lvl_16_Start";
					break;
				}
			}
			
			dialog.text = "Nada que informar, capitán.";
			link.l1 = "Sigue así, Alonso.";
			link.l1.go = "exit";
		break;
		
		case "Alonso_1":
			DelLandQuestMark(npchar);
			dialog.text = "¿Cómo lo lleva, capitán?";
			link.l1 = "¿A qué te refieres?";
			link.l1.go = "Alonso_2";
		break;
		
		// Основная развилка стадии 1
        case "Alonso_2":
            dialog.text = "Ya lleváis meses surcando estas aguas del Caribe, mientras que algunos no duran ni una semana aquí. La tripulación os respeta, eso es seguro, pero yo... yo me preocupo por vuestro futuro.\n"+
                          "Compartid vuestros planes, haced ese favor a la tripulación. ¿Hacia dónde navega el "+pchar.ship.name+"?";
                          
            link.l1 = "No tengo un plan. Primero quiero conocer estas aguas. La aventura nos encontrará por sí sola.";
            link.l1.go = "Alonso_Choice_1";
            
            link.l2 = "Estas aguas están llenas de depredadores, Alonso. Y el "+pchar.ship.name+" es el más pequeño de ellos. Por ahora.";
            link.l2.go = "Alonso_Choice_2";
            
            link.l3 = "Me gusta ganar dinero. Preferiblemente de forma legal. Pero ya veremos cómo sale.";
            link.l3.go = "Alonso_Choice_3";
			
            if (!SandBoxMode)
            {
                link.l4 = "Ya lo sabes. Después de aquella memorable conversación en el Ulises, todo se complicó aún más…";
                link.l4.go = "Alonso_Choice_4";
            }
        break;
        
        case "Alonso_Choice_1":
            dialog.text = "¡Eso es libertad! Lo importante es tener para mantener el barco y guardar algo en los cofres para los malos tiempos.\n"+
                          "Donde os lleve el humor, la misión o el mapa del tesoro - coged pasajeros, fletes, cualquier trabajillo que se cruce en vuestro camino.\n"+
                          "No vendría mal algo de comercio menor - comprad barato donde sea obvio, vended donde podáis.\n"+
                          "Y si veis un mercante solitario por el camino... Je. Tenéis razón, capitán. La aventura nos encontrará sin duda.";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50);
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            
            link.l1 = "Gracias por el buen consejo, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_2":
            dialog.text = "Negocio rentable, si el barco lo permite. Buscad mercantes solitarios y enseñadles lo que significa 'lo barato sale caro'.\n"+
                          "Por desgracia para vos, entra en juego otro refrán: 'No hay secreto que cien años dure'. Siempre habrá una lengua suelta en la tripulación que contará vuestras hazañas en el primer puerto.\n"+
                          "Así que robad a todas las banderas un poco, o elegid vuestro enemigo de por vida.\n"+
                          "Aunque quizás me estoy adelantando. Si las cosas se ponen feas, hay un abogado en Port Royal que arregla cualquier problema con las autoridades por buenos pesos. Llamémoslo impuesto pirata, ¡je, je!";
            
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", -1);
            
            link.l1 = "Gracias por el buen consejo, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_3":
            dialog.text = "Eh, ahí no puedo ayudaros mucho, capitán. Necesitáis un barco mercante de verdad: un bergantín goleta, o mejor aún, una barca. Probablemente me arrepienta de esto, pero mejor llevar cañones ligeros o tirarlos directamente.\n"+
                          "Tomad contratos de carga de los dueños de tiendas, comerciad por vuestra cuenta en el camino y transportad pasajeros.\n"+
                          "Cuando hayáis ahorrado suficiente, invertid en tiendas y bancos. Ya veréis, capitán - llegará el día en que vuestro dinero hará dinero, y podréis permitiros un gran barco con doscientos hombres a bordo.\n"+
                          "Por el cual, por cierto, no pagaréis vos, sino vuestro negocio.";
            
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            AddCharacterExpToSkill(pchar, SKILL_SAILING, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "Gracias por el buen consejo, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_4":
            dialog.text = "Yo lo veo de otra manera, capitán. En el Ulises erais solo un pasajero - esas pobres almas no tienen control sobre su destino. Ahora sois un capitán que se ha ganado su sombrero, lo que significa que podéis resolver cualquier problema. Ya os lo dije antes - no hay posición más alta en nuestro mundo.\n"+
                          "Me huelo que esta epopeya con vuestro hermano durará años, así que cuidaos primero vos. Monsieur Michel no se va a ir a ninguna parte, je, je…\n"+
                          "No sois el único con problemas en el Caribe. Es el momento perfecto para ayudar a otros mientras ganáis dinero, equipo y contactos. Aprenderéis todo lo que necesitaréis para este asunto familiar por el camino…";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 100);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "Gracias por el buen consejo, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
		
        case "Alonso_Common_End":
            dialog.text = "No os limitéis a un solo papel, capitán. Haced solo lo que queráis. Tomadlo todo y no devolváis nada. Todo os saldrá bien.";
            link.l1 = "Y gracias también por las palabras de aliento.";
            link.l1.go = "Alonso_Common_End_2";
        break;
        
        case "Alonso_Common_End_2":
            dialog.text = "Eh, para eso me pagáis, capitán. ¿Creéis que a la tripulación le basta con su miserable paga para cumplir vuestras órdenes?\n"+
                          "Docenas de hombres encerrados en un espacio reducido, sin saber cuándo verán tierra, o si la verán. ¿Y hundir un barco? Pan comido.";
            link.l1 = "Sí, sí, ya conozco ese discurso, Alonso. ¿Qué decías antes sobre los barcos?";
            link.l1.go = "Alonso_Common_End_3";
        break;
        
        case "Alonso_Common_End_3":
            dialog.text = "¡Je! Un barco es una prisión, un campamento militar y un monasterio todo en uno. Una reunión de hombres, en resumen. Así que los problemas se resuelven con palabras o con el látigo. En vuestro caso lo segundo, je, je, no es opción, así que pensé en charlar con vos. Para haceros las cosas más fáciles, digamos.";
            link.l1 = "¿Has estado alguna vez en prisión? ¿En el ejército? ¿En un monasterio, Dios no lo quiera? Y en general, Alonso, cuéntame de ti. Apenas sé nada sobre ti.";
            link.l1.go = "Alonso_Story_1";
        break;
        
        // История Алонсо
        case "Alonso_Story_1":
            dialog.text = "Pues en monasterios no he estado, no voy a mentir. Aunque sí serví en la Santa Inquisición una vez…";
            link.l1 = "¿Cómo diablos ocurrió eso?";
            link.l1.go = "Alonso_Story_2";
        break;
        
        case "Alonso_Story_2":
            dialog.text = "¡Oh! Fue así. Estuve tirando del carro como mercenario en la guerra europea. El diablo sabrá cómo empezó o quién luchaba contra quién. Solo sabíamos que la guerra llevaba treinta años y qué comandante pagaba más o menos regularmente. ¡Eso sí fue una aventura!\n"+
                          "Esto fue en el '42... ¿o fue en el '41? No importa. Dos compañías, ambas al servicio del Emperador, se encontraron en un bosque. En la niebla. ¡Y empezaron a hacerse pedazos! ¡Tres días de matanza!";
            link.l1 = "¿Cómo es posible?";
            link.l1.go = "Alonso_Story_3";
        break;
        
        case "Alonso_Story_3":
            dialog.text = "Intenta distinguir amigo de enemigo en esa niebla. Además, no nos habían pagado en tres meses, así que todos pensaban en el botín.\n"+
                          "Nos matamos la mitad unos a otros. Cuando nos dimos cuenta, ya era tarde. Ahí conocí a un moscovita. ¡Grande como un oso, pero con corazón de oro!";
            link.l1 = "¿Y qué pasó después?";
            link.l1.go = "Alonso_Story_4";
        break;
        
        case "Alonso_Story_4":
            dialog.text = "¿Sabéis cómo es en la guerra? El primero en informar es el héroe. Así que pensamos - ¡saquemos provecho de este desastre!\n"+
                          "Nos pusimos de acuerdo con los muchachos, fuimos al pagador, informamos de una 'gran batalla'. A los muertos les cortaron la paga, a los supervivientes les pagaron, mi amigo y yo recibimos bonificaciones, y el comandante su parte.";
            link.l1 = "Entonces eres rico, Alonso.";
            link.l1.go = "Alonso_Story_5";
        break;
        
        case "Alonso_Story_5":
            dialog.text = "¡Ja! Luego pasamos una semana bebiendo vino y jugando a las cartas. Por suerte, mi nuevo amigo del lejano reino de Moscú tenía debilidad por las piezas raras, o habría acabado en prisión por deudas. Me compró un trofeo: una magnífica pistola de tres cañones, y a buen precio. No se aprovechó de mi desgracia.";
            link.l1 = "Una historia fantástica, Alonso. Me parece que te la acabas de inventar.";
            link.l1.go = "Alonso_Gift";
        break;
        
        // Вручение подарка
        case "Alonso_Gift":
            dialog.text = "Me ofendéis, capitán. Tomad, un regalito.";
            link.l1 = "¿Qué es?";
            link.l1.go = "Alonso_Gift_2";
        break;
        
        case "Alonso_Gift_2":
            // Выдаем Берендейку
            GiveItem2Character(pchar, "talisman20");
			SetAlchemyRecipeKnown("talisman20");
            
            dialog.text = "Una bandolera para combate con mosquete. En la patria de mi amigo moscovita todos las llevan. O eso decía él.\n"+
                          "Que os sirva bien, capitán. Consideradlo un regalo de la tripulación.";
            link.l1 = "¡Inesperado! Gracias, Alonso. ¿Y qué hay de tu servicio en la Inquisición?";
            link.l1.go = "Alonso_Escape";
        break;
        
        case "Alonso_Escape":
            PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Eh…\n"+
                          "¡Suenan las campanas, capitán! Hora de volver al trabajo. Continuaremos en otra ocasión.";
            link.l1 = "Definitivamente continuaremos esta conversación. ¡Gracias por el regalo!";
            link.l1.go = "exit";
            
			AddDialogExitQuestFunction("LoyaltyPack_FirstStage_DlgExit");
        break;
		
		// (Уровень 8) - Продолжаем историю
        case "Alonso_Lvl_8_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Habéis logrado mucho desde nuestra última charla, y nadie - ni la tripulación, ni yo - duda ya de vuestros talentos.";
			link.l1 = "¿Había dudas?";
			link.l1.go = "Alonso_Lvl_8_1";
        break;

        case "Alonso_Lvl_8_1":
            dialog.text = "Claro que las había. Somos gente sencilla - acostumbrados a prepararnos para lo peor. Disfrutad de vuestra libertad, capitán. Seguid así y veréis un lado completamente diferente del Caribe.";
            link.l1 = "Me alegra oírlo. Ahora cuéntame sobre tu servicio en la Inquisición. La última vez empezaste con una historia del ejército y también terminaste con ella.";
            link.l1.go = "Alonso_Lvl_8_2";
        break;

        case "Alonso_Lvl_8_2":
            dialog.text = "¿Qué hay que contar? Después de aquella matanza sin sentido pero muy rentable en el bosque, el moscovita y yo nos hicimos muy amigos y montamos unos cuantos negocios más.\n"+
                          "Recuerdo que una vez decidimos asaltar un convoy imperial. Los exploradores dijeron que llevaban trofeos, oro, armas...";
            link.l1 = "¿Y qué, lo conseguisteis?";
            link.l1.go = "Alonso_Lvl_8_3";
        break;

        case "Alonso_Lvl_8_3":
            dialog.text = "Pan comido. Atacamos por dos lados, dispersamos a los guardias, abrimos los carros - ¡y encontramos repollo! ¡Repollo podrido y apestoso para alguna guarnición! ¿Pero sabéis qué? No habíamos comido en una semana, ¡así que hasta eso nos alegró!";
            link.l1 = "Como si en mi barco se comiera mejor.";
            link.l1.go = "Alonso_Lvl_8_4";
        break;

        case "Alonso_Lvl_8_4":
            dialog.text = "Bueno, ahora ya estoy acostumbrado. Pero entonces… Después de una semana de forrajeo, ¡roerías hasta la corteza de los árboles!\n"+
                          "Pero mi amigo no se desanimó. Sacó una petaca con su brebaje especial - receta moscovita, dijo. ¡A nosotros qué nos importaba, con tal de que no fuera vinagre! ¡Después de unos tragos, hasta el repollo parecía un manjar!";
            link.l1 = "Repugnante.";
            link.l1.go = "Alonso_Lvl_8_5";
        break;

        case "Alonso_Lvl_8_5":
            dialog.text = "Repugnante es el estado de nuestros barriles de agua, pero aquel brebaje moscovita me salvó la vida ese día.";
            link.l1 = "¿Cómo es eso?";
            link.l1.go = "Alonso_Lvl_8_6";
        break;

        case "Alonso_Lvl_8_6":
            dialog.text = "Nos emborrachamos hasta las cejas allí mismo, entre el barro del camino con repollos flotando. Bueno, una cosa llevó a la otra, y discutí con un noblete. Un alemán, todo pulcro y emperifollado. Demasiado bueno para beber con nosotros, solo limpiaba su mosquete y soltaba comentarios mordaces.\n"+
                          "Así que estamos allí sentados, descansando, ahogando las penas con el repollo. Y él empieza a sermonearnos sobre sabiduría militar. Que nuestras fieles espadas y picas pronto serán olvidadas, pero la bayoneta - eso sí es el futuro y la clave de todo.\n"+
                          "Así que discutí con él, y de alguna manera acordamos luchar a muerte - con bayonetas, nada menos. No me preguntéis cómo pasó, yo mismo no lo recuerdo.\n"+
                          "Pero en toda nuestra compañía solo había dos bayonetas. Una del oficialerito ese, la otra de Fox, un inglés. Le pedí prestado su fusil y apalee al alemán hasta matarlo, y me largué.";
            link.l1 = "Pero estabas hambriento y borracho.";
            link.l1.go = "Alonso_Lvl_8_7";
        break;

        case "Alonso_Lvl_8_7":
            dialog.text = "Luego me di cuenta de que el brebaje de mi amigo realmente estabiliza la mano cuando balanceas un mosquete pesado. Así que ahora estoy más inclinado a estar de acuerdo con las ideas del alemán muerto.";
            link.l1 = "¿Y qué tiene esto que ver con tu servicio en la Inquisición?";
            link.l1.go = "Alonso_Lvl_8_Gift";
        break;

        case "Alonso_Lvl_8_Gift":
            dialog.text = "¡Otra vez no me creéis, capitán! Tomad esto.";
            link.l1 = "¿Una botella y un papel?";
            link.l1.go = "Alonso_Lvl_8_Gift_2";
        break;

        case "Alonso_Lvl_8_Gift_2":
            // Даём игроку настойку и рецепт
            GiveItem2Character(pchar, "vodka");
            SetAlchemyRecipeKnown("vodka");

            dialog.text = "Es el brebaje del que os hablaba. Y la receta. Por si os gusta, je, je.";
            link.l1 = "Lo siento, amigo mío, pero garabatos y algún brebaje turbio no…";
            link.l1.go = "Alonso_Lvl_8_Gift_3";
        break;

        case "Alonso_Lvl_8_Gift_3":
            // Даём игроку мушкет с багинетом
            GiveItem2Character(pchar, "mushket10");

            dialog.text = "Vale, vale, capitán. De todos modos iba a regalároslo. A mí no me va este tipo de arma, pero a vos os será útil. Las bayonetas son bestias raras. Pero cuando aprendáis a usarla, os olvidaréis de blandir sables.";
            link.l1 = "Espera, ¿es este el mosquete del oficial imperial? ¿El que mataste?";
            link.l1.go = "Alonso_Lvl_8_Gift_4";
        break;

        case "Alonso_Lvl_8_Gift_4":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "El mismo. Como veis, os dije la verdad, capitán.";
            link.l1 = "Pero no era eso lo que preguntaba.";
            link.l1.go = "Alonso_Lvl_8_Escape";
        break;

        case "Alonso_Lvl_8_Escape":
            dialog.text = "¡Suenan las campanas, capitán! Hora de volver al trabajo. Continuaremos en otra ocasión.";
            link.l1 = "Definitivamente continuaremos esta conversación. ¡Gracias por el mosquete!";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_SecondStage_DlgExit");
        break;

        // (Уровень 12)
        case "Alonso_Lvl_12_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Capitán, sobre los nuevos reclutas...";
			link.l1 = "¿Ha pasado algo?";
			link.l1.go = "Alonso_Lvl_12_1";
        break;

        case "Alonso_Lvl_12_1":
            dialog.text = "Quería informaros que en la cena uno de los reclutas mencionó que quería enrolarse específicamente en vuestro barco.";
            link.l1 = "¿Y qué significa eso exactamente?";
            link.l1.go = "Alonso_Lvl_12_2";
        break;

        case "Alonso_Lvl_12_2":
            dialog.text = "Que pronto podría haber más como él. Ya tenéis un nombre, capitán.";
            link.l1 = "Curioso que todavía no sé qué hay detrás de tu nombre. Nunca terminaste esa historia sobre la Inquisición.";
            link.l1.go = "Alonso_Lvl_12_3";
        break;

        case "Alonso_Lvl_12_3":
            dialog.text = "Oh, por dónde iba... ¡Ah sí! Decidimos hacernos proveedores militares. La guerra estaba terminando, había que pensar en el futuro. Y mi amigo siempre tenía la cabeza llena de planes para el futuro.";
            link.l1 = "Eso es un gran salto profesional. Hace poco os emborrachabais junto a un carro saqueado lleno de repollos.";
            link.l1.go = "Alonso_Lvl_12_4";
        break;

        case "Alonso_Lvl_12_4":
            dialog.text = "¿Y qué? Recibimos un pedido de cien yelmos para algún regimiento. Nos dieron un buen anticipo. Nos alegramos, fuimos a celebrar... Jugamos a las cartas.\n"+
                          "Por la mañana despertamos --- el anticipo no está, el ejército marcha en dos días, ¡y no tenemos ni un solo yelmo!";
            link.l1 = "¿Y qué hicisteis?";
            link.l1.go = "Alonso_Lvl_12_5";
        break;

        case "Alonso_Lvl_12_5":
            dialog.text = "Fuimos al campo de batalla reciente, recogimos sombreros de los muertos. Luego clavamos trozos de metal, pusimos placas... ¡Se veía ridículo, pero funcionaba! Definitivamente podía salvar de un sablazo. Bueno, al menos una vez seguro. ¡Tan bueno como cualquier yelmo, ¿no?!";
            link.l1 = "¿El intendente apreció vuestra ingeniosidad?";
            link.l1.go = "Alonso_Lvl_12_6";
        break;

        case "Alonso_Lvl_12_6":
            dialog.text = "Nos envió al tribunal por malversación y fraude. ¿Pero sabéis qué? Los soldados dijeron después que esos sombreros les salvaron la vida más de una vez. Y a nosotros también, resultó.";
            link.l1 = "¿Cómo es eso?";
            link.l1.go = "Alonso_Lvl_12_7";
        break;

        case "Alonso_Lvl_12_7":
            dialog.text = "Pues ambos acabamos en prisión. Y nuestra compañía fue enviada a una misión. No sé dónde ni contra quién, y probablemente ellos tampoco lo sabían. Nunca regresaron.\n"+
                          "...\n"+
                          "Perdonad, capitán. Continuaremos en otra ocasión. Tomad este sombrero y las instrucciones. Lo hice ayer para alegraros... Pero solo me entristecí yo sin motivo.";
            link.l1 = "Por supuesto, Alonso. Gracias por el regalo.";
            link.l1.go = "Alonso_Lvl_12_Gift";
        break;

        case "Alonso_Lvl_12_Gift":
            // Даём игроку шляпу
            GiveItem2Character(pchar, "hat10");
            SetAlchemyRecipeKnown("Hat10");

            DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_ThirdStage_DlgExit");
        break;

        // (Уровень 16) - Финальный
        case "Alonso_Lvl_16_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Capitán, solo quería informaros que a vuestra tripulación la reciben con honores en tabernas y burdeles. ¡Servir bajo vuestra bandera significa algo hoy en día!";
			link.l1 = "Gracias, Alonso... Lástima que yo todavía no veo mucho de ese trato de honor hacia mí.";
			link.l1.go = "Alonso_Lvl_16_1";
        break;

        case "Alonso_Lvl_16_1":
            dialog.text = "Ya lo veréis pronto. El Caribe es un pastel que se reparten unas pocas docenas de capitanes. Pronto tendréis asiento en esa mesa y cogeréis vuestra porción.\n"+
                          "¿Y quién sabe? Quizás seáis vos la leyenda del Caribe que se lleve todo el pastel.";
            link.l1 = "¿Entonces terminarás tu historia? Nos quedamos donde acabaste en prisión.";
            link.l1.go = "Alonso_Lvl_16_2";
        break;

        case "Alonso_Lvl_16_2":
            dialog.text = "¡Ja! El caso de los grandes ladrones de sombreros. Un moscovita y un portugués en una celda diminuta en algún lugar de Flandes. Esperando sentencia. De muerte, naturalmente.\n"+
                          "Nos salvó un señor importante - ¡resultó ser el embajador moscovita! Viejo amigo de Fadey. Estaba de paso, se enteró de nuestro apuro, ¡compró nuestra libertad!";
            link.l1 = "¿Fadey? ¿EL Fadey? ¡¿Y te lo callaste?!";
            link.l1.go = "Alonso_Lvl_16_3";
        break;

        case "Alonso_Lvl_16_3":
            dialog.text = "Ajá. Ahí nos separamos: él volvió a su Moscú, ya sea para luchar contra los polacos o para manejar grandes negocios. Yo anduve un poco más por la vieja patria, y aquí estoy.";
            link.l1 = "Impresionante, Alonso. Todo este tiempo y has conseguido contarme de todo menos de ti mismo. Extraño cómo alguien tan listo como tú dejó escapar lo de la Inquisición.";
            link.l1.go = "Alonso_Lvl_16_4";
        break;

        case "Alonso_Lvl_16_4":
            dialog.text = "¡Y os conté la pura verdad, capitán! No me creéis - preguntadle al mismo Fadey. No es difícil encontrarlo en Basse-Terre.";
            link.l1 = "Quizás lo haga. ¿Y mi regalo?";
            link.l1.go = "Alonso_Lvl_16_5";
        break;

        case "Alonso_Lvl_16_5":
            dialog.text = "¿Eh?";
            link.l1 = "Me dabas un regalo al final de cada historia.";
            link.l1.go = "Alonso_Lvl_16_Escape";
        break;

        case "Alonso_Lvl_16_Escape":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "¿Oís eso? Suenan las campanas. Hora de trabajar.";
            link.l1 = "Sigue así, Alonso.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_FourthStage_DlgExit");
        break;
	}
} 