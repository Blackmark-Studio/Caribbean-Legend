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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "¿Qué desea?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		case "Kristian":
			dialog.text = "¡Bienvenido a mi casa! Me llamo Christian. Christian Deluce. ¿En qué puedo ayudarle?";
			link.l1 = "Soy el capitán "+GetFullName(pchar)+". Necesito adquirir un lote de licor. ¿Sabe a qué me refiero?";
			link.l1.go = "Kristian_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Kristian_2":
			dialog.text = "¿Qué??? ¿Quién le dijo eso? ¡Debe haber un error! Le aseguro que no vendo ningún tipo de licor.";
			link.l1 = "Vaya, parece que estoy en el lugar correcto.";
			link.l1.go = "Kristian_3";
		break;
		
		case "Kristian_3":
			dialog.text = "¡Oh, no, no! ¡Claro que no! ¡No vendo licor! Yo... simplemente, eh... bueno... Sí, tengo mercancía, pero todo es legal. Solo compro para particulares, eh... para fiestas, pequeñas reuniones.";
			link.l1 = "¿Por qué se pone tan nervioso? No he venido a arrestarle, sino a ayudarle a prosperar. Y espero que mis bolsillos también se llenen con algunas monedas de oro.";
			link.l1.go = "Kristian_4";
		break;
		
		case "Kristian_4":
			dialog.text = "¡Yo... yo no estoy nervioso! ¿Por qué habría de estarlo? Soy un ciudadano honesto, mi casa está justo al lado de la residencia del gobernador. ¡No estoy infringiendo ninguna ley, se lo aseguro!";
			link.l1 = "¿Así que no comercia con licor? Qué lástima. Verá, tengo una oferta muy lucrativa. Estoy seguro de que un comerciante clandestino como usted nunca ha soñado con tantos doblones. Bueno, si no es usted a quien busco, me marcharé. ¿De acuerdo?";
			link.l1.go = "Kristian_5";
		break;
		
		case "Kristian_5":
			dialog.text = "Eh... espere... "+GetAddress_Form(NPChar)+"... disculpe, me puse tan nervioso que olvidé su nombre.";
			link.l1 = "Capitán "+GetFullName(pchar)+".";
			link.l1.go = "Kristian_6";
		break;
		
		case "Kristian_6":
			dialog.text = ""+GetSexPhrase("Señor","Señorita")+" "+pchar.lastname+", el asunto es que... eh... bueno... sé dónde encontrar a la persona que necesita. Puedo transmitirle... su propuesta.";
			link.l1 = "¿Transmitir? ¿Realmente cree que en este tipo de asuntos es prudente usar intermediarios?";
			link.l1.go = "Kristian_7";
		break;
		
		case "Kristian_7":
			dialog.text = "Tiene razón. Pero... bah... que sea lo que Dios quiera... sí, soy la persona que está buscando.";
			link.l1 = "Así está mejor, Christian. Verá, la taberna enfrenta serios problemas con el suministro de licor, y espero que podamos sacar provecho de esta situación.";
			link.l1.go = "Kristian_8";
		break;
		
		case "Kristian_8":
			dialog.text = "Capitán, estoy al tanto de las dificultades del tabernero, porque la gente comenzó a acudir a mí, y ya me da miedo seguir vendiendo, llama demasiado la atención. Así que pensé que usted... bueno, ya me entiende...";
			link.l1 = "¿Y por qué no le ofreció sus servicios directamente?";
			link.l1.go = "Kristian_9";
		break;
		
		case "Kristian_9":
			dialog.text = "Él... él jamás aceptaría colaborar conmigo. Ese hombre no soporta a comerciantes menores como yo.";
			link.l1 = "Sí, ya lo había oído. Tal vez con usted no quiera tratar. Pero conmigo, sí lo hará.";
			link.l1.go = "Kristian_10";
		break;
		
		case "Kristian_10":
			dialog.text = "¿Quiere actuar como intermediario? Bueno, no me opongo... hace poco trajimos un cargamento —¡todo un récord! Debería haber durado al menos medio año. Pero, ¡Dios es testigo!, sólo un milagro nos salvó de ser descubiertos.\nTodavía no entiendo cómo logramos escapar. Intentar algo así de nuevo sería un suicidio.";
			link.l1 = "Entonces debería dejar la clandestinidad. Al menos en parte.";
			link.l1.go = "Kristian_11";
		break;
		
		case "Kristian_11":
			dialog.text = "¿Salir de la clandestinidad? Pero... eso requiere contactos... ¡y dinero! ¿Y para qué? ¿Acaso usted, capitán de un barco, se establecerá en la ciudad y se encargará de suministros para la taberna local?";
			link.l1 = "En cuanto a contactos, creo que puedo ayudarle. En cuanto al dinero... no creo que sea tanto. Y sobre lo último, no hará falta. Usted actuará en mi nombre. Yo le ayudaré, y usted me ayudará a mí. De manera regular. Usted gana un canal estable de ventas, y yo un proveedor confiable. ¿Qué me dice?";
			link.l1.go = "Kristian_12";
		break;
		
		case "Kristian_12":
			dialog.text = "Pensé que esto era una trampa. Pero, para ser sincero, su propuesta suena... muy tentadora. Estabilidad, fiabilidad... Quién lo diría, ¡una oportunidad así para mí! "+GetSexPhrase("Señor","Señorita")+", acepto. ¿Cuánto desea comprar?";
			link.l1 = "Primero legalicemos su negocio, luego discutiremos los detalles. ¿Cuánto ron y vino tiene disponible ahora mismo?";
			link.l1.go = "Kristian_13";
		break;
		
		case "Kristian_13":
			dialog.text = "¿Ahora mismo? Eh... Vamos a la bodega, allí podré decirle la cantidad exacta.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_GoToPogreb");	// спускаемся в погреб
		break;
		
		// погреб
		case "Kristian_15":
			dialog.text = "Veamos... ¿Qué tenemos aquí? Ajá\nActualmente tengo exactamente cien botellas de ron y cien de vino en stock.";
			link.l1 = "Bien, creo que esto será suficiente para comenzar. Si logramos resolver el problema con la importación, ¿podría suministrar estas cantidades mensualmente sin fallos?";
			link.l1.go = "Kristian_16";
		break;
		
		case "Kristian_16":
			dialog.text = "¡Por supuesto, capitán! Incluso el triple, no, ¡el cuádruple si hace falta! No habrá fallos, siempre mantendré suficiente en el almacén por si acaso surge algún contratiempo.";
			link.l1 = "¿Cuánto quiere recibir por este lote?";
			link.l1.go = "Kristian_17";
		break;
		
		case "Kristian_17":
			dialog.text = "Estoy dispuesto a aceptar: diez doblones por cada diez botellas de vino y tres doblones por cada diez botellas de ron. En total, serían ciento treinta doblones por todo el lote.";
			link.l1 = "De acuerdo. Hablaré con el tabernero y regresaré pronto.";
			link.l1.go = "Kristian_18";
		break;
		
		case "Kristian_18":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_18_1";
			pchar.questTemp.TPZ_Tavern_2 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			AddQuestRecord("TPZ", "4");
		break;
		
		case "Kristian_18_1":
			dialog.text = "Capitán, ¿hay novedades? ¿Qué dijo el tabernero?";
			link.l1 = "Justamente voy camino hacia él.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_18_1";
		break;
		
		case "Kristian_21":
			dialog.text = "¿Cómo fue todo, capitán? ¿Logró llegar a un acuerdo con el tabernero?";
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				link.l1 = "Hice un buen trabajo, Christian. Comprará este lote y todos los siguientes por doscientos cuarenta doblones. Por este primero le pagaré los ciento treinta que pidió. El resto me lo quedo como recompensa por mis gestiones. Las ganancias futuras serán totalmente suyas.";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				link.l1 = "Trabajé bien, Christian. Acordé que comprará este lote y los siguientes por doscientos doblones. Por el primero le pagaré los ciento treinta que pidió. El resto me lo quedo como recompensa. El beneficio futuro será suyo.";
			}
			link.l1.go = "Kristian_22";
			DelLandQuestMark(npchar);
		break;
		
		case "Kristian_22":
			dialog.text = "¡Qué noticia, capitán! ¡Jamás habría soñado con un trato así, gracias! Pero... ¿no se habrá apresurado? ¿El gobernador... yo... es decir...";
			link.l1 = "Con el gobernador todo está arreglado. A partir de ahora, cada mes pagará un impuesto de cien doblones y entregará informes sobre su comercio.";
			link.l1.go = "Kristian_23";
		break;
		
		case "Kristian_23":
			dialog.text = "¡Increíble! ¿Cómo lo logró, capitán? El gobernador es un hombre estricto, y además un ferviente enemigo del comercio clandestino...";
			link.l1 = "Precisamente, Christian, él es enemigo del contrabando, no del comercio honesto. Me escuchó con atención y me comunicó las condiciones para comerciar licor en la isla. Usted trabajará en mi nombre, y por todos sus errores responderé yo también. Así que no me falle, o lo encontraré incluso en el más allá.";
			link.l1.go = "Kristian_24";
		break;
		
		case "Kristian_24":
			dialog.text = "¡Lo juro, capitán, no se arrepentirá!";
			link.l1 = "Ahora debemos cerrar el trato con el tabernero, y después discutiremos los detalles de nuestra cooperación.";
			link.l1.go = "Kristian_25";
		break;
		
		case "Kristian_25":
			dialog.text = "Por supuesto, capitán. ¿Está listo para llevarse el lote ahora mismo? Le costará ciento treinta doblones.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Sí, aquí están sus doblones.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "En este momento no tengo la suma necesaria. Espéreme aquí, buscaré el dinero y volveré.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;
		
		case "Kristian_25_1":
			dialog.text = "¡Capitán! ¿Volvió para recoger la mercancía? Serán ciento treinta doblones.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Exactamente. Aquí están sus doblones.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Lamentablemente, aún no tengo el dinero. Volveré más tarde.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;
		
		case "Kristian_26":
			dialog.text = "¡Gracias! ¡Lléveselo! Cien botellas de vino y cien de ron, tal como acordamos.";
			link.l1 = "Mis marineros se encargarán de recoger la mercancía. Mientras tanto, iré a hablar con el tabernero.";
			link.l1.go = "Kristian_27";
			RemoveDublonsFromPCharTotal(130);
		break;
		
		case "Kristian_27":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.TPZ_Tavern_4 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "Kristian_31":
			dialog.text = "¡"+pchar.name+"! ¡Ya está aquí! ¿Y bien, todo salió bien?";
			link.l1 = "Todo en orden, Christian. El tabernero recogerá los mismos lotes dos veces al mes. Asegúrese de que los suministros sean estables, y olvidará lo que es la pobreza.";
			link.l1.go = "Kristian_32";
			DelLandQuestMark(npchar);
		break;
		
		case "Kristian_32":
			dialog.text = "Capitán... usted... ¡es como si el destino mismo lo hubiera traído a mí! Es un verdadero milagro, ¡aún no lo creo! ¿Qué he hecho para merecer tanta bondad? ¡No sé cómo agradecerle!";
			link.l1 = "Pero yo sí sé, Christian. Cada mes deberá reservar una parte de la mercancía exclusivamente para mí, y para nadie más. La compraré al precio que mencionó: diez doblones por diez botellas de vino y tres doblones por diez de ron.";
			link.l1.go = "Kristian_33";
		break;
		
		case "Kristian_33":
			dialog.text = "¡Será un placer, "+pchar.name+", reservarle el producto! Puede estar seguro, no le fallaré. ¿Cuánto desea llevar? ¿Cincuenta? ¿Cien botellas? ¡La cantidad que diga!";
			link.l1 = "Por ahora no necesito tanto. Veinte botellas estarán bien. Si necesito más, se lo haré saber.";
			link.l1.go = "Kristian_34";
		break;
		
		case "Kristian_34":
			dialog.text = "¡Por supuesto, por supuesto! Entonces, veinte botellas de vino y veinte de ron por 26 doblones. Cada mes, el día 15, la mercancía le estará esperando. ¡Será un gusto verle en cualquier momento, incluso si solo viene a saludar!";
			link.l1 = "Perfecto. Y otra cosa, Christian. He respondido por usted con mi nombre. No me falle.";
			link.l1.go = "Kristian_35";
		break;
		
		case "Kristian_35":
			dialog.text = "Yo... qué dice, capitán... usted... no, no, ¡no le fallaré! ¡Todo estará al más alto nivel, lo juro!";
			link.l1 = "Entonces, hasta pronto.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_SpawnShip");
		break;
		
		case "Pirate_1":
			dialog.text = "¡Canalla"+GetSexPhrase(""," maldita")+"! ¿Acaso no te enseñaron que meter la nariz en asuntos ajenos siempre trae problemas?";
			link.l1 = "Fuiste tú quien me atacó, y ahora dices que me entrometo en asuntos ajenos. ¿Estás loco?";
			link.l1.go = "Pirate_2";
		break;
		
		case "Pirate_2":
			dialog.text = "¡Rayo en mi bauprés! ¿Así que tú, "+GetSexPhrase("bastardo","desgraciada")+", ni siquiera entiendes en qué te has metido"+GetSexPhrase("","ta")+"? ¿Crees que los suministros a la taberna se detuvieron por casualidad?";
			link.l1 = "¿Quieres decir que esa factoría ardió por tu culpa?";
			link.l1.go = "Pirate_3";
		break;
		
		case "Pirate_3":
			dialog.text = "Ja, ja, por fin lo captas, ¡una bala en mi hígado! ¡Exactamente por mí! Estaba demasiado metido en el negocio. Pero como ves, siempre encuentro la manera de vencer al enemigo. Y tú tampoco escaparás, ¡una metralla en mi vela!";
			link.l1 = "Divertido. Bueno, veremos qué tan bueno eres, ¡una piraña en tu garganta! ¡Ja ja!";
			link.l1.go = "Pirate_4";
		break;
		
		case "Pirate_4":
			DialogExit();
			
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Kristian_41":
			dialog.text = "¡Hola "+pchar.name+"! ¿Qué le trae por aquí?";
			if(CheckAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom")) // торговля вином и ромом
			{
				if (GetDataDay() == 15)
				{
					link.l1 = "Hola, Christian. ¿Está listo el pedido para mí?";
					link.l1.go = "Kristian_42";
				}
			}
			link.l2 = "Hola, Christian. Solo quería ver cómo le va. Ya me voy.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Kristian_41";
		break;
		
		case "Kristian_42":
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				dialog.text = "Por supuesto, capitán. ¿Cómo pudo dudar de mi fiabilidad?";
				if (PCharDublonsTotal() >= 130)
				{
					link.l1 = "Claro que no, Christian. Aquí tiene sus doblones, me llevo la mercancía.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "En absoluto. Pero olvidé traer los doblones. Tal vez regrese más tarde.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			else
			{
				dialog.text = "Por supuesto, capitán. ¿Cómo pudo dudar de mi fiabilidad?";
				if (PCharDublonsTotal() >= 26)
				{
					link.l1 = "Claro que no, Christian. Aquí tiene sus doblones, me llevo la mercancía.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "En absoluto. Pero olvidé traer los doblones. Tal vez regrese más tarde.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoBlock")) // увеличить объём поставок вина и рома
			{
				link.l4 = "Christian, quiero comprar más. Digamos, cien botellas de ron y vino al mes.";
				link.l4.go = "UpgradeVino";
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom") && sti(pchar.Money) >= 50000) // увеличить объём поставок вина и рома, если в первый раз не принесли
			{
				link.l4 = "Christian, quiero hablar sobre aumentar los suministros.";
				link.l4.go = "UpgradeVino_Agreed";
			}
		break;
		
		case "Kristian_43":
					dialog.text = "Perfecto. El día quince habrá un nuevo lote esperándole, como siempre. Pase cuando guste.";
			link.l1 = "Por supuesto que vendré. Hasta pronto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				RemoveDublonsFromPCharTotal(130);
				AddItems(pchar, "potionrum", 100);
				AddItems(pchar, "potionwine", 100);
			}
			else
			{
				RemoveDublonsFromPCharTotal(26);
				AddItems(pchar, "potionrum", 20);
				AddItems(pchar, "potionwine", 20);
			}
			
			DeleteAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom");
			SetFunctionTimerCondition("TPZ_KristianReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			pchar.questTemp.TPZ_KritstianVinoAndRom = sti(pchar.questTemp.TPZ_KritstianVinoAndRom) + 1; // счётчик покупок
		break;
		
		case "UpgradeVino":
			dialog.text = "Capitán, aumentar el volumen es, por supuesto, algo placentero, pero también costoso. Más mercancía significa más manos de obra, ampliar el almacén, contratar un barco más grande... Sin inversión no podré garantizar el suministro a tiempo.";
			link.l1 = "¿Y de qué suma estamos hablando? ¿Cuánto se necesita para que todo funcione bien?";
			link.l1.go = "UpgradeVino_2";
		break;
		
		case "UpgradeVino_2":
			dialog.text = "Cincuenta mil pesos. Yo me haré cargo de los demás gastos.";
			link.l1 = "¿Cincuenta mil? Hmm... una suma considerable. ¿No se puede reducir el coste?";
			link.l1.go = "UpgradeVino_3";
		break;
		
		case "UpgradeVino_3":
			dialog.text = "Lamentablemente, capitán, no se puede ahorrar en esto. Si no se hace como es debido, todo puede salir... digamos, muy mal. Ni usted ni yo queremos problemas, ¿verdad?";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Aquí tiene el dinero. No me decepcione, Christian.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "¿Sabe, Christian? Tal vez no sea tan buena idea. Hablaremos más adelante.";
			link.l2.go = "UpgradeVino_4";
		break;
		
		case "UpgradeVino_4":
			dialog.text = "Como usted diga, capitán. Si cambia de opinión, hágamelo saber.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			pchar.questTemp.TPZ_KritstianVinoPotom = true;
		break;
		
		case "UpgradeVino_Agreed":
			dialog.text = "¡Capitán, son excelentes noticias! ¿Está listo para pagar los cincuenta mil pesos de inmediato?";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Aquí están sus monedas. No me decepcione, Christian.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Ahora mismo no tengo esa cantidad. Volveré cuando tenga suficiente dinero.";
			link.l2.go = "UpgradeVino_4";
		break;
		
		case "UpgradeVino_5":
			dialog.text = "¡Se lo prometo, "+pchar.name+", no se arrepentirá! Me pondré a trabajar de inmediato. Ya con el próximo lote podrá recibir cien botellas de ron y otras tantas de excelente vino, todo por ciento treinta doblones.";
			link.l1 = "Perfecto. Y no olvide actuar con cautela. Su trabajo afecta también a mi reputación.";
			link.l1.go = "UpgradeVino_6";
			AddMoneyToCharacter(pchar, -50000);
		break;
		
		case "UpgradeVino_6":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_41";
			pchar.questTemp.TPZ_UpgradeVino = true;
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			DeleteAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom");
			AddQuestRecordInfo("Useful_Acquaintances", "4_1");
		break;
		
		
	}
}